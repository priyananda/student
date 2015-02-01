h63916
s 00004/00001/00192
d D 1.16 00/08/03 15:02:05 lm 17 16
c Do not move less than MINMOVE bytes.  Don't run this over your modem.
cC
cHwork.bitmover.com
cK05364
e
s 00001/00001/00192
d D 1.15 97/10/19 23:40:11 lm 16 15
c *** empty log message ***
cC
cK01142
cSAlpha2.11
e
s 00007/00008/00186
d D 1.14 97/06/25 10:25:01 lm 15 14
c ifdef TOUCH
cK01089
e
s 00004/00004/00190
d D 1.13 97/06/16 19:05:50 lm 14 13
c lint
cK05198
e
s 00004/00002/00190
d D 1.12 97/06/15 22:38:58 lm 13 12
c lint
cK02970
e
s 00024/00022/00168
d D 1.11 97/06/13 20:39:50 lm 12 11
c lint
cK02317
e
s 00013/00016/00177
d D 1.10 97/06/12 21:30:06 lm 11 10
c new bench.h macros.
cK02007
e
s 00038/00019/00155
d D 1.9 97/05/27 16:01:56 lm 10 9
c make it work witht he new timing loop.
cK01621
e
s 00017/00029/00157
d D 1.8 97/04/23 22:10:09 lm 9 8
c 10 second loop.
cK46000
cZ-07:00
e
s 00054/00060/00132
d D 1.7 96/11/11 03:36:51 lm 8 7
c Auto adjusting changes.
cK57455
e
s 00022/00025/00170
d D 1.6 96/11/08 19:58:07 lm 7 6
c gcc -Wall cleanup & new timing.c integration.
cK22746
cZ-08:00
e
s 00036/00027/00159
d D 1.5 96/05/30 00:32:36 lm 6 5
c autotiming
cK19272
cZ-07:00
e
s 00007/00007/00179
d D 1.4 96/01/24 17:09:19 lm 5 4
c Make everything use XFERSIZE
cK11890
cZ-08:00
e
s 00019/00004/00167
d D 1.3 95/06/21 14:02:49 lm 4 3
c Use valloc for buffer.
cK11250
cZ-07:00
e
s 00027/00014/00144
d D 1.2 95/03/10 18:18:06 lm 3 2
c sockopt stuff and make it so that I can wrap a script around it to do N.
cK62334
e
s 00158/00000/00000
d D 1.1 94/11/18 00:49:48 lm 2 1
c Initial revision
cK49052
e
s 00000/00000/00000
d D 1.0 94/11/18 00:49:47 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK19070
cPsrc/bw_tcp.c
cR7051c2802eae1cf3
cV4
cX0x21
cZ-08:00
e
u
U
f e 0
f x 0x21
t
lmbench src
T
I 2
/*
 * bw_tcp.c - simple TCP bandwidth test
 *
 * Three programs in one -
 *	server usage:	bw_tcp -s
 *	client usage:	bw_tcp hostname
 *	shutdown:	bw_tcp -hostname
 *
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id$\n";
D 8
#include "lib_tcp.c"
#include "timing.c"
I 7
#include	<sys/types.h>
#include	<sys/wait.h>
E 8
I 8
D 11
#include <sys/types.h>
#include <sys/wait.h>
E 11
#include "bench.h"
D 11
#include "timing.h"
#include "lib_tcp.h"
E 11
E 8
E 7

I 17
#define	MINMOVE	(10<<20)

E 17
D 7
main(ac, av)
	char  **av;
E 7
I 7
int	server_main(int ac, char **av);
int	client_main(int ac, char **av);
D 8
void	absorb(int control, int data);
E 8
I 8
void	source(int data);
E 8

I 8
char	*buf;

E 8
D 12
int
main(int ac, char **av)
E 7
{
D 6
	write(2, id, strlen(id));
E 6
	if (ac != 2 && ac != 3) {
		fprintf(stderr, "Usage: %s -s OR %s [-]serverhost\n",
		    av[0], av[0]);
		exit(1);
	}
I 8
	buf = valloc(XFERSIZE);
	bzero(buf, XFERSIZE);
E 8
	if (!strcmp(av[1], "-s")) {
		if (fork() == 0) {
			server_main(ac, av);
		}
		exit(0);
	} else {
		client_main(ac, av);
	}
D 3
	exit(0);
E 3
I 3
	return(0);
E 3
}

E 12
I 12
void
E 12
I 10
transfer(uint64 move, char *server)
{
	int	data, c;
	uint64	todo;

	todo = move;
D 11
	/* printf("Move %lu MB\n", (unsigned long)(move>>20)); */
