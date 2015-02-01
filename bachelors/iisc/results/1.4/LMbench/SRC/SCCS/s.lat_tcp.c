h49754
s 00001/00001/00136
d D 1.7 97/06/15 22:38:58 lm 8 7
c lint
cC
cK42655
cSAlpha2.11
e
s 00006/00013/00131
d D 1.6 97/06/12 21:30:06 lm 7 6
c new bench.h macros.
cK42425
cZ-07:00
e
s 00008/00012/00136
d D 1.5 96/11/11 03:36:51 lm 6 5
c Auto adjusting changes.
cK55355
e
s 00021/00009/00127
d D 1.4 96/11/08 20:03:43 lm 5 4
c gcc -Wall cleanup.
cK55818
cZ-08:00
e
s 00000/00001/00136
d D 1.3 96/05/30 00:33:07 lm 4 3
c no what strings
cK34860
cZ-07:00
e
s 00024/00006/00113
d D 1.2 95/03/10 18:25:31 lm 3 2
c lint, sockopt, & make it N way capable.
cK36931
e
s 00119/00000/00000
d D 1.1 94/11/18 00:49:48 lm 2 1
c Initial revision
cK19319
e
s 00000/00000/00000
d D 1.0 94/11/18 00:49:47 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK17274
cPsrc/lat_tcp.c
cR403c1dd2be70f174
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
 * tcp_xact.c - simple TCP transaction latency test
 *
 * Three programs in one -
 *	server usage:	tcp_xact -s
 *	client usage:	tcp_xact hostname
 *	shutdown:	tcp_xact -hostname
 *
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id$\n";
I 5

E 5
D 6
#include "bench.h"
#include "lib_tcp.c"
#include "timing.c"
E 6
I 5
D 7
#include <sys/types.h>
#include <sys/wait.h>
I 6
#include "timing.h"
E 7
#include "bench.h"
D 7
#include "lib_tcp.h"
E 7
E 6

E 5
D 6
#define	N	5000

E 6
D 5
main(ac, av)
	char  **av;
E 5
I 5
void	client_main(int ac, char **av);
void	doserver(int sock);
D 7
void	doclient(int sock, char *host);
E 7
I 7
void	doclient(int sock);
E 7
void	server_main(int ac, char **av);
void	doserver(int sock);

int
main(int ac, char **av)
E 5
{
D 4
	write(2, id, strlen(id));
E 4
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
D 8
	exit(0);
E 8
I 8
	return(0);
E 8
}

D 5
client_main(ac, av)
	char  **av;
E 5
I 5
void
client_main(int ac, char **av)
E 5
{
D 3
	int     newsock, sock;
E 3
I 3
	int     sock;
E 3
	char	*server;
I 7
	char	buf[100];
E 7

	if (ac != 2) {
		fprintf(stderr, "usage: %s host\n", av[0]);
		exit(1);
	}
	server = av[1][0] == '-' ? &av[1][1] : av[1];
D 3
	sock = tcp_connect(server, TCP_XACT);
E 3
I 3
	sock = tcp_connect(server, TCP_XACT, SOCKOPT_NONE);
E 3

	/*
	 * Stop server code.
	 */
	if (av[1][0] == '-') {
		close(sock);
		exit(0);
	}

D 7
	doclient(sock, server);
E 7
I 7
	BENCH(doclient(sock), MEDIUM);
	sprintf(buf, "TCP latency using %s", av[1]);
	micro(buf, get_n());
E 7
	exit(0);
	/* NOTREACHED */
}

D 5
doclient(sock, host)
	char	*host;
E 5
I 5
void
D 7
doclient(int sock, char *host)
E 7
I 7
doclient(int sock)
E 7
E 5
{
	char    c;
D 6
	int     i;
E 6
I 6
D 7
	int     i, N;
E 6
	char	buf[100];
E 7

D 6
	start();
	for (i = 0; i < N; ++i) {
		write(sock, &c, 1);
		read(sock, &c, 1);
	}
	stop();
E 6
I 6
D 7
	LOOP_FIRST(N, i, MEDIUM);
E 7
	write(sock, &c, 1);
	read(sock, &c, 1);
D 7
	LOOP_LAST(N, i, MEDIUM);
E 6
	sprintf(buf, "TCP latency using %s", host);
	micro(buf, N);
E 7
}

I 5
void
E 5
I 3
child()
{
	wait(0);
	signal(SIGCHLD, child);
}

E 3
D 5
server_main(ac, av)
	char  **av;
E 5
I 5
void
server_main(int ac, char **av)
E 5
{
D 3
	int     server, newsock, sock;
E 3
I 3
	int     newsock, sock;
E 3

	if (ac != 2) {
		fprintf(stderr, "usage: %s -s\n", av[0]);
		exit(1);
	}
	GO_AWAY;
D 3
	sock = tcp_server(TCP_XACT);
E 3
I 3
	signal(SIGCHLD, child);
	sock = tcp_server(TCP_XACT, SOCKOPT_NONE);
E 3
	for (;;) {
D 3
		newsock = tcp_accept(sock);
		doserver(newsock);
E 3
I 3
		newsock = tcp_accept(sock, SOCKOPT_NONE);
		switch (fork()) {
		    case -1:
			perror("fork");
			break;
		    case 0:
			doserver(newsock);
			exit(0);
		    default:
			close(newsock);
			break;
		}
E 3
	}
	/* NOTREACHED */
}

D 5
doserver(sock)
E 5
I 5
void
doserver(int sock)
E 5
{
	char    c;
	int	n = 0;

	while (read(sock, &c, 1) == 1) {
		write(sock, &c, 1);
		n++;
	}

	/*
	 * A connection with no data means shut down.
	 */
	if (n == 0) {
		tcp_done(TCP_XACT);
I 3
		kill(getppid(), SIGTERM);
E 3
		exit(0);
	}
}
E 2
I 1
E 1
