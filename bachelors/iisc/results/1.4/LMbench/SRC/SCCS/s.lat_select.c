h20814
s 00001/00001/00144
d D 1.13 00/12/11 16:22:32 staelin 14 13
c - Fix lat_select so all tmpfiles are always removed
cC
cK15464
e
s 00044/00014/00101
d D 1.12 00/10/30 13:42:37 staelin 13 12
c - Use SOCKOPT_REUSE on the tcp_server() socket
c - Close all open file descriptors on exit
c - Make sure you kill the child server process correctly
cC
cK16558
e
s 00081/00012/00034
d D 1.11 00/10/25 12:33:29 staelin 12 11
c - Enhance lat_select so it can select either on a file or on a TCP
c   socket.
c - Modify getsummary so the TCP socket select latency is used rather
c   than the file latency (select() is more commonly used for networking
c   than for files)
cC
cHhpli8.hpli.hpl.hp.com
cK51510
cZ+02:00
e
s 00001/00001/00045
d D 1.10 00/09/24 12:00:13 lm 11 10
c Add an exit(0) for that lovely example of operating system
c known as OpenBSD, which apparently can't handle a return(0).
cC
cHopenbsd.bitmover.com
cK01621
e
s 00002/00001/00044
d D 1.9 98/07/31 12:47:56 lm 10 9
c There was a hang if I didn't put a timeout in there when
c running in MP mode on IRIX 6.5 (Olson's machine).  XXX
cC
cK01851
cSAlpha2.11
e
s 00002/00001/00043
d D 1.8 98/06/29 22:37:39 lm 9 8
c Redo to compile clean with -Wall.
cK64699
e
s 00008/00006/00036
d D 1.7 97/10/19 23:47:45 lm 8 7
c *** empty log message ***
cK63471
e
s 00000/00001/00042
d D 1.6 97/06/15 22:38:58 lm 7 6
c lint
cK60745
e
s 00001/00000/00042
d D 1.5 97/06/14 12:20:51 lm 6 5
c morefds().
cK61345
e
s 00008/00007/00034
d D 1.4 97/06/13 20:39:50 lm 5 4
c lint
cK60434
e
s 00012/00015/00029
d D 1.3 97/06/12 21:30:06 lm 4 3
c new bench.h macros.
cK59990
cZ-07:00
e
s 00004/00002/00040
d D 1.2 96/11/21 17:48:04 lm 3 2
c timing.c interfaces.
cK03852
e
s 00042/00000/00000
d D 1.1 96/11/13 16:16:07 lm 2 1
c Initial revision
cK03500
e
s 00000/00000/00000
d D 1.0 96/11/13 16:16:06 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK65044
cPsrc/lat_select.c
cR97c296f6daba401d
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
/*
 * lat_select.c - time select system call
 *
D 12
 * usage: lat_select [n]
E 12
I 12
 * usage: lat_select tcp|file [n]
E 12
 *
 * Copyright (c) 1996 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 */
char	*id = "$Id$\n";

D 4
#include "timing.h"
E 4
#include "bench.h"
D 4
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
E 4

I 13
int	nfds;
fd_set	set;

E 13
I 5
void
doit(int n, fd_set *set)
{
D 8
	fd_set	save = *set;
	select(n, 0, set, 0, 0);
	*set = save;
E 8
I 8
	fd_set	nosave = *set;
D 10
	select(n, 0, &nosave, 0, 0);
E 10
I 10
	static	struct timeval tv;
	select(n, 0, &nosave, 0, &tv);
E 10
E 8
}

I 13
void
sigterm(int sig)
{
	int	fid;

	for (fid = 0; fid < nfds; ++fid) {
		if (FD_ISSET(fid, &set)) {
			close(fid);
		}
	}
	tcp_done(TCP_SELECT);
	exit(0);
}

E 13
E 5
int
main(int ac, char **av)
{
D 7
	char	c;
E 7
D 4
	int	N = 200, i, fd;
	fd_set	save, set;
E 4
I 4
D 8
	int	N = 200, fd;
E 8
I 8
D 9
	int	i, last, N = 200, fd;
E 9
I 9
D 12
	int	i, last = 0 /* lint */;
	int	N = 200, fd;
E 12
I 12
D 13
	int	n, N, last, fd, fid;
E 13
I 13
	char	c;
	int	n, N, fd, fid;
E 13
	pid_t	pid, ppid;
E 12
E 9
E 8
D 13
	fd_set	set;
E 13
E 4
I 3
D 12
	char	buf[256];
E 12
I 12
	char	buf[L_tmpnam+256];
	char	fname[L_tmpnam];
	char*	report_file = "Select on %d fd's";
	char*	report_tcp  = "Select on %d tcp fd's";
	char*	report;
	char*	usage = "lat_select tcp|file [n]\n";
E 12
E 3

I 6
	morefds();
E 6
D 12
	if (ac > 1) N = atoi(av[1]);
E 12
I 12
	N = 200;
	fname[0] = 0;
	pid = 0;
I 13
	c = 0;
	nfds = 0;
	FD_ZERO(&set);
E 13
	report = report_file;

	if (ac != 2 && ac != 3) {
		fprintf(stderr, usage);
		exit(1);
	}

	if (streq(av[1], "tcp")) {
		report = report_tcp;
		
		/* Create a socket for clients to connect to */
D 13
		fd = tcp_server(TCP_CONNECT, SOCKOPT_NONE);
E 13
I 13
		fd = tcp_server(TCP_SELECT, SOCKOPT_REUSE);
E 13
		if (fd <= 0) {
			perror("lat_select: Could not open tcp server socket");
			exit(1);
		}

		/* Start server process to accept client connections */
		ppid = getpid();
		switch(pid = fork()) {
		case 0:
			/* child server process */
I 13
			if (signal(SIGTERM, sigterm) == SIG_ERR) {
				perror("signal(SIGTERM, sigterm) failed");
				exit(1);
			}
			FD_SET(fd, &set);
E 13
			while (ppid == getppid()) {
				int newsock = tcp_accept(fd, SOCKOPT_NONE);
D 13
				read(newsock, &fid, 1);
				close(newsock);
E 13
I 13
				if (newsock >= nfds) nfds = newsock + 1;
				FD_SET(newsock, &set);
E 13
			}
D 13
			close(fd);
			exit(0);
E 13
I 13
			sigterm(SIGTERM);
			/* NOTREACHED */
E 13
		case -1:
			/* error */
			perror("lat_select::server(): fork() failed");
			exit(1);
		default:
			break;
		}
		close(fd);
D 13
		fd = tcp_connect("localhost", TCP_CONNECT, SOCKOPT_NONE);
E 13
I 13
		fd = tcp_connect("localhost", TCP_SELECT, SOCKOPT_NONE);
E 13
		if (fd <= 0) {
			perror("lat_select: Could not open socket");
			exit(1);
		}
	} else if (streq(av[1], "file")) {
		/* Create a temporary file for clients to open */
		tmpnam(fname);
		fd = open(fname, O_RDWR|O_APPEND|O_CREAT, 0666);
I 14
		unlink(fname);
E 14
		if (fd <= 0) {
			char buf[L_tmpnam+128];
			sprintf(buf, 
				"lat_select: Could not create temp file %s", fname);
			perror(buf);
			exit(1);
		}
	} else {
		fprintf(stderr, usage);
		exit(1);
	}

	if (ac == 3) N = atoi(av[2]);

E 12
D 13
	FD_ZERO(&set);
I 8
D 12
	for (i = 3; i < 50; ++i) close(i);
E 8
	for (fd = 0; fd < N; fd++) {
D 4
		i = open("/dev/tty", 1);
E 4
I 4
D 8
		int i = open("/dev/tty", 1);
E 8
I 8
		i = dup(0);
E 8
E 4
I 3
		if (i == -1) break;
I 8
		last = i;
E 8
E 3
		FD_SET(i, &set);
E 12
I 12
	last = 0;
E 13
	for (n = 0; n < N; n++) {
		fid = dup(fd);
		if (fid == -1) break;
D 13
		if (fid > last) last = fid;
E 13
I 13
		if (fid >= nfds) nfds = fid + 1;
E 13
		FD_SET(fid, &set);
E 12
	}
D 4
	LOOP_FIRST(N, i, ENOUGH);
	save = set;
	select(fd, 0, &set, 0, 0);
	set = save;
	LOOP_LAST(N, i, ENOUGH);
E 4
I 4
D 8
	BENCH(doit(fd, &set), 0);
E 8
I 8
D 13
	last++;
	BENCH(doit(last, &set), 0);
E 13
I 13
	BENCH(doit(nfds, &set), 0);
E 13
E 8
E 4
D 3
	fprintf(stderr,
	    "Select on %d fd's: %.3f microseconds\n", fd, (double)i/N);
E 3
I 3
D 12
	sprintf(buf, "Select on %d fd's", fd);
E 12
I 12
	sprintf(buf, report, n);
E 12
D 4
	micro(buf, N);
E 4
I 4
	micro(buf, get_n());
I 12
D 13
	if (pid) kill(SIGKILL, pid);
E 13
I 13

	for (fid = 0; fid < nfds; fid++) {
		if (FD_ISSET(fid, &set)) {
			close(fid);
		}
	}
	close(fd);
	if (pid) kill(pid, SIGTERM);
E 13
D 14
	if (fname[0]) unlink(fname);
E 14
I 13

E 13
E 12
E 4
E 3
D 11
	return(0);
E 11
I 11
	exit(0);
E 11
}
I 4
D 5

doit(int n, fd_set *set)
{
	fd_set	save = *set;
	select(n, 0, set, 0, 0);
	*set = save;
}
E 5
E 4
E 2
I 1
E 1