E 11
I 11
D 12
	/*printf("Move %lu MB\n", (unsigned long)(move>>20)); /* */
E 12
I 12
	/*printf("Move %lu MB\n", (unsigned long)(move>>20));
	*/
E 12
E 11
	data = tcp_connect(server, TCP_DATA, SOCKOPT_READ);
	(void)sprintf(buf, "%lu", (unsigned long)move);
	if (write(data, buf, strlen(buf)) != strlen(buf)) {
		perror("control write");
		exit(1);
	}
	while (todo > 0 && (c = read(data, buf, XFERSIZE)) > 0) {
		todo -= c;
D 15
#ifdef	TOUCH
D 14
		bzero(buf, c);
E 14
I 14
		bzero((void*)buf, c);
E 14
#endif
E 15
	}
	(void)close(data);
}

I 13
/* ARGSUSED */
E 13
E 10
D 7
client_main(ac, av)
	char  **av;
E 7
I 7
int
client_main(int ac, char **av)
E 7
{
D 4
	char    buf[SOCKBUF];
E 4
I 4
D 5
	char    *buf = valloc(SOCKBUF);
E 5
I 5
D 8
	char    *buf = valloc(XFERSIZE);
E 5
E 4
	int     data, control;
	int     c;
D 7
	int     bytes;
E 7
I 7
	int     move;
E 7
I 6
	int	usecs;
	int	todo;
E 8
I 8
D 10
	int	data;
	int	c;
D 9
	uint64	move, usecs, todo;
E 9
I 9
	uint64	move, N, usecs, todo;
E 10
I 10
	uint64	move;
D 11
	int	N, usecs;
E 11
E 10
E 9
E 8
E 6
	char   *server;
I 11
	uint64	usecs;
E 11

	if (ac != 2 && ac != 3) {
D 8
		(void)fprintf(stderr, "usage: %s remotehost [count]\n",
E 8
I 8
		(void)fprintf(stderr, "usage: %s remotehost [bytes]\n",
E 8
		    av[0]);
		exit(0);
	}
I 4
	if (!buf) {
		perror("valloc");
		exit(1);
	}
E 4
	if (ac == 3) {
D 7
		bytes = atoi(av[2]);
		if ((last(av[2]) == 'k') || (last(av[2]) == 'K'))
			bytes *= 1024;
		if ((last(av[2]) == 'm') || (last(av[2]) == 'M'))
			bytes *= (1024 * 1024);
E 7
I 7
		move = bytes(av[2]);
E 7
	} else {
D 5
		bytes = 3*1024*1024;
E 5
I 5
D 7
		bytes = 10*1024*1024;
E 7
I 7
D 9
		move = 10*1024*1024;
E 9
I 9
D 11
		move = 25*1024*1024;
E 11
I 11
D 17
		move = 10*1024*1024;
E 17
I 17
		move = MINMOVE;
E 17
E 11
E 9
E 7
E 5
	}
I 8
	/*
	 * Disabler message to other side.
	 */
E 8
	if (av[1][0] == '-') {
I 10
		int	data;

E 10
D 7
		bytes = 0;
E 7
I 7
		move = 0;
E 7
		server = &av[1][1];
I 8
		data = tcp_connect(server, TCP_DATA, SOCKOPT_NONE);
		write(data, "0", 1);
		exit(0);
E 8
	} else {
		server = av[1];
	}
I 11
	/*
	 * Make one run take at least 5 seconds.
	 * This minimizes the effect of connect & reopening TCP windows.
	 */
E 11
D 3
	control = tcp_connect(server, TCP_CONTROL);
	data = tcp_connect(server, TCP_DATA);
E 3
I 3
D 6
	control = tcp_connect(server, TCP_CONTROL, SOCKOPT_NONE);
	data = tcp_connect(server, TCP_DATA, SOCKOPT_WRITE);
E 3
	(void)sprintf(buf, "%d", bytes);
	if (write(control, buf, strlen(buf)) != strlen(buf)) {
		perror("control write");
		exit(1);
	}
	/*
	 * Disabler message to other side.
	 */
	if (bytes == 0) {
		exit(0);
	}
D 4
	while (bytes > 0 && (c = write(data, buf, sizeof(buf))) > 0)
E 4
I 4
D 5
	while (bytes > 0 && (c = write(data, buf, SOCKBUF)) > 0) {
E 5
I 5
	while (bytes > 0 && (c = write(data, buf, XFERSIZE)) > 0) {
E 5
E 4
		bytes -= c;
I 4
#if 0
E 6
I 6
D 8
	do {
E 8
I 8
D 9
	for (;;) {
E 8
D 7
		todo = bytes;
E 7
I 7
		todo = move;
E 7
D 8
		start();
		control = tcp_connect(server, TCP_CONTROL, SOCKOPT_NONE);
		data = tcp_connect(server, TCP_DATA, SOCKOPT_WRITE);
D 7
		(void)sprintf(buf, "%d", bytes);
E 7
I 7
		(void)sprintf(buf, "%d", move);
E 7
		if (write(control, buf, strlen(buf)) != strlen(buf)) {
E 8
I 8
		/* printf("Move %lu MB\n", (unsigned long)(move>>20)); */
		data = tcp_connect(server, TCP_DATA, SOCKOPT_READ);
		(void)sprintf(buf, "%lu", (unsigned long)move);
		if (write(data, buf, strlen(buf)) != strlen(buf)) {
E 8
			perror("control write");
			exit(1);
		}
E 6
D 8
		/*
D 6
		 * On IRIX/Hippi, this slows things down from 89 to 42MB/sec.
E 6
I 6
		 * Disabler message to other side.
E 6
		 */
D 6
		bzero(buf, c);
#endif
	}
E 4
	(void)close(data);
	(void)fprintf(stderr, "Socket bandwidth using %s: ", server);
	while (read(control, buf, 1) == 1) {
		(void)fprintf(stderr, "%c", buf[0]);
		if (buf[0] == '\n') {
E 6
I 6
		if (todo == 0) {
E 6
			exit(0);
		}
D 6
	}
E 6
I 6
		while (todo > 0 && (c = write(data, buf, XFERSIZE)) > 0) {
E 8
I 8
		start(0);
		while (todo > 0 && (c = read(data, buf, XFERSIZE)) > 0) {
E 8
			todo -= c;
E 9
I 9
D 10
	LOOP_FIRST(N, usecs, LONGER);
	todo = move;
	/* printf("Move %lu MB\n", (unsigned long)(move>>20)); */
	data = tcp_connect(server, TCP_DATA, SOCKOPT_READ);
	(void)sprintf(buf, "%lu", (unsigned long)move);
	if (write(data, buf, strlen(buf)) != strlen(buf)) {
		perror("control write");
		exit(1);
E 10
I 10
	start(0);
	transfer(move, server);
	usecs = stop(0,0);
D 11
	if (usecs >= LONGER) {	/* slow friggin machine */
		N = 1;
E 11
I 11
	if (usecs >= LONGER) {	/* must be 10Mbit ether or sloooow box */
		save_n(1);
E 11
		goto out;
E 10
	}
D 10
	while (todo > 0 && (c = read(data, buf, XFERSIZE)) > 0) {
		todo -= c;
E 9
D 8
#if 0
			/*
			 * On IRIX/Hippi, this slows things down from 89 to 42MB/sec.
			 */
E 8
I 8
#ifdef	TOUCH
E 8
D 9
			bzero(buf, c);
E 9
I 9
		bzero(buf, c);
E 9
#endif
D 9
		}
		(void)close(data);
D 8
		c = 0;
		while (read(control, &buf[c++], 1) == 1) {
			if (buf[c-1] == '\n') {
				buf[c] = 0;
				break;
			}
E 8
I 8
		usecs = stop(0,0);
		/*
		 * Flat out refuse to report results for less than 10 sec runs.
		 */
		if (usecs < 10000000) {
			double	adj;
			adj = (10000000 * 1.2)/usecs;
			move *= adj;
		} else {
			break;
E 8
		}
E 9
D 8
		usecs = stop();
		(void)close(control);
D 7
		bytes <<= 2;
E 7
I 7
		move <<= 2;
E 7
	} while (usecs < 10000000);
	(void)fprintf(stderr, "Socket bandwidth using %s: %s", server, buf);
E 8
I 8
	}
I 9
	(void)close(data);
E 10
I 10
D 11
	usecs = LONGER / usecs;
	usecs *= 2;
	move *= usecs;
	LOOP_FIRST(N, usecs, LONGER);
	transfer(move, server);
E 10
	LOOP_LAST(N, usecs, LONGER);
E 11
I 11
	usecs = 5000000 / usecs;
D 16
	move *= usecs * 1.2;
E 16
I 16
	move *= usecs * 1.25;
I 17
	if (move < MINMOVE) move = MINMOVE;
E 17
E 16
	BENCH(transfer(move, server), LONGER);
E 11
E 9
D 10
	(void)fprintf(stderr, "Socket bandwidth using %s: ", server);
E 10
I 10
out:	(void)fprintf(stderr, "Socket bandwidth using %s: ", server);
E 10
D 9
	mb(move);
E 9
I 9
D 11
	mb(move * N);
E 11
I 11
	mb(move * get_n());
E 11
E 9
E 8
E 6
	exit(0);
	/*NOTREACHED*/
}

D 7
last(s)
	char	*s;
{
	while (*s++)
		;
	return (s[-2]);
}

E 7
I 7
void
E 7
I 3
child()
{
	wait(0);
	signal(SIGCHLD, child);
}

I 13
/* ARGSUSED */
E 13
E 3
D 7
server_main()
E 7
I 7
int
server_main(int ac, char **av)
E 7
{
D 8
	int	data, control, newdata, newcontrol;
E 8
I 8
	int	data, newdata;
E 8

	GO_AWAY;

D 3
	data = tcp_server(TCP_DATA);
	control = tcp_server(TCP_CONTROL);
E 3
I 3
	signal(SIGCHLD, child);
D 8
	data = tcp_server(TCP_DATA, SOCKOPT_READ);
	control = tcp_server(TCP_CONTROL, SOCKOPT_NONE);
E 8
I 8
	data = tcp_server(TCP_DATA, SOCKOPT_WRITE);
E 8
E 3

	for ( ;; ) {
D 3
		newcontrol = tcp_accept(control);
		newdata = tcp_accept(data);
		absorb(newcontrol, newdata);
E 3
I 3
D 8
		newcontrol = tcp_accept(control, SOCKOPT_NONE);
		newdata = tcp_accept(data, SOCKOPT_READ);
E 8
I 8
		newdata = tcp_accept(data, SOCKOPT_WRITE);
E 8
		switch (fork()) {
		    case -1:
			perror("fork");
			break;
		    case 0:
D 8
			absorb(newcontrol, newdata);
E 8
I 8
			source(newdata);
E 8
			exit(0);
		    default:
D 8
			close(newcontrol);
E 8
			close(newdata);
			break;
		}
E 3
	}
}

/*
D 8
 * Read the number of bytes to be transfered on the control socket.
 * Read that many bytes on the data socket.
 * Write the performance results on the control socket.
E 8
I 8
 * Read the number of bytes to be transfered.
 * Write that many bytes on the data socket.
E 8
 */
D 7
absorb(control, data)
E 7
I 7
void
D 8
absorb(int control, int data)
E 8
I 8
source(int data)
E 8
E 7
{
D 13
	int	nread, save, nbytes;
E 13
I 13
D 15
	int	nread, nbytes;
E 15
I 15
	int	n, nbytes;
E 15
E 13
D 3
#ifdef	SO_RCVBUF
E 3
D 4
	char	buf[SOCKBUF];
E 4
I 4
D 5
	char	*buf = valloc(SOCKBUF);
E 5
I 5
D 8
	char	*buf = valloc(XFERSIZE);
E 8
E 5
E 4
D 3
	int	sockbuf = SOCKBUF;
E 3

I 4
	if (!buf) {
		perror("valloc");
		exit(1);
	}
E 4
D 3
	while (setsockopt(data, SOL_SOCKET, SO_RCVBUF, &sockbuf, sizeof(int))) {
		sockbuf -= 128;
	}
#endif
E 3
D 5
	bzero(buf, SOCKBUF);
	if (read(control, buf, SOCKBUF) <= 0) {
E 5
I 5
D 14
	bzero(buf, XFERSIZE);
E 14
I 14
	bzero((void*)buf, XFERSIZE);
E 14
D 8
	if (read(control, buf, XFERSIZE) <= 0) {
E 8
I 8
	if (read(data, buf, XFERSIZE) <= 0) {
E 8
E 5
		perror("control nbytes");
		exit(7);
	}
D 13
	nbytes = save = atoi(buf);
E 13
I 13
	nbytes = atoi(buf);
E 13

	/*
	 * A hack to allow turning off the absorb daemon.
	 */
     	if (nbytes == 0) {
		tcp_done(TCP_DATA);
D 8
		tcp_done(TCP_CONTROL);
E 8
I 3
		kill(getppid(), SIGTERM);
E 3
		exit(0);
	}
D 8
	start();
D 4
	while (nbytes > 0 && (nread = read(data, buf, sizeof(buf))) > 0)
E 4
I 4
D 5
	while (nbytes > 0 && (nread = read(data, buf, SOCKBUF)) > 0)
E 5
I 5
	while (nbytes > 0 && (nread = read(data, buf, XFERSIZE)) > 0)
E 8
I 8
D 15
	while (nbytes > 0 && (nread = write(data, buf, XFERSIZE)) > 0) {
E 8
E 5
E 4
		nbytes -= nread;
E 15
I 15
	while (nbytes > 0) {
E 15
D 8
	stop();
	(void)close(2);		/* stderr - timing stats go to stderr */
	(void)dup(control);	/* stderr == control now */
	mb(save);
E 8
I 8
#ifdef	TOUCH
D 14
		bzero(buf, c);
E 14
I 14
D 15
		bzero((void*)buf, c);
E 15
I 15
		touch(buf, XFERSIZE);
E 15
E 14
#endif
I 15
		n = write(data, buf, XFERSIZE);
		if (n <= 0) break;
		nbytes -= n;
E 15
	}
E 8
}

I 12

int
main(int ac, char **av)
{
	if (ac != 2 && ac != 3) {
		fprintf(stderr, "Usage: %s -s OR %s [-]serverhost\n",
		    av[0], av[0]);
		exit(1);
	}
	buf = valloc(XFERSIZE);
D 14
	bzero(buf, XFERSIZE);
E 14
I 14
D 15
	bzero((void*)buf, XFERSIZE);
E 15
I 15
	touch(buf, XFERSIZE);
E 15
E 14
	if (!strcmp(av[1], "-s")) {
		if (fork() == 0) {
			server_main(ac, av);
		}
		exit(0);
	} else {
		client_main(ac, av);
	}
	return(0);
}
E 12
E 2
I 1
E 1
