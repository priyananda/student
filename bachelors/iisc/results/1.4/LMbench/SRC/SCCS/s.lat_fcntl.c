h50401
s 00016/00018/00112
d D 1.2 00/12/11 16:20:57 staelin 3 2
c - Fix lock/unlock sequencing bug in lat_fcntl
c - Remove unnecessary fork()/wait() operations in lat_fcntl
c - Always remove tmpfiles in lat_fcntl
cC
cHhpli8.hpli.hpl.hp.com
cK48357
cZ+02:00
e
s 00130/00000/00000
d D 1.1 99/12/08 09:18:19 lm 2 1
cC
cF1
cK45595
cO-rw-r--r--
e
s 00000/00000/00000
d D 1.0 99/12/08 09:18:19 lm 1 0
c BitKeeper file /home/lm/lmbench/src/lat_fcntl.c
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHwork.bitmover.com
cK08698
cPsrc/lat_fcntl.c
cR13b82230576b9707
cV4
cX0x21
cZ-08:00
e
u
U
f e 0
f x 0x21
t
T
I 2
#include "bench.h"

/*
 * lat_pipe.c - pipe transaction test
 *
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id: lat_pipe.c,v 1.8 1997/06/16 05:38:58 lm Exp $\n";

#include "bench.h"

struct	flock lock, unlock;
struct	flock s1, s2;
int	fd1, fd2;

/*
 * Create two files, use them as a ping pong test.
 * Process A:
 *	lock(1)
 *	unlock(2)
 * Process B:
 *	unlock(1)
 *	lock(2)
 * Initial state:
 *	lock is locked
 *	lock2 is locked
 */

#define	waiton(fd)	fcntl(fd, F_SETLKW, &lock)
#define	release(fd)	fcntl(fd, F_SETLK, &unlock)

void
procA()
{
	if (waiton(fd1) == -1) {
		perror("lock of fd1 failed\n");
		exit(1);
	}
	if (release(fd2) == -1) {
		perror("unlock of fd2 failed\n");
		exit(1);
	}
	if (waiton(fd2) == -1) {
		perror("lock of fd2 failed\n");
		exit(1);
	}
	if (release(fd1) == -1) {
		perror("unlock of fd1 failed\n");
		exit(1);
	}
}

void
procB()
{
	if (release(fd1) == -1) {
		perror("unlock of fd1 failed\n");
		exit(1);
	}
	if (waiton(fd2) == -1) {
		perror("lock of fd2 failed\n");
		exit(1);
	}
D 3
	if (waiton(fd1) == -1) {
		perror("lock of fd1 failed\n");
		exit(1);
	}
E 3
	if (release(fd2) == -1) {
		perror("unlock of fd2 failed\n");
		exit(1);
	}
I 3
	if (waiton(fd1) == -1) {
		perror("lock of fd1 failed\n");
		exit(1);
	}
E 3
}

int
main()
{
	char	buf[10000];
	int	pid;

	unlink("/tmp/lmbench-fcntl.1");
	unlink("/tmp/lmbench-fcntl.2");
	if ((fd1 = open("/tmp/lmbench-fcntl.1", O_CREAT|O_RDWR, 0666)) == -1) {
		perror("create");
		exit(1);
	}
	if ((fd2 = open("/tmp/lmbench-fcntl.2", O_CREAT|O_RDWR, 0666)) == -1) {
		perror("create");
		exit(1);
	}
I 3
	unlink("/tmp/lmbench-fcntl.1");
	unlink("/tmp/lmbench-fcntl.2");
E 3
	write(fd1, buf, sizeof(buf));
	write(fd2, buf, sizeof(buf));
	lock.l_type = F_WRLCK;
	lock.l_whence = 0;
	lock.l_start = 0;
	lock.l_len = 1;
	unlock = lock;
	unlock.l_type = F_UNLCK;
	if (waiton(fd1) == -1) {
		perror("lock1");
		exit(1);
	}
	if (waiton(fd2) == -1) {
		perror("lock2");
		exit(1);
	}
D 3
	if (fork()) {
		wait(0);
	}
	pid = fork();
	if (pid == -1) {
E 3
I 3
	switch (pid = fork()) {
	case -1:
E 3
		perror("fork");
		exit(1);
D 3
	}
	if (pid > 0) {
		waiton(fd1);
		BENCH(procA(), SHORT);
		micro("Fcntl lock latency", get_n());
		kill(pid, 15);
	} else {
		waiton(fd2);
E 3
I 3
	case 0:
E 3
		for ( ;; ) {
			procB();
		}
D 3
	}
E 3
I 3
		exit(0);
	default:
		break;
	}
	BENCH(procA(), SHORT);
	micro("Fcntl lock latency", 2 * get_n());
	kill(pid, 15);
E 3
	return (0);
}
E 2
I 1
E 1
