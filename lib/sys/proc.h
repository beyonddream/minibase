#include <bits/signal.h>
#include <syscall.h>

#define	WNOHANG		1	/* Don't block waiting.  */
#define WUNTRACED	2	/* Report stopped child. */
#define WCONTINUED	8	/* Report continued child.  */

#define WEXITSTATUS(status)	(((status) & 0xFF00) >> 8)
#define WTERMSIG(status)	((status) & 0x7F)

#define WIFEXITED(status)	(WTERMSIG(status) == 0)
#define WIFSIGNALED(status)	(!WIFSTOPPED(status) && !WIFEXITED(status))
#define WIFSTOPPED(status)	(((status) & 0xFF) == 0x7F)
#define WIFCONTINUED(status)	((status) == 0xFFFF)

inline static long sys_fork(void)
{
	return syscall5(NR_clone, SIGCHLD, 0, 0, 0, 0);
}

inline static long sys_execve(const char* exe, char** argv, char** envp)
{
	return syscall3(NR_execve, (long)exe, (long)argv, (long)envp);
}

inline static long sys_waitpid(int pid, int* status, int flags)
{
	return syscall4(NR_wait4, pid, (long)status, flags, 0);
}
