h59420
s 00001/00001/00059
d D 1.6 97/06/15 22:38:58 lm 7 6
c lint
cC
cK23557
cSAlpha2.11
e
s 00003/00008/00057
d D 1.5 97/06/12 21:30:06 lm 6 5
c new bench.h macros.
cK23327
cZ-07:00
e
s 00007/00012/00058
d D 1.4 96/11/11 03:36:51 lm 5 4
c Auto adjusting changes.
cK29884
e
s 00012/00006/00058
d D 1.3 96/11/08 20:04:09 lm 4 3
c gcc -Wall cleanup.
cK33166
cZ-08:00
e
s 00000/00001/00064
d D 1.2 96/05/30 00:33:07 lm 3 2
c no what strings
cK27161
e
s 00065/00000/00000
d D 1.1 96/05/22 00:33:03 lm 2 1
c Initial revision
cK29232
e
s 00000/00000/00000
d D 1.0 96/05/22 00:33:02 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK07499
cPsrc/lat_unix.c
cR60b40b303e5dd5e0
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
 * tcp_xact.c - simple TCP transaction latency test
 *
 * Three programs in one -
 *	server usage:	tcp_xact -s
 *	client usage:	tcp_xact hostname
D 4
 *	shutdown:	tcp_xact -hostname
E 4
I 4
 *	shutwn:	tcp_xact -hostname
E 4
 *
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id$\n";
I 5
D 6
#include "timing.h"
E 6
E 5
#include "bench.h"
D 5
#include "timing.c"
E 5
D 6
#include <sys/socket.h>
E 6
D 5
#define	N	10000
E 5

D 4
main()
E 4
I 4
void	client(int sock);
void	server(int sock);

int
main(int ac, char **av)
E 4
{
	int	sv[2];

D 3
	write(2, id, strlen(id));
E 3
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) == -1) {
		perror("socketpair");
	}
	if (fork() == 0) {
D 4
		doclient(sv[1]);
E 4
I 4
D 6
		client(sv[1]);
E 6
I 6
		BENCH(client(sv[1]), MEDIUM);
		micro("AF_UNIX sock stream latency", get_n());
		kill(getppid(), SIGTERM);
E 6
E 4
	} else {
D 4
		doserver(sv[0]);
E 4
I 4
		server(sv[0]);
E 4
	}
D 7
	exit(0);
E 7
I 7
	return(0);
E 7
}

D 4
doclient(int sock)
E 4
I 4
void
client(int sock)
E 4
{
	char    c;
D 5
	int     i;
	char	buf[100];
E 5
I 5
D 6
	int     i, N;
E 6
E 5

D 5
	start();
	for (i = 0; i < N; ++i) {
		write(sock, &c, 1);
		read(sock, &c, 1);
	}
	stop();
	sprintf(buf, "AF_UNIX sock stream latency");
	micro(buf, N);
E 5
I 5
D 6
	LOOP_FIRST(N, i, ENOUGH);
E 6
	write(sock, &c, 1);
	read(sock, &c, 1);
D 6
	LOOP_LAST(N, i, ENOUGH);
	micro("AF_UNIX sock stream latency", N);
E 5
	kill(getppid(), SIGTERM);
E 6
}

D 4
doserver(sock)
E 4
I 4
void
server(int sock)
E 4
{
	char    c;
	int	n = 0;
	void	exit();

	signal(SIGTERM, exit);
	while (read(sock, &c, 1) == 1) {
		write(sock, &c, 1);
		n++;
	}
}
E 2
I 1
E 1
