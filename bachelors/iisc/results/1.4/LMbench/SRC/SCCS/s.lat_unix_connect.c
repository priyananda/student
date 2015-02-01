h18804
s 00000/00001/00083
d D 1.2 98/06/29 23:50:59 lm 3 2
c lint
cC
cK53896
cSAlpha2.11
e
s 00084/00000/00000
d D 1.1 97/10/19 23:50:16 lm 2 1
c Initial revision
cK54897
e
s 00000/00000/00000
d D 1.0 97/10/19 23:50:15 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK47898
cPsrc/lat_unix_connect.c
cR993911110514ea9
cV4
cX0x21
cZ-07:00
e
u
U
f e 0
f x 0x21
t
lmbench lat_unix_connect.c
T
I 2
/*
 * lat_unix_connect.c - simple UNIX connection latency test
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
#include "bench.h"

void	server_main(int ac, char **av);
void	client_main(int ac, char **av);

void
doit()
{
	int	sock = unix_connect("/tmp/af_unix");
	close(sock);
}

int
main(int ac, char **av)
{
	if (ac > 1 && !strcmp(av[1], "-s")) {
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

void
client_main(int ac, char **av)
{
D 3
	int     sock;
E 3
	char	buf[256];

	if (ac != 1) {
		fprintf(stderr, "usage: %s\n", av[0]);
		exit(1);
	}

	BENCH(doit(), 100000);
	sprintf(buf, "UNIX connection cost ");
	micro(buf, get_n());
	exit(0);
	/* NOTREACHED */
}

void
server_main(int ac, char **av)
{
	int     newsock, sock;
	char	c;

	if (ac != 2) {
		fprintf(stderr, "usage: %s -s\n", av[0]);
		exit(1);
	}
	GO_AWAY;
	sock = unix_server("/tmp/af_unix");
	for (;;) {
		newsock = unix_accept(sock);
		c = 0;
		read(newsock, &c, 1);
		if (c && c == '0') {
			unix_done(sock, "/tmp/af_unix");
			exit(0);
		}
		close(newsock);
	}
	/* NOTREACHED */
}
E 2
I 1
E 1
