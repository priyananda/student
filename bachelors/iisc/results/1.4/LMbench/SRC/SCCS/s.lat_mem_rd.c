h60502
s 00005/00003/00167
d D 1.14 00/08/01 16:04:21 staelin 15 14
c - Report more significant digits for memory latency
cC
cHhpli8.hpli.hpl.hp.com
cK17665
cZ+03:00
e
s 00018/00008/00152
d D 1.13 98/06/30 16:13:49 lm 14 13
c Go backwards instead of forwards; might fool HP machines.
cC
cK14350
cSAlpha2.11
e
s 00001/00001/00159
d D 1.12 98/06/29 22:37:35 lm 13 12
c Redo to compile clean with -Wall.
cK61572
cZ-07:00
e
s 00001/00001/00159
d D 1.11 97/10/31 18:06:23 lm 12 11
c use_result -> use_int/pointer
cK60686
cZ-08:00
e
s 00001/00001/00159
d D 1.10 97/06/15 22:38:58 lm 11 10
c lint
cK60411
e
s 00002/00003/00158
d D 1.9 97/06/14 18:23:34 lm 10 9
c *** empty log message ***
cK60181
e
s 00000/00001/00161
d D 1.8 97/06/12 21:30:06 lm 9 8
c new bench.h macros.
cK61081
e
s 00007/00001/00155
d D 1.7 97/04/23 22:35:06 lm 8 7
c step function.
cK62764
cZ-07:00
e
s 00005/00004/00151
d D 1.6 96/11/11 03:36:51 lm 7 6
c Auto adjusting changes.
cK55951
e
s 00014/00046/00141
d D 1.5 96/11/08 19:59:31 lm 6 5
c gcc -Wall cleanup & new timing.c integration.
c Get rid of mhz dependency (move that into the post processing).
cK52519
cZ-08:00
e
s 00000/00001/00187
d D 1.4 96/05/30 00:33:07 lm 5 4
c no what strings
cK09695
e
s 00001/00001/00187
d D 1.3 96/04/16 12:02:28 lm 4 3
c Jack Veenstra @ sgi.com found a bug that made the results off by .1%.
cK11766
cZ-07:00
e
s 00022/00001/00166
d D 1.2 96/01/22 23:25:34 lm 3 2
c make it take the k/m suffices.
cK12068
e
s 00167/00000/00000
d D 1.1 94/11/18 00:49:48 lm 2 1
c Initial revision
cK62263
e
s 00000/00000/00000
d D 1.0 94/11/18 00:49:47 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK64604
cPsrc/lat_mem_rd.c
cRc02704ba4b897de0
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
 * lat_mem_rd.c - measure memory load latency
 *
 * usage: lat_mem_rd size-in-MB stride [stride ...]
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
#include "bench.h"
E 7
D 6
#define N       1000000
E 6
I 6
#define N       1000000	/* Don't change this */
E 6
#define STRIDE  (512/sizeof(char *))
D 10
#define	TRIES	4
E 10
I 10
#define	MEMTRIES	4
E 10
#define	LOWER	512
D 7

#include	"timing.c"
E 7
I 6
void	loads(char *addr, int range, int stride);
int	step(int k);
E 6

D 6
main(ac, av)
        char  **av;
E 6
I 6
int
main(int ac, char **av)
E 6
{
        int     len;
	int	range;
	int	stride;
	int	i;
D 6
	float	clk, getclock();
E 6
        char   *addr;

D 5
	write(2, id, strlen(id));
E 5
        len = atoi(av[1]) * 1024 * 1024;
        addr = (char *)malloc(len);
D 6
	clk = getclock();
	printf("clk=%.2f\n", clk);
E 6

	if (av[2] == 0) {
		fprintf(stderr, "\"stride=%d\n", STRIDE);
		for (range = LOWER; range <= len; range = step(range)) {
D 6
			loads(addr, range, STRIDE, clk);
E 6
I 6
			loads(addr, range, STRIDE);
E 6
		}
	} else {
		for (i = 2; i < ac; ++i) {
D 3
			stride = atoi(av[i]);
E 3
I 3
			stride = bytes(av[i]);
E 3
			fprintf(stderr, "\"stride=%d\n", stride);
			for (range = LOWER; range <= len; range = step(range)) {
D 6
				loads(addr, range, stride, clk);
E 6
I 6
				loads(addr, range, stride);
E 6
			}
			fprintf(stderr, "\n");
		}
	}
D 11
	exit(0);
E 11
I 11
	return(0);
E 11
}

D 6
loads(addr, range, stride, clk)
	char	*addr;
	int	stride;
	float	clk;
