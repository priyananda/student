h41102
s 00001/00001/00105
d D 1.13 98/07/30 22:04:11 lm 14 13
c XXX - a bandaid hack for running out of sockets.
cC
cK28543
cSAlpha2.11
e
s 00000/00001/00106
d D 1.12 97/06/15 22:38:58 lm 13 12
c lint
cK28585
e
s 00001/00000/00106
d D 1.11 97/06/14 12:20:39 lm 12 11
c it wasn't cleaning up after itself.
cK29262
e
s 00007/00006/00099
d D 1.10 97/06/13 20:39:50 lm 11 10
c lint
cK27393
e
s 00009/00007/00096
d D 1.9 97/06/12 21:30:06 lm 10 9
c new bench.h macros.
cK26949
e
s 00001/00002/00102
d D 1.8 97/04/23 22:40:47 lm 9 8
c ?
cK24081
cZ-07:00
e
s 00003/00003/00101
d D 1.7 96/11/13 16:09:37 lm 8 7
c timing.c interfaces.
cK25784
e
s 00011/00019/00093
d D 1.6 96/11/11 03:36:51 lm 7 6
c Auto adjusting changes.
cK26000
e
s 00009/00006/00103
d D 1.5 96/11/08 19:58:39 lm 6 5
c gcc -Wall cleanup.
cK34823
cZ-08:00
e
s 00002/00004/00107
d D 1.4 96/05/30 00:33:07 lm 5 4
c no what strings
cK27190
e
s 00001/00001/00110
d D 1.3 95/09/25 22:42:08 lm 4 3
c Add a sleep so that the other side is finished.
c Get rid of the write(), it added needless overhead.
cK36722
cZ-07:00
e
s 00004/00004/00107
d D 1.2 95/03/10 18:25:01 lm 3 2
c lint & sockopt.
cK34180
e
s 00111/00000/00000
d D 1.1 94/11/18 00:49:48 lm 2 1
c Initial revision
cK30092
e
s 00000/00000/00000
d D 1.0 94/11/18 00:49:47 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK14665
cPsrc/lat_connect.c
cR86372c4fec5b6e34
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
 * lat_connect.c - simple TCP connection latency test
 *
 * Three programs in one -
 *	server usage:	lat_connect -s
 *	client usage:	lat_connect hostname [N]
 *	shutdown:	lat_connect -hostname
 *
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id$\n";
D 7
#include "bench.h"
E 7
D 9
#define	NO_SETSOCKOPT
#include "lib_tcp.c"
E 9
D 7
#include "timing.c"
E 7
I 7
D 10
#include "timing.h"
E 10
#include "bench.h"
I 9
D 10
#include "lib_tcp.h"
E 10
E 9
E 7

D 7
/*
 * A small N is used because the connections hang around even after the
D 5
 * socket has been closed.  XXX - is this a TCP (implementation) bug?
E 5
I 5
 * socket has been closed.  
E 5
 */
D 5
#define	N	20
E 5
I 5
#define	N	100
E 5

E 7
D 6
main(ac, av)
	char  **av;
E 6
I 6
void	server_main(int ac, char **av);
void	client_main(int ac, char **av);

I 11
void
doit(char *server)
{
	int	sock = tcp_connect(server, TCP_CONNECT, SOCKOPT_NONE);
	close(sock);
}

E 11
int
main(int ac, char **av)
E 6
{
D 5
	write(2, id, strlen(id));
E 5
	if (ac != 2) {
		fprintf(stderr, "Usage: %s -s OR %s [-]serverhost\n",
		    av[0], av[0]);
		exit(1);
	}
	if (!strcmp(av[1], "-s")) {
		if (fork() == 0) {
			server_main(ac, av);
		}
		exit(0);
	} else {
		client_main(ac, av);
	}
	exit(0);
	/* NOTREACHED */
}

I 10
D 11
doit(char *server)
{
	int	sock = tcp_connect(server, TCP_CONNECT, SOCKOPT_NONE);
	close(sock);
}

E 11
E 10
D 6
client_main(ac, av)
	char  **av;
E 6
I 6
void
client_main(int ac, char **av)
E 6
{
	int     sock;
	char	*server;
D 7
	int	i, tmp, cost;
E 7
I 7
D 13
	int	i, N;
E 13
I 8
	char	buf[256];
E 8
E 7

	if (ac != 2) {
		fprintf(stderr, "usage: %s host\n", av[0]);
		exit(1);
	}
	server = av[1][0] == '-' ? &av[1][1] : av[1];

	/*
	 * Stop server code.
	 */
	if (av[1][0] == '-') {
D 3
		sock = tcp_connect(server, TCP_CONNECT);
E 3
I 3
		sock = tcp_connect(server, TCP_CONNECT, SOCKOPT_NONE);
E 3
		write(sock, "0", 1);
		close(sock);
		exit(0);
		/* NOTREACHED */
	}

D 7
	cost = 0x7fffffff;
	for (i = 0; i < N; ++i) {
		start();
D 3
		sock = tcp_connect(server, TCP_CONNECT);
E 3
I 3
		sock = tcp_connect(server, TCP_CONNECT, SOCKOPT_NONE);
E 3
		tmp = stop();
		if (tmp < cost)
			cost = tmp;
D 4
		write(sock, "1", 1);
E 4
		close(sock);
I 4
D 5
		sleep(1);	/* give the sockets time to go away */
E 5
E 4
	}
E 7
I 7
	/*
	 * We don't want more than a few of these, they stack up in time wait.
I 10
	 * XXX - report an error if the clock is too shitty?
E 10
	 */
D 10
	LOOP_FIRST(N, i, 200000);
	sock = tcp_connect(server, TCP_CONNECT, SOCKOPT_NONE);
	close(sock);
	LOOP_LAST(N, i, 200000);
E 10
I 10
D 14
	BENCH(doit(server), 100000);
E 14
I 14
	BENCH(doit(server), 25000);
E 14
E 10
E 7
D 8
	fprintf(stderr, "TCP/IP connection cost to %s: %d microseconds\n", 
D 7
	    server, cost);
E 7
I 7
	    server, i/N);
E 7

E 8
I 8
	sprintf(buf, "TCP/IP connection cost to %s", server);
D 10
	micro(buf, N);
E 10
I 10
	micro(buf, get_n());
E 10
E 8
	exit(0);
	/* NOTREACHED */
}

D 6
server_main(ac, av)
	char  **av;
E 6
I 6
void
server_main(int ac, char **av)
E 6
{
	int     newsock, sock;
	char	c;

	if (ac != 2) {
		fprintf(stderr, "usage: %s -s\n", av[0]);
		exit(1);
	}
	GO_AWAY;
D 3
	sock = tcp_server(TCP_CONNECT);
E 3
I 3
	sock = tcp_server(TCP_CONNECT, SOCKOPT_NONE);
E 3
	for (;;) {
D 3
		newsock = tcp_accept(sock);
E 3
I 3
		newsock = tcp_accept(sock, SOCKOPT_NONE);
E 3
		c = 0;
		read(newsock, &c, 1);
		if (c && c == '0') {
I 12
			tcp_done(TCP_CONNECT);
E 12
			exit(0);
		}
		close(newsock);
	}
	/* NOTREACHED */
}
E 2
I 1
E 1
