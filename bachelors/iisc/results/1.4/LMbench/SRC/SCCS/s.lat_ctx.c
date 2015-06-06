h65392
s 00007/00048/00318
d D 1.24 98/06/30 23:58:20 lm 25 24
c This version suns the data in the L1 cache in order to
c calculate the overhead of summing the data.  This works
c fine for small tests, but is somewhat confusing on larger
c tests since the context switch includes more work than
c it should (the sum overhead should include L1/L2 cache
c misses if they occur in the single process case).
c However, this does seem to get less bouncy results.
cC
cK07445
cSAlpha2.11
e
s 00093/00029/00273
d D 1.23 98/06/30 22:44:04 lm 24 23
c Saving a copy that doesn't work well.  This one shows the
c results of taking the min sum from all the children which
c still doesn't work.  
cK04187
e
s 00020/00016/00282
d D 1.22 98/06/29 23:50:03 lm 23 22
c Major change from the 1.x release;  these numbers are
c not directly comparable to 1.x (tho the shape of the
c graph is very similar).
c The change is to sum up every 4th int (assumes a 16byte
c or greater cache line) and to not subtract the sum costs
c from the context switch.  This should keep the numbers
c above zero, even when we get screwed up caches.
c I still subtract off the cost of the pipe overhead, this
c makes the 0 sized process numbers the same.
cK15577
e
s 00001/00001/00297
d D 1.21 98/06/29 22:37:29 lm 22 21
c Redo to compile clean with -Wall.
cK65410
cZ-07:00
e
s 00001/00001/00297
d D 1.20 97/10/31 18:06:23 lm 21 20
c use_result -> use_int/pointer
cK64524
cZ-08:00
e
s 00080/00073/00218
d D 1.19 97/06/27 17:23:14 lm 20 19
c carl's stuff plus some bug fixes.
cK64864
e
s 00005/00021/00286
d D 1.18 97/06/19 13:51:14 lm 19 18
c get rid of /dev/zero mmap.
cK53458
e
s 00031/00001/00276
d D 1.17 97/06/16 19:05:50 lm 18 17
c lint
cK08668
e
s 00045/00030/00232
d D 1.16 97/06/16 16:05:24 lm 17 16
c make do TRIPS trips around the ring no matter what enough may be.
cK31959
e
s 00007/00004/00255
d D 1.15 97/06/15 22:38:58 lm 16 15
c lint
cK19847
e
s 00001/00001/00258
d D 1.14 97/06/14 18:23:06 lm 15 14
c *** empty log message ***
cK13753
e
s 00010/00026/00249
d D 1.13 97/06/14 12:20:00 lm 14 13
c Carl's changes + morefds().
cK13755
e
s 00025/00011/00250
d D 1.12 97/06/13 20:26:39 lm 13 12
c wje's idea of doing a constant amount of work.
cK22027
e
s 00081/00087/00180
d D 1.11 97/06/12 21:13:10 lm 12 11
c carl's idea.
cK03826
e
s 00024/00065/00243
d D 1.10 97/06/12 20:42:52 lm 11 10
c last rev before Carl's version.
cK08070
e
s 00000/00003/00308
d D 1.9 97/06/11 19:04:27 lm 10 9
c bench.h
cK02765
cZ-07:00
e
s 00023/00058/00288
d D 1.8 97/02/12 19:19:17 lm 9 8
c XXX - needs more work.
cK08424
e
s 00001/00001/00345
d D 1.7 96/11/13 16:09:37 lm 8 7
c typo.
cK55309
e
s 00012/00005/00334
d D 1.6 96/11/11 03:36:51 lm 7 6
c Auto adjusting changes.
cK55202
e
s 00012/00042/00327
d D 1.5 96/11/08 19:58:43 lm 6 5
c gcc -Wall cleanup.
c Get rid of virtual address cache hack.
c Bug in the overhead code.
cK49157
cZ-08:00
e
s 00000/00001/00369
d D 1.4 96/05/30 00:33:07 lm 5 4
c no what strings
cK23593
e
s 00005/00003/00365
d D 1.3 95/10/25 21:03:09 lm 4 3
c *** empty log message ***
cK25664
e
s 00041/00019/00327
d D 1.2 95/09/28 15:08:42 lm 3 2
c make it auto size to the clock.
cK22957
cZ-07:00
e
s 00346/00000/00000
d D 1.1 94/11/18 00:49:48 lm 2 1
c Initial revision
cK61800
e
s 00000/00000/00000
d D 1.0 94/11/18 00:49:47 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK05650
cPsrc/lat_ctx.c
cR8c9456d3fe23f5b3
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
 * lat_ctx.c - context switch timer 
 *
 * usage: lat_ctx [-s size] #procs [#procs....]
 *
 * Copyright (c) 1994 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id$\n";

D 7
#include "timing.c"
E 7
I 7
D 10
#include "timing.h"
E 10
#include "bench.h"
E 7
D 6
/*
 * You may not report numbers with this define turned on.
 */