E 6
I 6
void
loads(char *addr, int range, int stride)
E 6
{
D 13
	register char **p;
E 13
I 13
	register char **p = 0 /* lint */;
E 13
        int     i;
	int	tries = 0;
	int	result = 0x7fffffff;
I 15
	double	time;
E 15

D 14
        /*
	 * First create a list of pointers.
	 */
E 14
     	if (stride & (sizeof(char *) - 1)) {
D 14
		fprintf(stderr, "list: stride must be aligned.\n");
E 14
I 14
		printf("lat_mem_rd: stride must be aligned.\n");
		return;
	}
	
	if (range < stride) {
E 14
		return;
	}

D 14
     	for (i = 0; i < range; i += stride) {
E 14
I 14
	/*
	 * First create a list of pointers.
	 *
	 * This used to go forwards, we want to go backwards to try and defeat
	 * HP's fetch ahead.
	 *
	 * We really need to do a random pattern once we are doing one hit per 
	 * page.
	 */
	for (i = range - stride; i >= 0; i -= stride) {
E 14
		char	*next;

		p = (char **)&addr[i];
D 14
		if (i + stride >= range) {
			next = &addr[0];
E 14
I 14
		if (i < stride) {
			next = &addr[range - stride];
E 14
		} else {
D 14
			next = &addr[i + stride];
E 14
I 14
			next = &addr[i - stride];
E 14
		}
		*p = next;
	}

	/*
	 * Now walk them and time it.
	 */
D 10
        for (tries = 0; tries < TRIES; ++tries) {
E 10
I 10
        for (tries = 0; tries < MEMTRIES; ++tries) {
E 10
                /* time loop with loads */
#define	ONE	p = (char **)*p;
#define	FIVE	ONE ONE ONE ONE ONE
#define	TEN	FIVE FIVE
#define	FIFTY	TEN TEN TEN TEN TEN
#define	HUNDRED	FIFTY FIFTY
D 4
		i = N - 1000;
E 4
I 4
		i = N;
E 4
D 10
		p = (char **)addr;
E 10
D 7
                start();
E 7
I 7
                start(0);
E 7
                while (i > 0) {
			HUNDRED
			HUNDRED
			HUNDRED
			HUNDRED
			HUNDRED
			HUNDRED
			HUNDRED
			HUNDRED
			HUNDRED
			HUNDRED
			i -= 1000;
                }
D 7
		i = stop(p);
E 7
I 7
		i = stop(0,0);
D 12
		use_result((int)p);
E 12
I 12
		use_pointer((void *)p);
E 12
E 7
		if (i < result) {
			result = i;
		}
	}
	/*
	 * We want to get to nanoseconds / load.  We don't want to
	 * lose any precision in the process.  What we have is the
	 * milliseconds it took to do N loads, where N is 1 million,
	 * and we expect that each load took between 10 and 2000
	 * nanoseconds.
	 *
	 * We want just the memory latency time, not including the
	 * time to execute the load instruction.  We allow one clock
	 * for the instruction itself.  So we need to subtract off
	 * N * clk nanoseconds.
	 *
I 6
	 * lmbench 2.0 - do the subtration later, in the summary.
	 * Doing it here was problematic.
	 *
E 6
	 * XXX - we do not account for loop overhead here.
	 */
D 6
     	i = (clk * N) / 1000;		/* load instruction time in usecs */
	result -= i;			/* time for the loads themselves */
E 6
D 15
	result *= 1000;			/* convert to nanoseconds */
	result /= N;				/* nanosecs per load */
	fprintf(stderr, "%.5f %d\n", range / (1024. * 1024), result);
E 15
I 15
	time = (double)result;
	time *= 1000.;				/* convert to nanoseconds */
	time /= (double)N;			/* nanosecs per load */
	fprintf(stderr, "%.5f %.3f\n", range / (1024. * 1024), time);
E 15
}

D 6
step(k)
E 6
I 6
int
step(int k)
E 6
{
	if (k < 1024) {
		k = k * 2;
        } else if (k < 4*1024) {
		k += 1024;
        } else if (k < 32*1024) {
		k += 2048;
        } else if (k < 64*1024) {
		k += 4096;
        } else if (k < 128*1024) {
		k += 8192;
        } else if (k < 256*1024) {
		k += 16384;
        } else if (k < 512*1024) {
		k += 32*1024;
D 8
	} else {
E 8
I 8
	} else if (k < 4<<20) {
E 8
		k += 512 * 1024;
I 8
	} else if (k < 8<<20) {
		k += 1<<20;
	} else if (k < 20<<20) {
		k += 2<<20;
	} else {
		k += 10<<20;
E 8
	}
	return (k);
}
D 6

float
getclock()
{
	float	c;
	FILE	*f = popen("mhz -c", "r");

	fscanf(f, "%f", &c);
	return (c);
}
I 3

int
bytes(s)
	char	*s;
{
	int	n = atoi(s);

	if ((last(s) == 'k') || (last(s) == 'K'))
		n *= 1024;
	if ((last(s) == 'm') || (last(s) == 'M'))
		n *= (1024 * 1024);
	return (n);
}

last(s)
	char	*s;
{
	while (*s++)
		;
	return (s[-2]);
}
E 6
E 3
E 2
I 1
E 1
