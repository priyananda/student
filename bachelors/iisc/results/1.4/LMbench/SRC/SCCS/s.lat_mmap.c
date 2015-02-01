h37867
s 00001/00001/00083
d D 1.11 97/06/15 22:38:58 lm 12 11
c lint
cC
cK10049
cSAlpha2.11
e
s 00028/00027/00056
d D 1.10 97/06/13 20:39:50 lm 11 10
c lint
cK09819
e
s 00045/00021/00038
d D 1.9 97/06/12 21:30:06 lm 10 9
c new bench.h macros.
cK09375
cZ-07:00
e
s 00001/00001/00058
d D 1.8 96/11/13 16:09:37 lm 9 8
c timing.c interfaces.
cK47751
e
s 00014/00020/00045
d D 1.7 96/11/11 03:36:51 lm 8 7
c Auto adjusting changes.
cK50131
e
s 00004/00015/00061
d D 1.6 96/11/08 20:00:09 lm 7 6
c gcc -Wall cleanup & new timing.c integration.
cK51089
cZ-08:00
e
s 00000/00001/00076
d D 1.5 96/05/30 00:33:07 lm 6 5
c no what strings
cK61854
e
s 00004/00000/00073
d D 1.4 95/10/25 18:03:42 lm 5 4
c MAP_FILE for FreeBSD.
cK63925
cZ-07:00
e
s 00000/00001/00073
d D 1.3 95/03/10 18:22:37 lm 4 3
c lint
cK57154
e
s 00001/00001/00073
d D 1.2 95/02/14 12:34:34 lm 3 2
c linux wants readonly fd's for mmap MAP_READ.
cK57749
e
s 00074/00000/00000
d D 1.1 94/11/18 00:49:48 lm 2 1
c Initial revision
cK57751
e
s 00000/00000/00000
d D 1.0 94/11/18 00:49:47 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK19537
cPsrc/lat_mmap.c
cRe3044628e9a37e7
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
 * lat_mmap.c - time how fast a mapping can be made and broken down
 *
 * Usage: mmap size file
 *
 * XXX - If an implementation did lazy address space mapping, this test
 * will make that system look very good.  I haven't heard of such a system.
 *
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id$\n";

D 8
#include "timing.c"

E 8
I 8
D 10
#include "timing.h"
E 10
#include "bench.h"
E 8
D 10
#include <sys/stat.h>
#include <sys/mman.h>
I 7
#include <fcntl.h>
E 10
E 7

I 10
#define	PSIZE	(16<<10)
#define	N	10
#define	STRIDE	(10*PSIZE)
#define	MINSIZE	(STRIDE*2)

E 10
#define	CHK(x)	if ((x) == -1) { perror("x"); exit(1); }
D 8
#ifndef	N
#define	N	5000
#endif
E 8

D 7
main(ac, av)
	char **av;
