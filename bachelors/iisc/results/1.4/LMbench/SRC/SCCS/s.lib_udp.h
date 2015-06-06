h12241
s 00002/00001/00013
d D 1.3 00/09/24 11:48:57 lm 4 3
c No protos if we aren't using the portmapper.
cC
cHopenbsd.bitmover.com
cK40423
e
s 00001/00000/00013
d D 1.2 97/06/15 22:38:58 lm 3 2
c lint
cC
cK38166
cSAlpha2.11
cZ-07:00
e
s 00013/00000/00000
d D 1.1 96/11/13 16:15:00 lm 2 1
c Initial revision
cK36460
e
s 00000/00000/00000
d D 1.0 96/11/13 16:14:59 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK51303
cPsrc/lib_udp.h
cR54591f07d0325bfe
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
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<netdb.h>
#include	<arpa/inet.h>

int	udp_server(u_long prog, int rdwr);
void	udp_done(int prog);
int	udp_connect(char *host, u_long prog, int rdwr);
void	sock_optimize(int sock, int rdwr);
I 3
int	sockport(int);
I 4
#ifndef	NO_PORTMAPPER
E 4
E 3
bool_t	pmap_set(u_long prognum, u_long versnum, u_long protocol, u_short port);
bool_t	pmap_unset(u_long prognum, u_long versnum);
D 4

E 4
I 4
#endif
E 4
E 2
I 1
E 1
