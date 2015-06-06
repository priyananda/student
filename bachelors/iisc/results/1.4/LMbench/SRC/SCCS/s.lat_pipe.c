h23565
s 00001/00002/00061
d D 1.8 97/06/15 22:38:58 lm 9 8
c lint
cC
cK21742
cSAlpha2.11
e
s 00011/00010/00052
d D 1.7 97/06/13 20:39:50 lm 8 7
c lint
cK22419
e
s 00013/00011/00049
d D 1.6 97/06/12 21:30:06 lm 7 6
c new bench.h macros.
cK21975
cZ-07:00
e
s 00001/00001/00059
d D 1.5 96/11/13 16:09:37 lm 6 5
c timing.c interfaces.
cK24451
e
s 00009/00022/00051
d D 1.4 96/11/11 03:36:51 lm 5 4
c Auto adjusting changes.
cK27376
e
s 00001/00000/00072
d D 1.3 96/11/08 20:00:24 lm 4 3
c gcc -Wall cleanup.
cK35168
cZ-08:00
e
s 00000/00001/00072
d D 1.2 96/05/30 00:33:07 lm 3 2
c no what strings
cK34257
cZ-07:00
e
s 00073/00000/00000
d D 1.1 94/11/18 00:49:48 lm 2 1
c Initial revision
cK36328
e
s 00000/00000/00000
d D 1.0 94/11/18 00:49:47 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK42508
cPsrc/lat_pipe.c
cRb08317879cd9d375
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
 * lat_pipe.c - pipe transaction test
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
#include "bench.h"
E 5

I 8
void
doit(int r, int w)
{
	char	c;

	if (write(w, &c, 1) != 1 || read(r, &c, 1) != 1) {
			perror("read/write on pipe");
			exit(1);
	}
}

E 8
D 5
#define N	2000
#define	TRIES	5

E 5
int
main()
{
D 9
	int	p1[2], p2[2];
D 5
	int	i;
	int	time = 0x7fffffff;
E 5
I 5
	int	i, N, pid;
E 9
I 9
	int	pid, p1[2], p2[2];
E 9
E 5
	char	c;
D 5
	int	pid;
	int	j;
E 5

D 3
	write(2, id, strlen(id));
E 3
     	if (pipe(p1) == -1 || pipe(p2) == -1) {
		perror("pipe");
		exit(1);
	}

	pid = fork();
	if (pid == -1) {
		perror("fork");
		exit(1);
	}
	if (pid > 0) {
		/*
		 * One time around to make sure both processes are started.
		 */
D 7
		if (write(p1[1], &c, 1) != 1 ||
		    read(p2[0], &c, 1) != 1 ||
		    write(p1[1], &c, 1) != 1) {
E 7
I 7
		if (write(p1[1], &c, 1) != 1 || read(p2[0], &c, 1) != 1) {
E 7
			perror("read/write on pipe");
			exit(1);
		}
D 5
		for (j = 0; j < TRIES; ++j) {
			start();
			for (i = 0; i < N; ++i) {
				if (read(p2[0], &c, 1) != 1 ||
				    write(p1[1], &c, 1) != 1) {
					perror("read/write on pipe");
					exit(1);
				}
			}
			i = stop();
			if (time > i) {
				time = i;
			}
E 5
I 5
D 7
		LOOP_FIRST(N, i, ENOUGH);
		if (read(p2[0], &c, 1) != 1 || write(p1[1], &c, 1) != 1) {
			perror("read/write on pipe");
			exit(1);
E 5
		}
D 5
		fprintf(stderr, "Pipe latency: %d microseconds\n", time / N);
E 5
I 5
		LOOP_LAST(N, i, ENOUGH);
D 6
		fprintf(stderr, "Pipe latency: %d microseconds\n", i / N);
E 6
I 6
		micro("Pipe latency", N);
E 7
I 7
		BENCH(doit(p2[0], p1[1]), SHORT);
		micro("Pipe latency", get_n());
E 7
E 6
E 5
		kill(pid, 15);
	} else {
		for ( ;; ) {
			if (read(p1[0], &c, 1) != 1 ||
			    write(p2[1], &c, 1) != 1) {
				perror("read/write on pipe");
				exit(1);
			}
		}
	}
I 4
	return (0);
E 4
}
I 7
D 8

doit(int r, int w)
{
	char	c;

	if (write(w, &c, 1) != 1 || read(r, &c, 1) != 1) {
			perror("read/write on pipe");
			exit(1);
	}
}
E 8
E 7
E 2
I 1
E 1