E 7
I 7
D 11
int
main(int ac, char **av)
E 7
{
D 8
	int fd;
	int i;
	char *where;
D 4
	int *p;
E 4
	int size;
	struct stat sbuf;
E 8
I 8
D 10
	int	fd, i, N;
	char	*where;
E 10
I 10
	int	fd;
E 10
	int	size;
D 10
	struct	stat sbuf;
E 10
I 10
	int	random = 0;
	char	*prog = av[0];
E 10
E 8

D 6
	write(2, id, strlen(id));
E 6
D 10
	if (ac != 3) {
		fprintf(stderr, "usage: %s size file\n", av[0]);
E 10
I 10
	if (ac != 3 && ac != 4) {
		fprintf(stderr, "usage: %s [-r] size file\n", prog);
E 10
		exit(1);
	}
I 10
	if (strcmp("-r", av[1]) == 0) {
		random = 1;
		ac--, av++;
	}
E 10
D 7
	size = atoi(av[1]);
	if ((last(av[1]) == 'k') || (last(av[1]) == 'K'))
		size *= 1024;
	if ((last(av[1]) == 'm') || (last(av[1]) == 'M'))
		size *= (1024 * 1024);
E 7
I 7
	size = bytes(av[1]);
E 7
D 3
	CHK(fd = open(av[2], 2));
E 3
I 3
D 10
	CHK(fd = open(av[2], 0));
E 3
	CHK(fstat(fd, &sbuf));
	if (sbuf.st_size < size) {
		fprintf(stderr, "%s: file %s is not as big as size %d\n",
		    av[0], av[2], size);
		exit(1);
E 10
I 10
	if (size < MINSIZE) {	
		return (1);
E 10
	}
D 8
	start();
	for (i = 0; i < N; ++i) {
E 8
I 8
D 10
	LOOP_FIRST(N, i, ENOUGH);
E 10
I 10
	CHK(fd = open(av[2], O_CREAT|O_RDWR, 0666));
	CHK(ftruncate(fd, size));
	BENCH(mapit(fd, size, random), 0);
	micromb(size, get_n());
	exit(0);
}

E 11
/*
 * This alg due to Linus.  The goal is to have both sparse and full
 * mappings reported.
 */
I 11
void
E 11
mapit(int fd, int size, int random)
{
	char	*p, *where, *end;
	char	c = size & 0xff;

E 10
E 8
I 5
#ifdef	MAP_FILE
D 8
		where = mmap(0, size, PROT_READ, MAP_FILE|MAP_SHARED, fd, 0);
E 8
I 8
D 10
	where = mmap(0, size, PROT_READ, MAP_FILE|MAP_SHARED, fd, 0);
E 10
I 10
	where = mmap(0, size, PROT_READ|PROT_WRITE, MAP_FILE|MAP_SHARED, fd, 0);
E 10
E 8
#else
E 5
D 8
		where = mmap(0, size, PROT_READ, MAP_SHARED, fd, 0);
E 8
I 8
D 10
	where = mmap(0, size, PROT_READ, MAP_SHARED, fd, 0);
E 10
I 10
	where = mmap(0, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
E 10
E 8
I 5
#endif
E 5
D 8
		if ((int)where == -1) {
			perror("mmap");
			exit(1);
		}
		munmap(where, size);
E 8
I 8
	if ((int)where == -1) {
		perror("mmap");
		exit(1);
E 8
	}
I 10
	if (random) {
		end = where + size;
		for (p = where; p < end; p += STRIDE) {
			*p = c;
		}
	} else {
		end = where + (size / N);
		for (p = where; p < end; p += PSIZE) {
			*p = c;
		}
	}
E 10
D 8
	i = stop();
E 8
I 8
	munmap(where, size);
D 10
	LOOP_LAST(N, i, ENOUGH);
E 8
D 9
	fprintf(stderr, "%.02f %d\n", size/(1024*1024.), i / N);
E 9
I 9
	micromb(size, N);
E 9
	exit(0);
E 10
}
I 11

int
main(int ac, char **av)
{
	int	fd;
	int	size;
	int	random = 0;
	char	*prog = av[0];

	if (ac != 3 && ac != 4) {
		fprintf(stderr, "usage: %s [-r] size file\n", prog);
		exit(1);
	}
	if (strcmp("-r", av[1]) == 0) {
		random = 1;
		ac--, av++;
	}
	size = bytes(av[1]);
	if (size < MINSIZE) {	
		return (1);
	}
	CHK(fd = open(av[2], O_CREAT|O_RDWR, 0666));
	CHK(ftruncate(fd, size));
	BENCH(mapit(fd, size, random), 0);
	micromb(size, get_n());
D 12
	exit(0);
E 12
I 12
	return(0);
E 12
}
E 11
D 7

last(s)
	char	*s;
{
	while (*s++)
		;
	return (s[-2]);
}
E 7
E 2
I 1
E 1
