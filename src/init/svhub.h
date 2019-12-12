#include <bits/types.h>

#define NAMELEN 19
#define NPROCS 40
#define NCONNS 10
#define NPREQS 10

#define STABLE_TRESHOLD 5
#define TIME_TO_RESTART 1
#define TIME_TO_SIGKILL 2
#define TIME_TO_SKIP    5

#define PAGE 4096
#define RINGSIZE 1024

#define P_DISABLED      (1<<0)
#define P_SIGSTOP       (1<<1)
#define P_SIGTERM       (1<<2)
#define P_SIGKILL       (1<<3)
#define P_RESTART       (1<<4)
#define P_FAILED        (1<<5)
#define P_STALE         (1<<6)
#define P_STUCK         (1<<7)

#define F_WAIT_PIDS     (1<<0)
#define F_SETUP_CTRL    (1<<1)
#define F_RELOAD_PROCS  (1<<2)
#define F_CHECK_PROCS   (1<<3)
#define F_TRIM_RING     (1<<4)
#define F_UPDATE_PFDS   (1<<5)
#define F_EXIT_LOOP     (1<<6)

struct proc {
	int pid;
	uint8_t flags;
	char name[NAMELEN];
	time_t lastrun;
	time_t lastsig;
	int status;
	int pipefd;
	/* ring buffer */
	short idx;
	short ptr;
};

struct conn {
	int fd;
	int pid;
};

struct ucmsg;

extern const char* rbscript;
extern int ctrlfd;
extern char* confdir;
extern char** environ;
extern time_t passtime;
extern char* reboot;

extern struct proc procs[];
extern struct conn conns[];
extern int nprocs;
extern int nconns;

struct proc* firstrec(void);
struct proc* nextrec(struct proc* rc);

struct proc* find_by_name(char* name);
struct proc* find_by_pid(int pid);
struct proc* grab_proc_slot(void);
void free_proc_slot(struct proc* rc);
void close_conn(struct conn* cn);

struct conn* grab_conn_slot(void);
void free_conn_slot(struct conn* cn);

void set_passtime(void);
int runtime(struct proc* rc);
void check_procs(void);
void update_poll_fds(void);
void wait_poll(void);
void wait_pids(void);

int setup_signals(void);
void setup_ctrl(void);
void accept_ctrl(int sfd);
void wakeupin(int ttw);
void request(int flag);
void handle_conn(struct conn* cn);
int stop_into(const char* script);
void notify_dead(int pid);

char* ring_buf_for(struct proc* rc);
int read_into_ring_buf(struct proc* rc);
void trim_ring_area(void);
void flush_ring_buf(struct proc* rc);

int reload_procs(void);

void report(char* msg, char* arg, int err);
void reprec(struct proc* rc, char* msg);

void stop_all_procs(void);