/*#define	VIRTUAL_ADDR_CACHE	/*Sun internal only*/
E 6
I 6
D 10
#include <sys/types.h>
#include <sys/wait.h>
E 10
E 6

I 18
#if	defined(sgi) && defined(PIN)
#include <sys/sysmp.h>
#include <sys/syssgi.h>
int	ncpus;
#endif
E 18
D 3
#define	TRIES	12
#define	WRITES	2000
E 3
I 3
D 4
#define	TRIES	6
E 4
I 4
D 9
#define	TRIES	8
E 9
I 9
D 11
#define	TRIES	4
E 11
I 11
D 12
#define	TRIES	6
E 12
I 12
D 13
#define	MAXPROC	20
E 13
E 12
E 11
E 9
E 4
E 3

I 13
D 19
#define	MAXPROC	96
E 19
I 19
D 20
#define	MAXPROC	1000
E 20
I 20
#define	MAXPROC	2048
E 20
E 19
D 24
#define	MAXSIZE	(64<<10)
E 24
I 24
#define	CHUNK	(4<<10)
E 24
I 17
#define	TRIPS	5
I 24
#ifndef	max
#define	max(a, b)	((a) > (b) ? (a) : (b))
#endif
E 24
E 17

E 13
int	process_size, *data;	/* size & pointer to an array that big */
D 12
int	pids[100];
E 12
I 12
int	pids[MAXPROC];
int	p[MAXPROC][2];
E 12
D 6
int	pipe_cost(), overhead(), ctx(), sumit();
void	doit();
E 6
I 6
D 11
int	caches(), pipe_cost(), overhead(), sumit();
int	ctx(int overhead, int writes, int procs);
E 11
I 11
D 14
double	pipe_cost(), overhead();
E 14
I 14
D 23
double	pipe_cost(int p[][2], int procs);
E 23
I 23
D 24
double	pipe_cost(int p[][2], int procs, int dosum);
E 24
I 24
double	pipe_cost(int p[][2], int procs);
E 24
E 23
E 14
D 16
int	sumit();
E 16
I 16
int	ctx(int procs, int nprocs);
int	sumit(int);
E 16
D 12
double	ctx(double overhead, int writes, int procs);
E 12
E 11
void	killem(int procs);
D 12
void	doit(int p[100][2], int rd, int wr);
E 12
I 12
void	doit(int p[MAXPROC][2], int rd, int wr);
D 20
void	create_daemons(int p[][2], int pids[], int procs);
E 20
I 20
int	create_pipes(int p[][2], int procs);
D 24
int	create_daemons(int p[][2], int pids[], int procs);
E 20
I 16
int	sumit(int howmuch);
E 24
I 24
D 25
int	create_daemons(int p[][2], int pids[], int procs, double *sum);
E 25
I 25
int	create_daemons(int p[][2], int pids[], int procs);
E 25
E 24
E 16
E 12
E 6

int
D 6
main(ac, av)
	int	ac;
	char	**av;
