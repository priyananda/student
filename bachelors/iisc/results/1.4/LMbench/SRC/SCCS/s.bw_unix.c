h24681
s 00004/00001/00080
d D 1.9 97/06/25 10:25:01 lm 10 9
c ifdef TOUCH
cC
cK60058
cSAlpha2.11
e
s 00001/00001/00080
d D 1.8 97/06/16 19:05:50 lm 9 8
c lint
cK57336
e
s 00006/00006/00075
d D 1.7 97/06/15 22:38:58 lm 8 7
c lint
cK56779
e
s 00026/00021/00055
d D 1.6 97/06/12 21:30:06 lm 7 6
c new bench.h macros.
cK53045
cZ-07:00
e
s 00003/00003/00073
d D 1.5 96/11/13 16:09:37 lm 6 5
c bugs.
cK46477
e
s 00042/00095/00034
d D 1.4 96/11/11 03:36:51 lm 5 4
c Auto adjusting changes.
cK45183
e
s 00015/00006/00114
d D 1.3 96/11/08 19:58:18 lm 4 3
c gcc -Wall cleanup.
cK37765
cZ-08:00
e
s 00020/00011/00100
d D 1.2 96/05/30 00:32:16 lm 3 2
c autotiming
cK21975
e
s 00111/00000/00000
d D 1.1 96/05/22 00:33:03 lm 2 1
c Initial revision
cK15440
e
s 00000/00000/00000
d D 1.0 96/05/22 00:33:02 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK32506
cPsrc/bw_unix.c
cR3ecbff5984316fe
cV4
cX0x21
cZ-07:00
e
u
U
f e 0
f x 0x21
t
AF_UNIX measurements.
T
I 2
/*
 * bw_unix.c - simple Unix stream socket bandwidth test
 *
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id$\n";
D 5
#include "timing.c"
E 5
I 5
D 7
#include "timing.h"
E 7
I 7

E 7
#include "bench.h"
E 5
D 7
#include <sys/socket.h>
I 4
#include <sys/types.h>
#include <sys/wait.h>
E 7
E 4
D 3
#define	N	1000
E 3

I 3
D 5
int	N = 100;
int	notdone = 1;
I 4
void	client(int sock);
void	server(int sock);
int	writen(int fd, char *buf, int n);
int	readn(int fd, char *buf, int n);
E 5
I 5
D 7
int	XFER	= 100*1024*1024;
E 7
I 7
D 8
extern	void	exit();		/* for lint on SunOS 4.x */
void		writer(), reader();
E 8
I 8
void	reader(int control[2], int pipes[2], int bytes);
void	writer(int control[2], int pipes[2]);
E 8

int	XFER	= 10*1024*1024;
int	pid;
E 7
char	*buf;
D 7
void	reader(int pipes[2]);
void	writer(int pipes[2]);
E 7
E 5
E 4

E 3
D 4
main()
E 4
I 4
int
D 7
main(int ac, char **av)
E 7
I 7
main()
E 7
E 4
{
D 5
	int	sv[2];
E 5
I 5
	int	pipes[2];
D 7
	int	pid, N, i;
E 7
I 7
	int	control[2];
E 7
E 5

D 3
	write(2, id, strlen(id));
E 3
D 5
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) == -1) {
E 5
I 5
	buf = valloc(XFERSIZE);
D 9
	bzero(buf, XFERSIZE);
E 9
I 9
D 10
	bzero((void*)buf, XFERSIZE);
E 10
I 10
	touch(buf, XFERSIZE);
E 10
E 9
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, pipes) == -1) {
E 5
		perror("socketpair");
I 7
		return (1);
E 7
	}
I 7
	if (pipe(control) == -1) {
		perror("pipe");
D 8
		exit(1);
E 8
I 8
		return(1);
E 8
	}
E 7
D 3
	if (fork() == 0) {
		doserver(sv[0]);
	} else {
		doclient(sv[1]);
	}
E 3
I 3
D 5
	do {
		if (fork() == 0) {
D 4
			doserver(sv[0]);
E 4
I 4
			server(sv[0]);
E 4
		} else {
D 4
			doclient(sv[1]);
E 4
I 4
			client(sv[1]);
E 4
		}
	} while (notdone);
E 5
I 5
	switch (pid = fork()) {
	    case 0:
D 7
		writer(pipes);
E 7
I 7
		writer(control, pipes);
E 7
D 8
		exit(0);
E 8
I 8
		return(0);
E 8
		/*NOTREACHED*/
	    
	    case -1:
		perror("fork");
D 8
		exit(1);
E 8
I 8
		return(1);
E 8
		/*NOTREACHED*/

	    default:
		break;
	}
