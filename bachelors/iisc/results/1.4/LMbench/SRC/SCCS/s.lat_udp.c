h46150
s 00008/00000/00127
d D 1.11 00/08/15 15:32:50 lm 12 11
c Add a timeout; HPUX seems to drop packets.
cC
cHhp.bitmover.com
cK08351
e
s 00005/00005/00122
d D 1.10 97/06/15 22:38:58 lm 11 10
c lint
cC
cK65433
cSAlpha2.11
e
s 00017/00015/00110
d D 1.9 97/06/13 20:39:50 lm 10 9
c lint
cK65293
e
s 00011/00010/00114
d D 1.8 97/06/12 21:30:06 lm 9 8
c new bench.h macros.
cK64839
cZ-07:00
e
s 00003/00001/00121
d D 1.7 96/11/13 16:09:37 lm 8 7
c timing.c interfaces.
cK00108
e
s 00016/00025/00106
d D 1.6 96/11/11 03:36:51 lm 7 6
c Auto adjusting changes.
cK00167
e
s 00013/00008/00118
d D 1.5 96/11/08 20:04:05 lm 6 5
c gcc -Wall cleanup.
cK08729
cZ-08:00
e
s 00000/00001/00126
d D 1.4 96/05/30 00:33:07 lm 5 4
c no what strings
cK61856
e
s 00015/00004/00112
d D 1.3 96/05/21 23:15:50 lm 4 3
c network byte order on the sequence number. Thanks Davem.
cK63927
cZ-07:00
e
s 00002/00002/00114
d D 1.2 95/03/10 18:15:39 lm 3 2
c sockopt stuff.
cK47871
e
s 00116/00000/00000
d D 1.1 94/11/18 00:49:48 lm 2 1
c Initial revision
cK45827
e
s 00000/00000/00000
d D 1.0 94/11/18 00:49:47 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK24062
cPsrc/lat_udp.c
cR7459a472444854ce
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
 * udp_xact.c - simple UDP transaction latency test
 *
 * Three programs in one -
 *	server usage:	udp_xact -s
 *	client usage:	udp_xact hostname
 *	shutdown:	udp_xact -hostname
 *
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id$\n";
I 7
D 9
#include "timing.h"
E 9
E 7
#include "bench.h"
D 7
#include "lib_udp.c"
#include "timing.c"
E 7
I 7
D 9
#include "lib_udp.h"
E 9
E 7

D 6
main(ac, av)
	char  **av;
E 6
I 6
void	client_main(int ac, char **av);
void	server_main(int ac, char **av);

I 12
void
timeout()
{
	fprintf(stderr, "Recv timed out\n");
	exit(1);
}
E 12
I 10

void
doit(int sock, int seq)
{
	int net = htonl(seq);
	int ret;

	if (send(sock, &net, sizeof(net), 0) != sizeof(net)) {
		perror("lat_udp client: send failed");
		exit(5);
	}
	if (recv(sock, &ret, sizeof(ret), 0) != sizeof(ret)) {
		perror("lat_udp client: recv failed");
		exit(5);
	}
}

E 10
int
main(int ac, char **av)
E 6
{
D 5
	write(2, id, strlen(id));
E 5
I 4
	if (sizeof(int) != 4) {
		fprintf(stderr, "lat_udp: Wrong sequence size\n");
D 11
		exit(1);
E 11
I 11
		return(1);
E 11
	}
E 4
	if (ac != 2 && ac != 3) {
		fprintf(stderr, "Usage: %s -s OR %s [-]serverhost [proto]\n",
		    av[0], av[0]);
D 11
		exit(1);
E 11
I 11
		return(1);
E 11
	}
	if (!strcmp(av[1], "-s")) {
		if (fork() == 0) {
			server_main(ac, av);
		}
D 11
		exit(0);
E 11
I 11
		return(0);
E 11
	} else {
		client_main(ac, av);
	}
D 11
	exit(0);
E 11
I 11
	return(0);
E 11
}

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
D 9
	int     seq = 0;
E 9
I 9
	int     seq = -1;
E 9
D 7
	int     ret;
	int     n = 0;
	char    buf[200];
E 7
I 7
D 11
	int     i, N, net, ret;
E 11
E 7
	char   *server;
I 8
	char	buf[256];
E 8

	if (ac != 2) {
		fprintf(stderr, "Usage: %s hostname\n", av[0]);
		exit(1);
	}

	server = av[1][0] == '-' ? &av[1][1] : av[1];