E 6
I 6
main(int ac, char **av)
E 6
{
D 12
	int	i;
	int	tries;
D 11
	int	result;
	int	min;
	int	overhead;
E 11
I 3
	int	writes;
E 12
I 12
	int	i, max_procs;
E 12
I 11
D 16
	double	result;
E 16
D 12
	double	min;
E 12
D 23
	double	overhead;
E 23
I 23
D 24
	double	pipeovr, overhead;
E 24
I 24
D 25
	double	t1, t2, sumAll = 0, sumMin = 0, overhead = 0;
E 25
I 25
	double	overhead = 0;
E 25
E 24
E 23
I 18
D 19
	char	*getbuf(int);
E 19
E 18
E 11
E 3

D 5
	write(2, id, strlen(id));
E 5
	if (ac < 2) {
usage:		printf("Usage: %s [-s kbytes] processes [processes ...]\n",
		    av[0]);
I 12
		exit(1);
E 12
	}

	/*
I 13
	 * Need 4 byte ints.
	 */
	if (sizeof(int) != 4) {
		fprintf(stderr, "Fix sumit() in ctx.c.\n");
		exit(1);
	}

	/*
E 13
	 * If they specified a context size, get it.
	 */
	if (!strcmp(av[1], "-s")) {
D 6
#ifdef	VIRTUAL_ADDR_CACHE
		int	nprocs = 0;
#endif

E 6
D 12
		if (ac < 3) {
E 12
I 12
		if (ac < 4) {
E 12
			goto usage;
		}
D 6
#ifdef	VIRTUAL_ADDR_CACHE
		for (i = 3; i < ac; ++i) {
			if (atoi(av[i]) > nprocs) {
				nprocs = atoi(av[i]);
			}
		}
#endif
E 6
		process_size = atoi(av[2]) * 1024;
D 6
#ifdef	VIRTUAL_ADDR_CACHE
		data = (int *)malloc(process_size * nprocs);
#else
E 6
D 13
		data = (int *)malloc(process_size);
E 13
I 13
D 18
		data = (int *)malloc(MAXSIZE);
E 18
I 18
D 19
		data = (int *)getbuf(MAXSIZE);
E 19
I 19
D 24
		data = (int *)malloc(MAXSIZE);
E 24
I 24
		if (process_size > 0) {
			data = (int *)calloc(1, max(process_size, CHUNK));
			BENCHO(sumit(CHUNK), sumit(0), 0);
			overhead = gettime();
			overhead /= get_n();
			overhead *= process_size;
			overhead /= CHUNK;
D 25
			BENCHO(sumit(process_size), sumit(0), 0);
			sumAll = gettime();
			sumAll /= get_n();
E 25
		}
E 24
E 19
E 18
E 13
D 6
#endif
E 6
		ac -= 2;
		av += 2;
	}

I 18
#if	defined(sgi) && defined(PIN)
	ncpus = sysmp(MP_NPROCS);
	sysmp(MP_MUSTRUN, 0);
#endif
E 18
D 14
	overhead = pipe_cost();

D 8
	fprintf(stderr, "\n\"size=%d ovr=%d\n", process_size/1024, overhead);
E 8
I 8
D 11
	fprintf(stderr, "\n\"size=%dk ovr=%d\n", process_size/1024, overhead);
E 11
I 11
	fprintf(stderr, "\n\"size=%dk ovr=%.2f\n", process_size/1024, overhead);
E 11
E 8

E 14
I 12
D 20
	for (max_procs = atoi(av[1]), i = 2; i < ac; ++i) {
E 20
I 20
	for (max_procs = atoi(av[1]), i = 1; i < ac; ++i) {
E 20
		int procs = atoi(av[i]);
		if (max_procs < procs) max_procs = procs;
	}
I 20
	max_procs = create_pipes(p, max_procs);
E 20
I 14
D 23
	overhead = pipe_cost(p, max_procs);
E 23
I 23
D 24
	overhead = pipe_cost(p, max_procs, 1);
	pipeovr = pipe_cost(p, max_procs, 0);
E 23
E 14
D 20
	create_daemons(p, pids, max_procs);
E 20
I 20
	max_procs = create_daemons(p, pids, max_procs);
E 20
I 14
	fprintf(stderr, "\n\"size=%dk ovr=%.2f\n", process_size/1024, overhead);
E 24
I 24
D 25
	t1 = overhead;
	t2 = pipe_cost(p, max_procs);
	overhead += t2;

	// new way
	overhead = sumMin + t2;
	max_procs = create_daemons(p, pids, max_procs, &sumMin);
	overhead += sumMin;
	fprintf(stderr, "\n\"size=%dk ovr=%.2f (sum=%.2f %.2f %.2f pipe=%.2f)\n",
	    process_size/1024, overhead, t1, sumAll, sumMin, t2);
E 25
I 25
	overhead += pipe_cost(p, max_procs);
	max_procs = create_daemons(p, pids, max_procs);
	fprintf(stderr, "\n\"size=%dk ovr=%.2f\n", process_size/1024, overhead);
E 25
E 24
E 14
E 12
	for (i = 1; i < ac; ++i) {
I 3
D 12
		/*
		 * OK, assume that the worst clock is 10msec.
		 * We want 10 times that.
		 */
		writes = 100;
		do {
			writes <<= 1;
			result = ctx(overhead, writes, 10);
		} while (((result + overhead) * writes) < 100000);
E 12
I 12
		double	time;
		int	procs = atoi(av[i]);
E 12

I 20
		if (procs > max_procs) continue;

E 20
D 12
		/*
		 * Now make each subtest take about a second.
		 */
D 4
		writes *= 8;
E 4
I 4
		writes *= 10;
E 12
I 12
D 17
		/* give the scheduler time to adapt */
D 14
		BENCH(ctx(procs, max_procs), 300000);
E 14
I 14
D 15
		BENCH1(ctx(procs, max_procs), 300000);
E 15
I 15
		BENCH1(ctx(procs, max_procs), 100000);
E 17
E 15
E 14
		BENCH(ctx(procs, max_procs), 0);
		time = usecs_spent();
		time /= get_n();
		time /= procs;
I 17
		time /= TRIPS;
E 17
D 23
		time -= overhead;
E 23
I 23
D 24
		time -= pipeovr;
E 24
I 24
		time -= overhead;
E 24
E 23
	    	fprintf(stderr, "%d %.2f\n", procs, time);
	}
E 12
E 4

E 3
D 11
		min = 0x7fffffff;
E 11
I 11
D 12
		min = 1e100;
E 11
		for (tries = 0; tries < TRIES; ++tries) {
D 3
			result = ctx(overhead, WRITES, atoi(av[i]));
E 3
I 3
			result = ctx(overhead, writes, atoi(av[i]));
E 3
			if (min > result) {
				min = result;
			}
E 12
I 12
	/*
	 * Close the pipes and kill the children.
	 */
     	killem(max_procs);
     	for (i = 0; i < max_procs; ++i) {
		close(p[i][0]);
		close(p[i][1]);
		if (i > 0) {
			wait(0);
E 12
		}
D 11
	    	fprintf(stderr, "%d %d\n", atoi(av[i]), min);
E 11
I 11
D 12
	    	fprintf(stderr, "%d %.2f\n", atoi(av[i]), min);
E 12
E 11
	}
	return (0);
}

D 11
int
D 6
ctx(overhead, writes, procs)
	int	overhead, writes, procs;
E 6
I 6
ctx(int overhead, int writes, int procs)
E 11
I 11
D 12
double
ctx(double overhead, int writes, int procs)
E 12
I 12
D 20
void
create_daemons(int p[][2], int pids[], int procs)
E 12
E 11
E 6
{
D 12
	int	p[100][2];
	int	msg = 0, i;
D 11
	int	time;
E 11
I 11
	double	time;
E 11
	int	sum;
E 12
I 12
	int	i;
	int	msg;
E 20
E 12

D 12

E 12
D 20
	/*
D 14
	 * Get a bunch of pipes.
	 */
     	for (i = 0; i < procs; ++i) {
		if (pipe(p[i]) == -1) {
			perror("pipe");
			exit(1);
		}
	}

	/*
E 14
	 * Use the pipes as a ring, and fork off a bunch of processes
	 * to pass the byte through their part of the ring.
	 */
	signal(SIGTERM, SIG_IGN);
     	for (i = 1; i < procs; ++i) {
		switch (pids[i] = fork()) {
		    case -1: 
			perror("fork");
			killem(procs);
I 19
			exit(1);
E 19

		    case 0:	/* child */
I 18
#if	defined(sgi) && defined(PIN)
	sysmp(MP_MUSTRUN, i % ncpus);
#endif
E 18
D 6
#ifdef	VIRTUAL_ADDR_CACHE
			/*
			 * This is a hack to put the per process data
			 * at different virtual addresses.  It was
			 * added to see if it makes a difference on
			 * ROSS HyperSPARC modules that have a VAC.
			 * It does.
			 */
			((char *) data) += process_size * i;
#endif
E 6
			doit(p, i-1, i);
			/* NOTREACHED */

		    default:	/* parent */
		    	;
	    	}
	}

I 19
	bzero((void*)data, MAXSIZE);	/* make sure we have our own copy */

E 19
	/*
	 * Go once around the loop to make sure that everyone is ready and
	 * to get the token in the pipeline.
	 */
	if (write(p[0][1], &msg, sizeof(msg)) != sizeof(msg) ||
D 11
	    read(p[procs-1][0], &msg, sizeof(msg)) != sizeof(msg) ||
	    write(p[0][1], &msg, sizeof(msg)) != sizeof(msg)) {
E 11
I 11
	    read(p[procs-1][0], &msg, sizeof(msg)) != sizeof(msg)) {
E 11
		perror("write/read/write on pipe");
		exit(1);
	}
D 13
	bzero(data, process_size);	/* make sure we have our own copy */
E 13
I 13
D 17
	bzero(data, MAXSIZE);	/* make sure we have our own copy */
E 17
I 17
D 19
	bzero((void*)data, MAXSIZE);	/* make sure we have our own copy */
E 19
E 17
E 13
I 12
}
E 12

I 12

E 20
int
ctx(int procs, int nprocs)
{
	int	msg;
I 17
	int	i;
	int	sum;
E 17

E 12
	/*
	 * Main process - all others should be ready to roll, time the
	 * loop.
	 */
D 7
	start();
E 7
I 7
D 12
	start(0);
E 7
	for (i = writes / procs; i--; ) {
D 11
		if (read(p[procs-1][0], &msg, sizeof(msg)) != sizeof(msg)) {
E 11
I 11
	    	if (write(p[0][1], &msg, sizeof(msg)) != sizeof(msg)) {
E 11
			perror("read/write on pipe");
			exit(1);
		}
D 11
		sum = sumit();
	    	if (write(p[0][1], &msg, sizeof(msg)) != sizeof(msg)) {
E 11
I 11
		if (read(p[procs-1][0], &msg, sizeof(msg)) != sizeof(msg)) {
E 11
			perror("read/write on pipe");
			exit(1);
		}
I 11
		sum = sumit(0);
E 12
I 12
D 17
    	if (write(p[nprocs - procs][1], &msg, sizeof(msg)) != sizeof(msg)) {
		perror("read/write on pipe");
		exit(1);
E 17
I 17
	for (i = 0; i < TRIPS; ++i) {
		if (write(p[nprocs - procs][1], &msg, sizeof(msg)) !=
		    sizeof(msg)) {
			perror("read/write on pipe");
			exit(1);
		}
		if (read(p[nprocs-1][0], &msg, sizeof(msg)) != sizeof(msg)) {
			perror("read/write on pipe");
			exit(1);
		}
		sum = sumit(process_size);
E 17
E 12
E 11
	}
D 7
	time = stop();
E 7
I 7
D 12
	time = stop(0,0);
E 7

	/*
	 * Close the pipes and kill the children.
	 */
     	killem(procs);
     	for (i = 0; i < procs; ++i) {
		close(p[i][0]);
		close(p[i][1]);
		if (i > 0) {
			wait(0);
		}
E 12
I 12
D 17
	if (read(p[nprocs-1][0], &msg, sizeof(msg)) != sizeof(msg)) {
		perror("read/write on pipe");
		exit(1);
E 12
	}
D 12

	/*
	 * We know the overhead cost of each pipe trip, but we did it
	 * write times.
	 */
	return ((time / writes) - overhead);
E 12
I 12
D 13
	return sumit(0);
E 13
I 13
	return sumit(process_size);
E 17
I 17
	return (sum);
E 17
E 13
E 12
}

D 6
killem(procs)
	int	procs;
E 6
I 6
void
killem(int procs)
E 6
{
	int	i;

	for (i = 1; i < procs; ++i) {
		if (pids[i] > 0) {
			kill(pids[i], SIGTERM);
		}
	}
}

void
D 6
doit(p, rd, wr)
	int	p[100][2];
	int	rd, wr;
E 6
I 6
D 12
doit(int p[100][2], int rd, int wr)
E 12
I 12
D 20
doit(int p[MAXPROC][2], int rd, int wr)
E 20
I 20
doit(int p[][2], int rd, int wr)
E 20
E 12
E 6
{
D 22
	int	msg, sum;
E 22
I 22
	int	msg, sum = 0 /* lint */;
E 22

	signal(SIGTERM, SIG_DFL);
D 13
	bzero(data, process_size);	/* make sure we have our own copy */
E 13
I 13
D 17
	bzero(data, MAXSIZE);	/* make sure we have our own copy */
E 17
I 17
D 20
	bzero((void*)data, MAXSIZE);	/* make sure we have our own copy */
E 20
I 20
D 24
	if (data) bzero((void*)data, MAXSIZE);	
E 24
I 24
	if (data) bzero((void*)data, process_size);	
E 24
E 20
E 17
E 13
	for ( ;; ) {
		if (read(p[rd][0], &msg, sizeof(msg)) != sizeof(msg)) {
			perror("read/write on pipe");
D 16
			exit(1);
E 16
I 16
			break;
E 16
		}
D 11
		sum = sumit();
E 11
I 11
D 13
		sum = sumit(0);
E 13
I 13
		sum = sumit(process_size);
E 13
E 11
		if (write(p[wr][1], &msg, sizeof(msg)) != sizeof(msg)) {
			perror("read/write on pipe");
D 16
			exit(1);
E 16
I 16
			break;
E 16
		}
	}
I 16
D 21
	use_result(sum);
E 21
I 21
	use_int(sum);
E 21
	exit(1);
E 16
}

I 17
D 20
doit_cost(int p[MAXPROC][2], int procs)
E 20
I 20
int
D 23
doit_cost(int p[][2], int procs)
E 23
I 23
D 24
doit_cost(int p[][2], int procs, int dosum)
E 24
I 24
doit_cost(int p[][2], int procs)
E 24
E 23
E 20
{
	static	int k;
	int	msg = 1;
	int	i;

D 24
	for (i =0; i < TRIPS; ++i) {
E 24
I 24
	for (i = 0; i < TRIPS; ++i) {
E 24
D 20
		if (write(p[k][1], &msg, sizeof(msg)) != sizeof(msg)) {		
			perror("read/write on pipe");			
E 20
I 20
		if (write(p[k][1], &msg, sizeof(msg)) != sizeof(msg)) {
			perror("read/write on pipe");
E 20
			exit(1);				
D 20
		}								
		if (read(p[k][0], &msg, sizeof(msg)) != sizeof(msg)) {	
			perror("read/write on pipe");		
			exit(1);			
		}								
		if (++k == procs) {					
			k = 0;					
		}					
E 20
I 20
		}
		if (read(p[k][0], &msg, sizeof(msg)) != sizeof(msg)) {
			perror("read/write on pipe");
			exit(1);
		}
		if (++k == procs) {
			k = 0;
		}
E 20
D 23
		msg = sumit(process_size);
E 23
I 23
D 24
		if (dosum) msg = sumit(process_size);
E 24
E 23
	}
	return (msg);
}

E 17
/*
D 24
 * Run the overhead test several times, taking the smallest overhead to
 * be valid.  The reasoning is that larger overheads probably included
 * the cost of some other system activity.
 *
E 24
 * The cost returned is the cost of going through one pipe once in usecs.
I 24
 * No memory costs are included here, this is different than lmbench1.
E 24
I 4
D 9
 *
 * XXX - this varies too much.
E 9
E 4
 */
D 11
int
E 11
I 11
double
E 11
D 14
pipe_cost()
E 14
I 14
D 23
pipe_cost(int p[][2], int procs)
E 23
I 23
D 24
pipe_cost(int p[][2], int procs, int dosum)
E 24
I 24
pipe_cost(int p[][2], int procs)
E 24
E 23
E 14
{
D 9
	int	i, min = 0x7fffffff;

D 4
	for (i = 0; i < TRIES; ++i) {
E 4
I 4
	for (i = 0; i < TRIES*2; ++i) {
E 4
		int	j = overhead();

		if (min > j) {
			min = j;
		}

		/*
		 * This seems to disturb the caches just
		 * enough that I get consistent overhead numbers.
		 * Weird, I know.
		 */
		j = caches();
	}
	return (min);
}

/*
 * Calculate the cost of passing a byte through a pipe.  I do it with a
 * bunch of pipes to try and burn through the onboard caches.  Note that
 * on a Sun SPARC ss2, it made little difference if the loop was over one
 * or thirty pipes.
 */
int
overhead()
{
E 9
D 12
	int	p[100][2];
D 9
	int	msg = 0, sum, i, n, k;
I 3
	int	writes;
E 9
I 9
	int	msg, sum, i, n, k, N;
E 12
I 12
D 14
	int	msg, sum, n, k;
E 14
I 14
D 17
	int	msg, sum, i, k;
E 17
I 17
D 20
	int	msg, i, k;
E 20
E 17
E 14
	double	result;
E 12
E 9
E 3

	/*
D 20
	 * Get a bunch of pipes.
	 */
D 14
	n = 0;
D 12
	while (n < 20 && pipe(p[n]) != -1)
		n++;
E 12
I 12
	while (n < MAXPROC) {
		if (pipe(p[n++]) == -1) {
E 14
I 14
	morefds();
     	for (i = 0; i < procs; ++i) {
		if (pipe(p[i]) == -1) {
E 14
			perror("pipe");
			exit(1);
		}
	}
E 12

I 12
D 17
#define PIPE_BODY 							\
	if (write(p[k][1], &msg, sizeof(msg)) != sizeof(msg)) {		\
		perror("read/write on pipe");				\
		exit(1);						\
	}								\
	if (read(p[k][0], &msg, sizeof(msg)) != sizeof(msg)) {		\
		perror("read/write on pipe");				\
		exit(1);						\
	}								\
D 14
	if (++k == MAXPROC) {							\
E 14
I 14
	if (++k == procs) {						\
E 14
		k = 0;							\
	}								\
D 13
	sum = sumit(1);
E 13
I 13
	sum = sumit(0);
E 13

E 17
E 12
	/*
E 20
	 * Measure the overhead of passing a byte around the ring.
	 */
D 11
	if (write(p[k = 0][1], &msg, sizeof(msg)) != sizeof(msg)) {
		perror("read/write on pipe");
		exit(1);
	}
E 11
D 3
	start();
	for (i = 0; i < WRITES; ++i) {
		if (read(p[k][0], &msg, sizeof(msg)) != sizeof(msg)) {
			perror("read/write on pipe");
			exit(1);
E 3
I 3
D 9
	writes = 200; 
	do {
		writes <<= 2;
E 9
I 9
D 20
	k = 0;
E 20
D 12
	LOOP_FIRST(N, i, ENOUGH);
	if (write(p[k][1], &msg, sizeof(msg)) != sizeof(msg)) {
		perror("read/write on pipe");
		exit(1);
	}
	if (read(p[k][0], &msg, sizeof(msg)) != sizeof(msg)) {
		perror("read/write on pipe");
		exit(1);
	}
	if (++k == n) {
E 9
		k = 0;
D 7
		start();
E 7
I 7
D 9
		start(0);
E 7
		for (i = 0; i < writes; ++i) {
			if (read(p[k][0], &msg, sizeof(msg)) != sizeof(msg)) {
				perror("read/write on pipe");
				exit(1);
			}
D 6
			if (k == n) {
E 6
I 6
			if (++k == n) {
E 6
				k = 0;
			}
			sum = sumit();
			if (write(p[k][1], &msg, sizeof(msg)) != sizeof(msg)) {
				perror("read/write on pipe");
				exit(1);
			}
E 3
		}
D 3
		if (k == n) {
			k = 0;
		}
		sum = sumit();
		if (write(p[k][1], &msg, sizeof(msg)) != sizeof(msg)) {
			perror("read/write on pipe");
			exit(1);
		}
	}
	k = stop();
E 3
I 3
D 7
		k = stop();
E 7
I 7
		k = stop(0,0);
E 7
	} while (k <= 1000000);

E 3
	for (i = 0; i < n; ++i) {
		close(p[i][0]);
		close(p[i][1]);
E 9
	}
D 3
	return (k / WRITES);
E 3
I 3
D 9
	return (k / writes);
E 9
I 9
D 11
	sum = sumit();
E 11
I 11
	sum = sumit(1);
E 11
	LOOP_LAST(N, i, ENOUGH);
	for (k = 0; k < n; ++k) {
E 12
I 12
D 17
	BENCH(PIPE_BODY, 0);
E 17
I 17
D 23
	BENCH(doit_cost(p, procs), 0);
E 23
I 23
D 24
	BENCH(doit_cost(p, procs, dosum), 0);
E 24
I 24
	BENCH(doit_cost(p, procs), 0);
E 24
E 23
E 17
	result = usecs_spent();
	result /= get_n();
D 17

D 14
	for (k = 0; k < MAXPROC; ++k) {
E 12
		close(p[k][0]);
		close(p[k][1]);
	}
E 14
D 11
	/* printf("pipe cost=%d %d %d\n", i/N,i,N); */
	return (i / N);
E 11
I 11
D 12
	/* printf("pipe cost=%d %d %d\n", i/N,i,N); /* */
	return ((double)i / N);
E 12
I 12
	use_result(sum);
E 17
I 17
	result /= TRIPS;
E 17
	return result;
E 12
E 11
E 9
E 3
}

I 20
int
D 24
create_daemons(int p[][2], int pids[], int procs)
E 24
I 24
D 25
create_daemons(int p[][2], int pids[], int procs, double *sump)
E 25
I 25
create_daemons(int p[][2], int pids[], int procs)
E 25
E 24
{
	int	i;
	int	msg;
I 24
D 25
	int	pipes[2];
E 25
E 24

	/*
	 * Use the pipes as a ring, and fork off a bunch of processes
	 * to pass the byte through their part of the ring.
I 24
	 *
	 * Do the sum in each process and get that time before moving on.
E 24
	 */
	signal(SIGTERM, SIG_IGN);
I 24
D 25
	if (data) {
		if (pipe(pipes) == -1) {
			perror("pipes");
			exit(1);
		}
		*sump = -1;
	} else {
		*sump = 0;
	}
E 25
E 24
     	for (i = 1; i < procs; ++i) {
		switch (pids[i] = fork()) {
		    case -1:	/* could not fork, out of processes? */
			procs = i;
			break;

		    case 0:	/* child */
#if	defined(sgi) && defined(PIN)
			sysmp(MP_MUSTRUN, i % ncpus);
#endif
I 24
D 25
			if (data) {
				double	sum;

				bzero((void*)data, process_size);	
				BENCH(sumit(process_size), 0);
				sum = gettime();
				sum /= get_n();
				write(pipes[1], &sum, sizeof(sum));
				close(pipes[1]);
				close(pipes[0]);
			}
E 25
E 24
			doit(p, i-1, i);
			/* NOTREACHED */

		    default:	/* parent */
D 24
		    	;
E 24
I 24
D 25
			if (data) {
				double	sum;

				read(pipes[0], &sum, sizeof(sum));
				if ((*sump == -1) || (sum < *sump)) {
					*sump = sum;
				}
			}
E 25
I 25
			;
E 25
E 24
	    	}
	}
I 24
D 25
	if (data) fprintf(stderr, "\n");
	close(pipes[0]);
	close(pipes[1]);
E 25
E 24

	/*
	 * Go once around the loop to make sure that everyone is ready and
	 * to get the token in the pipeline.
	 */
	if (write(p[0][1], &msg, sizeof(msg)) != sizeof(msg) ||
	    read(p[procs-1][0], &msg, sizeof(msg)) != sizeof(msg)) {
		perror("write/read/write on pipe");
		exit(1);
	}
D 24
	if (data) bzero((void*)data, MAXSIZE);	
E 24
I 24
	if (data) bzero((void*)data, process_size);	
E 24
	return procs;
}

int
create_pipes(int p[][2], int procs)
{
	int	i;
	/*
	 * Get a bunch of pipes.
	 */
	morefds();
     	for (i = 0; i < procs; ++i) {
		if (pipe(p[i]) == -1) {
			return i;
		}
	}
	return procs;
}

E 20
I 13
/*
D 23
 * Do 64K worth of reads over 2K..MAXSIZE worth of data.
E 23
I 23
 * Bring howmuch data into the cache, assuming that the smallest cache
 * line is 16 bytes.
E 23
 */
E 13
int
D 11
sumit()
E 11
I 11
D 13
sumit(int reset)
E 13
I 13
sumit(int howmuch)
E 13
E 11
{
D 13
	int	i, sum = 0;
E 13
I 13
D 24
	int	done, i, sum = 0;
E 24
I 24
	int	done, sum = 0;
E 24
E 13
D 23
	int	*d = data;
E 23
I 23
	register int *d = data;
E 23

I 24
#if 0
E 24
D 23
#define	TEN	sum+=d[0]+d[1]+d[2]+d[3]+d[4]+d[5]+d[6]+d[7]+d[8]+d[9];d+=10;
#define	FIFTY	TEN TEN TEN TEN TEN
#define	HUNDRED	FIFTY FIFTY
#define	HALFK	HUNDRED HUNDRED HUNDRED HUNDRED HUNDRED TEN sum+=*d++;sum+=*d++;
E 23
I 23
#define	A	sum+=d[0]+d[4]+d[8]+d[12]+d[16]+d[20]+d[24]+d[28]+\
		d[32]+d[36]+d[40]+d[44]+d[48]+d[52]+d[56]+d[60]+\
		d[64]+d[68]+d[72]+d[76]+d[80]+d[84]+d[88]+d[92]+\
		d[96]+d[100]+d[104]+d[108]+d[112]+d[116]+d[120]+d[124];\
		d+=128;
#define	TWOKB	A A A A
I 24
#else
#define	A	sum+=d[0]+d[1]+d[2]+d[3]+d[4]+d[5]+d[6]+d[7]+d[8]+d[9]+\
		d[10]+d[11]+d[12]+d[13]+d[14]+d[15]+d[16]+d[17]+d[18]+d[19]+\
		d[20]+d[21]+d[22]+d[23]+d[24]+d[25]+d[26]+d[27]+d[28]+d[29]+\
		d[30]+d[31]+d[32]+d[33]+d[34]+d[35]+d[36]+d[37]+d[38]+d[39]+\
		d[40]+d[41]+d[42]+d[43]+d[44]+d[45]+d[46]+d[47]+d[48]+d[49]+\
		d[50]+d[51]+d[52]+d[53]+d[54]+d[55]+d[56]+d[57]+d[58]+d[59]+\
		d[60]+d[61]+d[62]+d[63]+d[64]+d[65]+d[66]+d[67]+d[68]+d[69]+\
		d[70]+d[71]+d[72]+d[73]+d[74]+d[75]+d[76]+d[77]+d[78]+d[79]+\
		d[80]+d[81]+d[82]+d[83]+d[84]+d[85]+d[86]+d[87]+d[88]+d[89]+\
		d[90]+d[91]+d[92]+d[93]+d[94]+d[95]+d[96]+d[97]+d[98]+d[99]+\
		d[100]+d[101]+d[102]+d[103]+d[104]+\
		d[105]+d[106]+d[107]+d[108]+d[109]+\
		d[110]+d[111]+d[112]+d[113]+d[114]+\
		d[115]+d[116]+d[117]+d[118]+d[119]+\
		d[120]+d[121]+d[122]+d[123]+d[124]+d[125]+d[126]+d[127];\
		d+=128;	/* ints; bytes == 512 */
#define	TWOKB	A A A A
#endif
E 24
E 23

I 17
D 24
	if (!howmuch) return (0);
E 17
D 13
	for (i = process_size/sizeof(int); i > 512; i -= 512) {
I 11
		if (reset) d = data;
E 13
I 13
	for (done = 0, i = MAXSIZE/sizeof(int); i > 512; i -= 512) {
D 23
		if (done >= howmuch) d = data;
E 13
E 11
		HALFK
E 23
I 23
		if (done >= howmuch) return (sum);
E 24
I 24
	for (done = 0; done < howmuch; done += 2048) {
E 24
		TWOKB
E 23
I 13
D 24
		done += sizeof(int) * 512;
E 24
E 13
	}
	return (sum);
}
I 18
D 19

char *
getbuf(int size)
{
	int	fd = open("/dev/zero", 2);
	char	*buf;

	if (fd == -1) {
		return (malloc(size));
	}
	buf = mmap(0, size, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);
	if ((int)buf == -1) {
		perror("/dev/zero");
		return (malloc(size));
	}
	return (buf);
}
E 19
E 18
D 11

#define	SIZE	(1024 * 1024)

/*
 * This is a huge unrolled loop that is supposed to blow the instruction
 * and the data caches in an attempt to get more reproducible numbers.
 * It sort of works.
 */
int
caches()
{
I 9
#if 0
E 9
	int	i, sum = 0;
	char	*d = (char *)malloc(SIZE);
	char	*save = d;

	bzero(d, SIZE);

#define	TEN	sum+=d[0]+d[1]+d[2]+d[3]+d[4]+d[5]+d[6]+d[7]+d[8]+d[9];d+=10;
#define	FIFTY	TEN TEN TEN TEN TEN
#define	HUNDRED	FIFTY FIFTY
#define	HALFK	HUNDRED HUNDRED HUNDRED HUNDRED HUNDRED TEN sum+=*d++;sum+=*d++;
#define	KILO	HALFK HALFK

I 7
#if 0
E 7
	for (i = SIZE; i > 8192; i -= 8192) {
		KILO KILO KILO KILO
		KILO KILO KILO KILO
	}
I 7
#else
	for (i = SIZE; i > 1024; i -= 1024) {
		KILO 
	}
#endif
E 7
	free(save);
	return (sum);
I 9
#endif
E 9
}
E 11
E 2
I 1
E 1