D 6
	LOOP_FIRST(N, i, ENOUGH);
E 6
I 6
D 7
	LOOP_FIRST(N, i, MEDIUM);
E 6
	reader(pipes);
D 6
	LOOP_LAST(N, i, ENOUGH);
	fprintf(stderr, "Pipe bandwidth: ");
E 6
I 6
	LOOP_LAST(N, i, MEDIUM);
E 7
I 7
	BENCH(reader(control, pipes, XFER), MEDIUM);
E 7
	fprintf(stderr, "AF_UNIX sock stream bandwidth: ");
E 6
D 7
	mb(N * XFER);
E 7
I 7
	mb(get_n() * XFER);
E 7
	kill(pid, 15);
E 5
E 3
D 8
	exit(0);
E 8
I 8
	return(0);
E 8
}

D 4
doclient(int sock)
E 4
I 4
void
D 5
client(int sock)
E 5
I 5
D 7
writer(int pipes[2])
E 7
I 7
writer(int control[2], int pipes[2])
E 7
E 5
E 4
{
D 3
	int     i, n;
E 3
I 3
D 4
	int     usecs, i, n;
E 4
I 4
D 5
	int     usecs, i;
E 4
E 3
	char	*buf = valloc(XFERSIZE);
E 5
I 5
D 7
	int	todo, done, n;
E 7
I 7
	int	todo, n;
E 7
E 5

D 5
	start();
	for (i = 0; i < N; ++i) {
		if (writen(sock, buf, XFERSIZE) != XFERSIZE) {
			perror("write on socket");
			kill(getppid(), SIGTERM);
			exit(1);
		}
E 5
I 5
	for ( ;; ) {
D 7
		done = 0;
		todo = XFER;
		while ((done < todo) && ((n = write(pipes[1], buf, XFERSIZE)) > 0))
			done += n;
E 7
I 7
		read(control[0], &todo, sizeof(todo));
		while (todo > 0) {
I 10
#ifdef TOUCH
			touch(buf, XFERSIZE);
#endif
E 10
			n = write(pipes[1], buf, XFERSIZE);
			todo -= n;
		}
E 7
E 5
	}
D 5
	if (read(sock, buf, 1) != 1) {
		perror("can't read on socket");
		kill(getppid(), SIGTERM);
		exit(1);
	}
D 3
	stop();
	sprintf(buf, "AF_UNIX sock stream bandwidth");
	bandwidth(N * XFERSIZE, 1);
E 3
I 3
	usecs = stop();
	if (usecs < 1000000) {
		N <<= 2;
		wait(0);
		return;
	}
	notdone = 0;
	fprintf(stderr, "AF_UNIX sock stream bandwidth: ");
	mb(N * XFERSIZE);
E 5
E 3
}

D 4
doserver(sock)
E 4
I 4
void
D 5
server(sock)
E 5
I 5
D 7
reader(int pipes[2])
E 7
I 7
reader(int control[2], int pipes[2], int bytes)
E 7
E 5
E 4
{
D 5
	int	i;
	char	*buf = valloc(XFERSIZE);
	void	exit();

	signal(SIGTERM, exit);
	for (i = 0; i < N; ++i) {
		if (readn(sock, buf, XFERSIZE) != XFERSIZE) {
			perror("read on socket");
			kill(getppid(), SIGTERM);
			exit(1);
		}
E 5
I 5
	int	todo = XFER, done = 0, n;
I 7

	write(control[1], &bytes, sizeof(bytes));
E 7
	while ((done < todo) && ((n = read(pipes[0], buf, XFERSIZE)) > 0)) {
		done += n;
E 5
	}
D 5
	if (write(sock, buf, 1) != 1) {
		perror("can't read on socket");
		exit(1);
	}
	exit(0);
E 5
}
D 5

int
writen(int fd, char *buf, int n)
{
	int	done = 0, ret;

	do {
		ret = write(fd, buf + done, n - done);
		switch (ret) {
		    case -1:
		    case 0:
			perror("write");
			return (-1);
		    default:
			done += ret;
		}
	} while (done < n);
	return (done);
}

int
readn(int fd, char *buf, int n)
{
	int	done = 0, ret;

	do {
		ret = read(fd, buf + done, n - done);
		switch (ret) {
		    case -1:
		    case 0:
			perror("read");
			return (-1);
		    default:
			done += ret;
		}
	} while (done < n);
	return (done);
}
E 5
E 2
I 1
E 1
