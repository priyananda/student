h52407
s 00001/00001/00070
d D 1.12 97/10/31 18:06:23 lm 13 12
c use_result -> use_int/pointer
cC
cK61244
cSAlpha2.11
cZ-08:00
e
s 00001/00001/00070
d D 1.11 97/06/15 22:38:58 lm 12 11
c lint
cK61584
e
s 00001/00002/00070
d D 1.10 97/06/13 20:24:14 lm 11 10
c typo - sgi's cc caught it.
cK61354
e
s 00017/00021/00055
d D 1.9 97/06/12 21:30:06 lm 10 9
c new bench.h macros.
cK61956
cZ-07:00
e
s 00008/00008/00068
d D 1.8 96/11/11 03:36:51 lm 9 8
c Auto adjusting changes.
cK00301
e
s 00007/00004/00069
d D 1.7 96/11/08 20:00:16 lm 8 7
c gcc -Wall cleanup.
cK00115
cZ-08:00
e
s 00000/00001/00073
d D 1.6 96/05/30 00:33:07 lm 7 6
c no what strings
cK59305
cZ-07:00
e
s 00002/00004/00072
d D 1.5 95/11/07 17:39:50 lm 6 5
c *** empty log message ***
cK61376
e
s 00000/00002/00076
d D 1.4 95/03/10 18:26:03 lm 5 4
c lint.
cK64277
e
s 00004/00000/00074
d D 1.3 94/11/29 11:52:20 lm 4 3
c changes from Alain Durand for NetBSD
cK00220
e
s 00003/00003/00071
d D 1.2 94/11/23 17:59:11 lm 3 2
c change to 256K.
cK60736
e
s 00074/00000/00000
d D 1.1 94/11/18 00:49:48 lm 2 1
c Initial revision
cK60570
e
s 00000/00000/00000
d D 1.0 94/11/18 00:49:47 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK33722
cPsrc/lat_pagefault.c
cR21040cf28d60fb56
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
 * lat_pagefault.c - time a page fault in
 *
 * Usage: lat_pagefault file [file file...]
 *
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id$\n";

D 9
#include "timing.c"

E 9
I 9
D 10
#include "timing.h"
E 10
#include "bench.h"
E 9
D 10
#include <sys/stat.h>
#include <sys/mman.h>
I 8
#include <fcntl.h>
E 10
E 8

#define	CHK(x)	if ((x) == -1) { perror("x"); exit(1); }

D 8
main(ac, av)
	char **av;
E 8
I 8
void	timeit(char *file, char *where, int size);

int
main(int ac, char **av)
E 8
{
I 6
#ifdef	MS_INVALIDATE
E 6
	int fd;
D 11
	int i;
E 11
	char *where;
D 5
	int *p;
	int size;
E 5
	struct stat sbuf;

D 7
	write(2, id, strlen(id));
E 7
D 10
	if (ac < 2) {
		fprintf(stderr, "usage: %s file [file...]\n", av[0]);
E 10
I 10
	if (ac != 2) {
		fprintf(stderr, "usage: %s file\n", av[0]);
E 10
		exit(1);
	}
D 10
	for (i = 1; i < ac; ++i) {
		CHK(fd = open(av[i], 0));
		CHK(fstat(fd, &sbuf));
		sbuf.st_size &= ~(16*1024 - 1);		/* align it */
D 3
		if (sbuf.st_size < 100*1024) {
E 3
I 3
		if (sbuf.st_size < 1024*1024) {
E 3
			fprintf(stderr, "%s: %s too small\n", av[0], av[i]);
			continue;
		}
		where = mmap(0, sbuf.st_size, PROT_READ, MAP_SHARED, fd, 0);
I 4
D 6
#ifdef	BSD
		if (msync(where, sbuf.st_size) != 0) {
#else
E 6
E 4
		if (msync(where, sbuf.st_size, MS_INVALIDATE) != 0) {
I 4
D 6
#endif
E 6
E 4
			perror("msync");
			exit(1);
		}
		timeit(av[i], where, sbuf.st_size);
		munmap(where, sbuf.st_size);
E 10
I 10
	CHK(fd = open(av[1], 0));
	CHK(fstat(fd, &sbuf));
	sbuf.st_size &= ~(16*1024 - 1);		/* align it */
	if (sbuf.st_size < 1024*1024) {
		fprintf(stderr, "%s: %s too small\n", av[0], av[2]);
		exit(1);
E 10
	}
I 10
	where = mmap(0, sbuf.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (msync(where, sbuf.st_size, MS_INVALIDATE) != 0) {
		perror("msync");
		exit(1);
	}
D 11
	timeit(av[i], where, sbuf.st_size);
E 11
I 11
	timeit(av[1], where, sbuf.st_size);
E 11
	munmap(where, sbuf.st_size);
E 10
I 6
#endif
E 6
D 12
	exit(0);
E 12
I 12
	return(0);
E 12
}

/*
D 3
 * Get page fault times by going backwards in a stride of 32K
E 3
I 3
 * Get page fault times by going backwards in a stride of 256K
I 10
 * We don't want to do this in a loop, it needs a hi res clock.
 * XXX - hires.
E 10
E 3
 */
D 8
timeit(file, where, size)
	char	*file, *where;
E 8
I 8
void
timeit(char *file, char *where, int size)
E 8
{
	char	*end = where + size - 16*1024;
	int	sum = 0;
D 9
	int	lowest = 0x7fffffff;
E 9
I 9
	int	n = 0, usecs = 0;
E 9

	while (end > where) {
D 9
		start();
E 9
I 9
		start(0);
E 9
		sum += *end;
D 3
		end -= 32*1024;
E 3
I 3
		end -= 256*1024;
E 3
D 9
		sum = stop(sum);
		if (sum < lowest)
			lowest = sum;
E 9
I 9
		usecs += stop(0,0);
		n++;
E 9
	}
D 9
	fprintf(stderr, "Pagefaults on %s: %d usecs\n", file, lowest);
E 9
I 9
D 13
	use_result(sum);
E 13
I 13
	use_int(sum);
E 13
	fprintf(stderr, "Pagefaults on %s: %d usecs\n", file, usecs/n);
E 9
}
E 2
I 1
E 1
