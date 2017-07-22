#include <sys/file.h>
#include <sys/kill.h>
#include <sys/wait.h>

#include <format.h>
#include <string.h>
#include <fail.h>

#include "vtmux.h"

/* Non-terminal SIGCHLD handler. Close fds, deallocate VT,
   and do whatever else cleanup necessary.

   Most clients should die while active, but inactive ones may die
   as well. Background deaths should not cause VT switching.

   In case of abnormal exit, let the user read whatever the failed
   process might have printed to its stderr.

   Successful exit means logout and return to greeter. Except on
   a fixed VT, then it is probably better to restart the client.
   There's no such thing as "logout" on fixed VTs, and no login
   either, so no point in activating greeter VT.

   Restarts are not timed. Abnormal exits require user intervention,
   and normal exits are presumed to not happen too fast.

   Greeter may, and probably should, exit with 0 status if it is not
   being used for some time. There's no point in keeping it running
   in background, it will be re-started on request anyway. */

static void report_cause(int fd, int status)
{
	char msg[32];
	char* p = msg;
	char* e = msg + sizeof(msg) - 1;

	if(WIFEXITED(status)) {
		p = fmtstr(p, e, "Exit ");
		p = fmtint(p, e, WEXITSTATUS(status));
	} else {
		p = fmtstr(p, e, "Signal ");
		p = fmtint(p, e, WTERMSIG(status));
	}

	*p++ = '\n';
	int ret = sys_write(fd, msg, p - msg);

	if(ret < 0)
		warn("write", NULL, ret);
}

/* No idea why this is necessary, but the open tty fd somehow gets
   invalidated when the child exits. May be related to setsid.
   Anyway, to do anything with the tty we have to re-open it.

   There are few cases when the newly-opened fd will be closed
   immediately in closevt(), however skipping reopen just isn't
   worth the trouble. */

static void reopen_tty_device(struct term* vt)
{
	int fd;

	sys_close(vt->ttyfd);
	vt->ttyfd = 0;

	if((fd = open_tty_device(vt->tty)) < 0)
		return;

	vt->ttyfd = fd;
}

void wait_pids(int shutdown)
{
	int status;
	int pid, ret;
	struct term *cvt, *active = NULL;

	while((pid = sys_waitpid(-1, &status, WNOHANG)) > 0) {
		if(!(cvt = find_term_by_pid(pid)))
			continue;

		reopen_tty_device(cvt);

		if(status && cvt->ttyfd > 0)
			report_cause(cvt->ttyfd, status);
		if(cvt->tty == activetty && !status)
			active = cvt;

		closevt(cvt, !!status);
	}

	if(!active || shutdown)
		return;
	else if(active->pin)
		ret = switchto(active->tty); /* try to restart it */
	else
		ret = switchto(terms[0].tty); /* greeter */
	if(ret < 0)
		warn("switchto", NULL, ret);
}

/* Shutdown routines: wait for VT clients to die before exiting. */

int count_running(void)
{
	int count = 0;
	struct term* cvt;

	for(cvt = terms; cvt < terms + nterms; cvt++)
		if(cvt->pid > 0)
			count++;

	return count;
}

static void kill_all_terms(int sig)
{
	struct term* cvt;

	for(cvt = terms; cvt < terms + nterms; cvt++)
		if(cvt->pid > 0)
			sys_kill(cvt->pid, sig);
}

void terminate_children(void)
{
	warn("shutdown", NULL, 0);

	kill_all_terms(SIGTERM);

	if(poll_final(1) >= 0)
		return;

	warn("waiting for children to terminate", NULL, 0);

	if(poll_final(4) >= 0)
		return;

	warn("sending SIGKILL to all children", NULL, 0);
	kill_all_terms(SIGKILL);

	if(poll_final(1) >= 0)
		return;

	warn("timeout waiting for children", NULL, 0);
}