D 3
	sock = udp_connect(server, UDP_XACT);
E 3
I 3
	sock = udp_connect(server, UDP_XACT, SOCKOPT_NONE);
E 3

	/*
	 * Stop server code.
	 */
	if (av[1][0] == '-') {
		while (seq-- > -5) {
D 4
			(void) send(sock, &seq, sizeof(seq), 0);
E 4
I 4
			int	net = htonl(seq);

			(void) send(sock, &net, sizeof(net), 0);
E 4
		}
		exit(0);
	}
I 12
	signal(SIGALRM, timeout);
	alarm(15);
E 12
I 9
	BENCH(doit(sock, ++seq), MEDIUM);
	sprintf(buf, "UDP latency using %s", server);
	micro(buf, get_n());
	exit(0);
}
E 9

I 11
/* ARGSUSED */
E 11
D 7
	start();
	while (seq++ < 5000) {
D 4
		if (send(sock, &seq, sizeof(seq), 0) != sizeof(seq)) {
E 4
I 4
		int	net = htonl(seq);

		if (send(sock, &net, sizeof(net), 0) != sizeof(net)) {
E 4
			perror("lat_udp client: send failed");
			exit(5);
		}
		if (recv(sock, &ret, sizeof(ret), 0) != sizeof(ret)) {
			perror("lat_udp client: recv failed");
			exit(5);
		}
I 4
		ret = ntohl(ret);
E 4
		if (seq == ret) {
			n++;
		}
E 7
I 7
D 9
	LOOP_FIRST(N, i, MEDIUM);
	net = htonl(seq);
	seq++;
E 9
I 9
D 10
doit(int sock, int seq)
{
	int net = htonl(seq);
	int ret;

E 9
	if (send(sock, &net, sizeof(net), 0) != sizeof(net)) {
		perror("lat_udp client: send failed");
		exit(5);
E 7
	}
D 7
	stop();
	sprintf(buf, "UDP latency using %s", server);
	micro(buf, n);
E 7
I 7
	if (recv(sock, &ret, sizeof(ret), 0) != sizeof(ret)) {
		perror("lat_udp client: recv failed");
		exit(5);
	}
D 9
	LOOP_LAST(N, i, MEDIUM);
D 8
	fprintf(stderr, "UDP latency using %s: %d microseconds\n", server, i/N);
E 8
I 8
	sprintf(buf, "UDP latency using %s", server);
	micro(buf, N);
E 8
	exit(0);
E 9
E 7
}

E 10
D 6
server_main(ac, av)
	char  **av;
E 6
I 6
void
server_main(int ac, char **av)
E 6
{
D 4
	int     sock, sent, namelen, seq = 0;
E 4
I 4
	int     net, sock, sent, namelen, seq = 0;
E 4
	struct sockaddr_in it;

	GO_AWAY;

D 3
	sock = udp_server(UDP_XACT);
E 3
I 3
	sock = udp_server(UDP_XACT, SOCKOPT_NONE);
E 3

	while (1) {
		namelen = sizeof(it);
D 6
		if (recvfrom(sock, &sent, sizeof(sent), 0, &it, &namelen) < 0) {
E 6
I 6
		if (recvfrom(sock, (void*)&sent, sizeof(sent), 0, 
		    (struct sockaddr*)&it, &namelen) < 0) {
E 6
			fprintf(stderr, "lat_udp server: recvfrom: got wrong size\n");
			exit(9);
		}
I 4
		sent = ntohl(sent);
E 4
		if (sent < 0) {
			udp_done(UDP_XACT);
			exit(0);
		}
		if (sent != ++seq) {
D 7
printf("lat_udp server: wanted %d, got %d, resyncing\n", seq, sent);	/**/
E 7
			seq = sent;
		}
D 4
		if (sendto(sock, &seq, sizeof(seq), 0, &it, sizeof(it)) < 0) {
E 4
I 4
		net = htonl(seq);
D 6
		if (sendto(sock, &net, sizeof(net), 0, &it, sizeof(it)) < 0) {
E 6
I 6
		if (sendto(sock, (void*)&net, sizeof(net), 0, 
		    (struct sockaddr*)&it, sizeof(it)) < 0) {
E 6
E 4
			perror("lat_udp sendto");
			exit(9);
		}
	}
}
E 2
I 1
E 1
