H12533
s 00000/00008/00937
d D 1.41 01/06/13 10:42:19 staelin 42 41
c Add new/improved handling of various available interfaces for
c random number generation lrand48()/rand()/random().
cC
cK15882
e
s 00008/00000/00937
d D 1.40 01/05/21 10:28:38 staelin 41 40
c Add new tests for existence of srand48 and drand48, with backoff to srand and drand if they aren't found
cC
cHhpli69.hpli.hpl.hp.com
cK24485
e
s 00028/00029/00909
d D 1.39 00/07/31 16:41:17 staelin 40 39
c - Removed OS-based check for RUSAGE, now rely on build script to provide #define flag
c - Changed return foo; to return (foo); throughout file
c - In tvsub, changed "while(diff->tv_usec < 0 && ...)" to "if(...) { ... assert(diff->tv_usec >= 0);}"
c - Removed checks for zero time before each call to insertsort(), the check is now done
c   inside insertsort()
cC
cK15882
e
s 00001/00001/00937
d D 1.38 00/07/03 16:21:39 staelin 39 38
c - Try to force optimizers to leave benchmark code alone by marking dummy variable
c   as 'volatile'.  This should hopefully prevent them from optimizing away loops whose
c   sole purpose (apparently) is to update this variable via use_pointer() or use_int().
cC
cK21732
e
s 00003/00002/00935
d D 1.37 00/06/04 11:58:30 staelin 38 37
c Fix bug with unsigned arithmetic which made the 'enough' computations unstable.
c Basically, the difference of two unsigned integers is always non-negative, so
c ABS(a - b) doesn't return the absolute value of the difference when b is larger
c than a.
cC
cK20845
cZ+03:00
e
s 00115/00021/00822
d D 1.36 00/02/02 09:57:42 staelin 37 36
c - Added code to handle bad results in the various
c   result handling routines.
c - Cleaned up some variable/function types to keep
c   things uniform
c - Added some code for Windows timing
cC
cHhpli8.hpli.hpl.hp.com
cK16347
cZ+02:00
e
s 00010/00000/00833
d D 1.35 99/03/20 23:38:34 lm 36 35
c print_results() function.
cC
cK57041
cZ-08:00
e
s 00001/00001/00832
d D 1.34 98/07/21 18:41:28 lm 35 34
c ftiming bug caused core dumps.
cK45967
e
s 00014/00003/00819
d D 1.33 98/07/02 17:33:18 lm 34 33
c Glibc won't let you assign stderr to a global.
cK45976
e
s 00004/00003/00818
d D 1.32 98/06/29 22:37:42 lm 33 32
c Redo to compile clean with -Wall.
cHlm.bitmover.com
cK16719
e
s 00012/00020/00809
d D 1.31 98/06/26 10:01:23 lm 32 31
c Carl's bug fix for the alpha mhz.
cHwork
cK18041
cZ-07:00
e
s 00131/00112/00698
d D 1.30 98/05/07 15:34:47 staelin 31 30
c - changed result_t to a structure, and updated relevent routines
c - added saved state for results, and save_median() save_minimum() routines
c - fixed a bug in l_overhead() experimentation and calculation
c - changed #ifdef hpux to #if defined(hpux) || defined(__hpux)
cHhpisc8.lempel
cK30075
cZ-00:00
e
s 00020/00025/00790
d D 1.29 98/03/06 12:01:09 lm 30 29
c simplify; fix bug in sort. (Carl).
cK05444
e
s 00002/00003/00813
d D 1.28 97/11/19 21:10:51 lm 29 28
c some carl thing.
cK04882
e
s 00008/00007/00808
d D 1.27 97/10/31 18:06:23 lm 28 27
c use_result -> use_int/pointer
cK10037
e
s 00049/00038/00766
d D 1.26 97/10/30 18:37:23 lm 27 26
c From Carl.
cK03618
cZ-08:00
e
s 00002/00002/00802
d D 1.25 97/10/25 10:53:06 lm 26 25
c carl's stuff
cK39735
e
s 00044/00022/00760
d D 1.24 97/10/19 23:40:55 lm 25 24
c fix a few bugs.
cK37952
e
s 00029/00013/00753
d D 1.23 97/06/25 10:25:01 lm 24 23
c ifdef TOUCH
cK51056
e
s 00003/00008/00763
d D 1.22 97/06/23 23:27:09 lm 23 22
c carl's diffs.
cK34473
e
s 00001/00001/00770
d D 1.21 97/06/16 19:18:52 lm 22 21
c 5000
cK38651
e
s 00009/00003/00762
d D 1.20 97/06/16 19:05:50 lm 21 20
c lint
cK39733
e
s 00003/00003/00762
d D 1.19 97/06/15 23:13:12 lm 20 19
c namespace
cK28694
e
s 00011/00009/00754
d D 1.18 97/06/15 22:38:58 lm 19 18
c lint
cK29334
e
s 00224/00013/00539
d D 1.17 97/06/14 18:23:18 lm 18 17
c more loop junk.
cK26570
e
s 00044/00032/00508
d D 1.16 97/06/14 12:20:26 lm 17 16
c carl's changes.
cK25545
e
s 00046/00041/00494
d D 1.15 97/06/13 20:26:59 lm 16 15
c enough
cK11116
e
s 00111/00048/00424
d D 1.14 97/06/12 21:30:06 lm 15 14
c new bench.h macros.
cK09595
e
s 00031/00010/00441
d D 1.13 97/04/23 22:15:40 lm 14 13
c mostly just some stats in micro().
cK52190
cZ-07:00
e
s 00001/00000/00450
d D 1.12 97/01/27 14:06:50 lm 13 12
c lint
cK24509
e
s 00028/00004/00422
d D 1.11 96/12/16 12:32:12 lm 12 11
c *** empty log message ***
cK23598
e
s 00025/00003/00401
d D 1.10 96/11/13 16:09:37 lm 11 10
c tuning.
cK47690
e
s 00207/00138/00197
d D 1.9 96/11/11 03:36:51 lm 10 9
c Auto adjusting changes.
cK17037
e
s 00041/00003/00294
d D 1.8 96/11/08 20:06:19 lm 9 8
c gcc -Wall cleanup.
cK64643
e
s 00004/00001/00293
d D 1.7 96/01/22 23:58:23 lm 8 7
c make adjust return the new timespent.
cK24087
cZ-08:00
e
s 00031/00000/00263
d D 1.6 95/08/24 20:30:30 lm 7 6
c delta/Delta
cK14753
e
s 00007/00002/00256
d D 1.5 95/08/22 15:32:31 lm 6 5
c automagic adjustment of output.
cK40255
cZ-07:00
e
s 00006/00001/00252
d D 1.4 95/03/10 18:19:39 lm 5 4
c lint
cK31472
e
s 00014/00000/00239
d D 1.3 95/02/14 10:57:34 lm 4 3
c add nano interface.
cK24794
e
s 00212/00029/00027
d D 1.2 94/11/18 00:52:52 lm 3 2
c getting close to net release.
cK07298
cZ-08:00
e
s 00056/00000/00000
d D 1.1 92/06/24 14:09:15 lm 2 1
c date and time created 92/06/24 21:09:15 by lm
cK08376
e
s 00000/00000/00000
d D 1.0 92/06/24 14:09:14 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK13663
cPsrc/lib_timing.c
cR4ef3c93154a38206
cV4
cX0x21
cZ-07:00
e
u
U
f e 0
f x 0x21
t
T
I 2
/*
D 3
 * %W% %G%
E 3
I 3
D 10
 * $Id$
E 10
I 10
 * a timing utilities library
E 10
 *
D 10
 * Copyright (c) 1994 Larry McVoy.   
E 10
I 10
 * Requires 64bit integers to work.
E 10
 *
D 10
 * All output goes to stderr.
E 10
I 10
D 31
 * $Id$
E 31
I 31
D 32
 * $Id: lib_timing.c,v 1.29 1998/03/06 20:01:09 lm Exp $
E 32
I 32
 * %W% %@%
E 32
E 31
 *
D 32
 * Copyright (c) 1994-1996 Larry McVoy.
E 32
I 32
 * Copyright (c) 1994-1998 Larry McVoy.
E 32
E 10
E 3
 */
I 3
D 10
#include "bench.h"
E 10
D 15
#include <stdio.h>
E 3
#include <signal.h>
I 3
#include <unistd.h>
E 3
#include <sys/types.h>
#include <sys/time.h>
I 10
#include "timing.h"
E 15
I 14
#define	 _LIB /* bench.h needs this */
E 14
#include "bench.h"
E 10

I 5
D 10
#ifdef	sun
extern	int	gettimeofday();
extern	int	fprintf();
#endif

E 5
I 3
#ifdef	RUSAGE
#include <sys/resource.h>

#define	secs(tv)	(tv.tv_sec + tv.tv_usec / 1000000.0)
#endif

E 10
#define	nz(x)	((x) == 0 ? 1 : (x))
D 10
#define	MB	(1024*1024.0)
#define	KB	(1024.0)
E 10

D 10
#ifdef	RUSAGE
E 10
I 10
/*
 * I know you think these should be 2^10 and 2^20, but people are quoting
 * disk sizes in powers of 10, and bandwidths are all power of ten.
 * Deal with it.
 */
#define	MB	(1000*1000.0)
#define	KB	(1000.0)
E 10

D 10
#define	mine(f)		(ru_stop.f - ru_start.f)
E 10
I 10
D 15
static struct timeval start_tv, stop_tv;
E 15
I 15
D 33
static struct timeval start_tv, stop_tv, dummy_tv;
E 33
I 33
static struct timeval start_tv, stop_tv;
E 33
E 15
D 34
FILE	*ftiming = stderr;
E 34
I 34
FILE		*ftiming;
E 34
D 26
static	uint64	dummy;
E 26
I 26
D 27
uint64		use_result_dummy;
E 27
I 27
D 39
uint64		use_result_dummy;	/* !static for optimizers. */
E 39
I 39
volatile uint64	use_result_dummy;	/* !static for optimizers. */
E 39
E 27
E 26
I 15
D 19
static	double	timing_overhead = 0;
E 19
static	uint64	iterations;
I 19
static	void	init_timing(void);
E 19
E 15
E 10

I 31
#if defined(hpux) || defined(__hpux)
#include <sys/mman.h>
#endif
E 31
I 15

I 21
D 30
#ifndef	hpux
E 30
I 30
D 37
#if !defined(hpux) && !defined(__hpux)
E 37
I 37
D 40
#if !defined(hpux) && !defined(__hpux) && !defined(WIN32)
E 37
E 30
E 21
#define RUSAGE
I 21
#endif
E 40
E 21
#ifdef	RUSAGE
#include <sys/resource.h>
D 20
#define	secs(tv)	(tv.tv_sec + tv.tv_usec / 1000000.0)
E 20
I 20
#define	SECS(tv)	(tv.tv_sec + tv.tv_usec / 1000000.0)
E 20
#define	mine(f)		(int)(ru_stop.f - ru_start.f)

D 19
static struct rusage ru_start, ru_stop, ru_dummy;
E 19
I 19
static struct rusage ru_start, ru_stop;
E 19

void
rusage(void)
{
	double  sys, user, idle;
	double  per;

D 20
	sys = secs(ru_stop.ru_stime) - secs(ru_start.ru_stime);
	user = secs(ru_stop.ru_utime) - secs(ru_start.ru_utime);
E 20
I 20
	sys = SECS(ru_stop.ru_stime) - SECS(ru_start.ru_stime);
	user = SECS(ru_stop.ru_utime) - SECS(ru_start.ru_utime);
E 20
	idle = timespent() - (sys + user);
	per = idle / timespent() * 100;
I 34
	if (!ftiming) ftiming = stderr;
E 34
	fprintf(ftiming, "real=%.2f sys=%.2f user=%.2f idle=%.2f stall=%.0f%% ",
	    timespent(), sys, user, idle, per);
	fprintf(ftiming, "rd=%d wr=%d min=%d maj=%d ctx=%d\n",
	    mine(ru_inblock), mine(ru_oublock),
	    mine(ru_minflt), mine(ru_majflt),
	    mine(ru_nvcsw) + mine(ru_nivcsw));
}

#endif	/* RUSAGE */
E 15
D 10
static struct rusage ru_start, ru_stop;

E 10
I 10
/*
 * Redirect output someplace else.
 */
E 10
void
D 10
rusage()
E 10
I 10
timing(FILE *out)
E 10
{
D 10
	struct rusage r;
	double  sys, user, idle;
	double  per;
	double  timespent();

	sys = secs(ru_stop.ru_stime) - secs(ru_start.ru_stime);
	user = secs(ru_stop.ru_utime) - secs(ru_start.ru_utime);
	idle = timespent() - (sys + user);
	per = idle / timespent() * 100;
	fprintf(stderr, "real=%.2f sys=%.2f user=%.2f idle=%.2f stall=%.0f%% ",
	    timespent(), sys, user, idle, per);
	fprintf(stderr, "rd=%d wr=%d min=%d maj=%d ctx=%d\n",
	    mine(ru_inblock), mine(ru_oublock),
	    mine(ru_minflt), mine(ru_majflt),
	    mine(ru_nvcsw) + mine(ru_nivcsw));
E 10
I 10
	ftiming = out;
E 10
}

D 10
#endif

static struct timeval start_tv, stop_tv;

E 10
E 3
/*
D 3
 * utilities for timing
E 3
I 3
D 10
 * Start timing now.
E 10
I 10
D 34
 * Start ftiming now.
E 34
I 34
 * Start timing now.
E 34
E 10
E 3
 */
D 3
#include "stdio.h"
#include "sys/types.h"
#include "sys/time.h"
E 3
I 3
void
D 10
start()
E 10
I 10
start(struct timeval *tv)
E 10
{
D 10
	(void) gettimeofday(&start_tv, (struct timezone *) 0);
E 10
I 10
	if (tv == NULL) {
		tv = &start_tv;
	}
D 15
	(void) gettimeofday(tv, (struct timezone *) 0);
E 15
E 10
#ifdef	RUSAGE
	getrusage(RUSAGE_SELF, &ru_start);
#endif
I 15
	(void) gettimeofday(tv, (struct timezone *) 0);
E 15
}
E 3

D 3
static struct timeval t1, t2;
E 3
I 3
/*
I 15
D 17
 * Fake one for timing_overhead
 */
static void
timing_start(struct timeval *tv)
{
	if (tv == NULL) {
		tv = &dummy_tv;
	}
	(void) gettimeofday(tv, (struct timezone *) 0);
}

/*
E 17
E 15
D 10
 * Stop timing and return real time in microseconds.
E 10
I 10
D 34
 * Stop ftiming and return real time in microseconds.
E 34
I 34
 * Stop timing and return real time in microseconds.
E 34
E 10
 */
D 10
ulong
stop()
E 10
I 10
uint64
stop(struct timeval *begin, struct timeval *end)
E 10
{
D 30
	struct timeval tdiff;
I 10
	uint64	m;
E 10
E 3

E 30
D 3
start() {
	gettimeofday(&t1, (struct timezone *) 0);
E 3
I 3
D 10
	(void) gettimeofday(&stop_tv, (struct timezone *) 0);
E 10
I 10
	if (end == NULL) {
		end = &stop_tv;
	}
	(void) gettimeofday(end, (struct timezone *) 0);
E 10
#ifdef	RUSAGE
	getrusage(RUSAGE_SELF, &ru_stop);
#endif

D 10
	tvsub(&tdiff, &stop_tv, &start_tv);
	return (tdiff.tv_sec * 1000000 + tdiff.tv_usec);
E 10
I 10
	if (begin == NULL) {
		begin = &start_tv;
	}
D 30
	tvsub(&tdiff, end, begin);
	m = tdiff.tv_sec;
	m *= 1000000;
	m += tdiff.tv_usec;
	return (m);
E 30
I 30
	return tvdelta(begin, end);
E 30
E 10
E 3
}

I 15
D 16
/*
 * Figure out the timing overhead.  This has to track bench.h
 */
double
t_overhead()
{
	struct timeval foo;
	int	N, usecs;

	if (timing_overhead) return (timing_overhead);
	if (getenv("TIMING_O")) {
		timing_overhead = atof(getenv("TIMING_O"));
		return (timing_overhead);
	}
	timing_start(0);
	LOOP_FIRST(N, usecs, ENOUGH);
	timing_start(0);
	LOOP_LAST(N, usecs, ENOUGH);
	timing_overhead = usecs;
	timing_overhead /= N;
	return (timing_overhead);
}

/*
 * Figure out how long to run it.
 * If enough == 0, then they want us to figure it out.
 * If enough is !0 then return it unless we think it is too short.
 */
int
get_enough(int enough)
{
	if (!enough) {
		if (getenv("ENOUGH")) {
			return atoi(getenv("ENOUGH"));
		}
		return (SHORT);
	}
	if (enough < 50000) return (50000);
	return (enough);
}

E 16
E 15
D 3
stop() {
	gettimeofday(&t2, (struct timezone *) 0);
E 3
I 3
D 10
ulong
now()
E 10
I 10
uint64
now(void)
E 10
{
	struct timeval t;
I 10
	uint64	m;
E 10

	(void) gettimeofday(&t, (struct timezone *) 0);
D 10
	return (t.tv_usec / 100);
E 10
I 10
	m = t.tv_sec;
	m *= 1000000;
	m += t.tv_usec;
	return (m);
E 10
E 3
}

I 7
D 10
ulong
delta()
E 10
I 10
double
Now(void)
E 10
{
I 10
	struct timeval t;

	(void) gettimeofday(&t, (struct timezone *) 0);
	return (t.tv_sec * 1000000.0 + t.tv_usec);
}

uint64
delta(void)
{
E 10
	static struct timeval last;
	struct timeval t;
	struct timeval diff;
I 10
	uint64	m;
E 10
D 9
	ulong	tmp;
E 9

	(void) gettimeofday(&t, (struct timezone *) 0);
	if (last.tv_usec) {
		tvsub(&diff, &t, &last);
		last = t;
D 10
		return (diff.tv_sec * 1000000 + diff.tv_usec);
E 10
I 10
		m = diff.tv_sec;
		m *= 1000000;
		m += diff.tv_usec;
		return (m);
E 10
	} else {
		last = t;
		return (0);
	}
}

double
D 10
Delta()
E 10
I 10
Delta(void)
E 10
{
	struct timeval t;
	struct timeval diff;
D 9
	ulong	tmp;
E 9

	(void) gettimeofday(&t, (struct timezone *) 0);
	tvsub(&diff, &t, &start_tv);
	return (diff.tv_sec + diff.tv_usec / 1000000.0);
}

E 7
D 3
ptime(bytes) {
	ptransfer(bytes, &t1, &t2);
E 3
I 3
D 15
/*
 * Adjust time spent by usec amount.
 *
 * XXX - tv_usec may be too big after this.
 */
E 15
D 8
void
E 8
I 8
D 10
ulong
E 8
adjust(usec)
	int	usec;
E 10
I 10
void
D 15
adjust(int usec)
E 15
I 15
save_n(uint64 n)
E 15
E 10
{
I 8
D 10
	struct	timeval tdiff;
E 10
E 8
D 15
	int     sec = usec / 1000000;
E 15
I 15
	iterations = n;
}
E 15

D 15
	usec -= sec * 1000000;
	stop_tv.tv_sec += sec;
	stop_tv.tv_usec += usec;
E 15
I 15
uint64
get_n(void)
{
D 25
	return ((uint64)iterations);
E 25
I 25
	return (iterations);
E 25
E 15
I 8
D 10
	tvsub(&tdiff, &stop_tv, &start_tv);
	return (tdiff.tv_sec * 1000000 + tdiff.tv_usec);
E 10
E 8
E 3
}

I 12
/*
 * Make the time spend be usecs.
 */
I 14
void
E 14
settime(uint64 usecs)
{
D 21
	bzero(&start_tv, sizeof(start_tv));
E 21
I 21
	bzero((void*)&start_tv, sizeof(start_tv));
E 21
	stop_tv.tv_sec = usecs / 1000000;
	stop_tv.tv_usec = usecs % 1000000;
I 13
D 14
	return (0);
E 14
E 13
}

E 12
I 9
D 10
/*
 * Make the time spent be smaller by a factor of n.
 */
E 10
E 9
D 3
ptransfer(bytes, t0, t1)
	struct timeval *t0, *t1;
E 3
I 3
void
I 9
D 10
divide(int n)
E 10
I 10
bandwidth(uint64 bytes, uint64 times, int verbose)
E 10
{
D 10
	struct	timeval tdiff;
	ulong	usecs;
E 10
I 10
	struct timeval tdiff;
	double  mb, secs;
E 10

	tvsub(&tdiff, &stop_tv, &start_tv);
D 10
	start_tv.tv_sec = start_tv.tv_usec = 0;
	usecs = tdiff.tv_sec * 1000000 + tdiff.tv_usec;
	usecs /= n;
	stop_tv.tv_sec = usecs / 1000000;
	stop_tv.tv_usec = usecs % 1000000;
E 10
I 10
	secs = tdiff.tv_sec;
	secs *= 1000000;
	secs += tdiff.tv_usec;
	secs /= 1000000;
	secs /= times;
	mb = bytes / MB;
I 35
	if (!ftiming) ftiming = stderr;
E 35
	if (verbose) {
I 34
D 35
		if (!ftiming) ftiming = stderr;
E 35
E 34
		(void) fprintf(ftiming,
		    "%.4f MB in %.4f secs, %.4f MB/sec\n",
		    mb, secs, mb/secs);
	} else {
		if (mb < 1) {
D 11
			(void) fprintf(ftiming, "%.8f ", mb);
E 11
I 11
			(void) fprintf(ftiming, "%.6f ", mb);
E 11
		} else {
			(void) fprintf(ftiming, "%.2f ", mb);
		}
		if (mb / secs < 1) {
D 11
			(void) fprintf(ftiming, "%.8f\n", mb/secs);
E 11
I 11
			(void) fprintf(ftiming, "%.6f\n", mb/secs);
E 11
		} else {
			(void) fprintf(ftiming, "%.2f\n", mb/secs);
		}
	}
E 10
}

void
E 9
D 10
bandwidth(bytes, verbose)
D 5
	int	bytes;
E 5
I 5
	int	bytes, verbose;
E 10
I 10
kb(uint64 bytes)
E 10
E 5
E 3
{
	struct timeval td;
D 3
	double   s, bs;
E 3
I 3
	double  s, bs;
E 3

D 3
	tvsub(&td, t1, t0);
	s = td.tv_sec + td.tv_usec/1000000.0;
#define	nz(x)	((x) == 0 ? 1 : (x))
#define	MB	(1024*1024.0)
#define	KB	(1024.0)
E 3
I 3
	tvsub(&td, &stop_tv, &start_tv);
	s = td.tv_sec + td.tv_usec / 1000000.0;
E 3
	bs = bytes / nz(s);
I 34
	if (!ftiming) ftiming = stderr;
E 34
D 3
	printf("%.2f MB in %.2f seconds (%.2f KB/sec)\n",
	    bytes / MB, s, bs / KB);
E 3
I 3
D 10
	if (verbose) {
D 6
		(void) fprintf(stderr, "%.2f MB in %.2f secs, %.2f KB/sec\n",
		    bytes / MB, s, bs / KB);
E 6
I 6
		if ((bs / KB) > 1024) {
			(void) fprintf(stderr, "%.2f MB in %.2f secs, %.2f MB/sec\n",
			    bytes / MB, s, bs / MB);
		} else {
			(void) fprintf(stderr, "%.2f MB in %.2f secs, %.2f KB/sec\n",
			    bytes / MB, s, bs / KB);
		}
E 6
	} else {
D 9
		(void) fprintf(stderr, "%.2f %.2f\n",
E 9
I 9
		(void) fprintf(stderr, "%.6f %.1f\n",
E 9
		    bytes / MB, bs / MB);
	}
E 10
I 10
	(void) fprintf(ftiming, "%.0f KB/sec\n", bs / KB);
E 10
E 3
}

I 3
void
D 10
kb(bytes)
	int	bytes;
E 10
I 10
mb(uint64 bytes)
E 10
{
	struct timeval td;
	double  s, bs;

	tvsub(&td, &stop_tv, &start_tv);
	s = td.tv_sec + td.tv_usec / 1000000.0;
	bs = bytes / nz(s);
I 34
	if (!ftiming) ftiming = stderr;
E 34
D 10
	(void) fprintf(stderr, "%.0f KB/sec\n", bs / KB);
E 10
I 10
	(void) fprintf(ftiming, "%.2f MB/sec\n", bs / MB);
E 10
}

void
D 10
mb(bytes)
	int	bytes;
E 10
I 10
latency(uint64 xfers, uint64 size)
E 10
{
	struct timeval td;
D 10
	double  s, bs;
E 10
I 10
	double  s;
E 10

I 34
	if (!ftiming) ftiming = stderr;
E 34
	tvsub(&td, &stop_tv, &start_tv);
	s = td.tv_sec + td.tv_usec / 1000000.0;
D 10
	bs = bytes / nz(s);
	(void) fprintf(stderr, "%.2f MB/sec\n", bs / MB);
}

void
latency(xfers, size)
	int	xfers, size;
{
	struct timeval td;
	double  s;

	tvsub(&td, &stop_tv, &start_tv);
	s = td.tv_sec + td.tv_usec / 1000000.0;
	fprintf(stderr,
	    "%d xfers in %.2f secs, %.4f millisec/xfer, %.2f KB/sec\n",
	    xfers, s, s * 1000 / xfers,
	    (xfers * size) / (1024. * s));
E 10
I 10
D 12
	fprintf(ftiming,
	    "%d %dKB xfers in %.2f secs, %.4f millisec/xfer, %.2f MB/sec\n",
	    (int) xfers, (int) (size / KB), s, s * 1000 / xfers,
	    (xfers * size) / (MB * s));
E 12
I 12
	if (xfers > 1) {
		fprintf(ftiming, "%d %dKB xfers in %.2f secs, ",
		    (int) xfers, (int) (size / KB), s);
	} else {
		fprintf(ftiming, "%.1fKB in ", size / KB);
	}
	if ((s * 1000 / xfers) > 100) {
		fprintf(ftiming, "%.0f millisec%s, ",
		    s * 1000 / xfers, xfers > 1 ? "/xfer" : "s");
	} else {
		fprintf(ftiming, "%.4f millisec%s, ",
		    s * 1000 / xfers, xfers > 1 ? "/xfer" : "s");
	}
	if (((xfers * size) / (MB * s)) > 1) {
		fprintf(ftiming, "%.2f MB/sec\n", (xfers * size) / (MB * s));
	} else {
		fprintf(ftiming, "%.2f KB/sec\n", (xfers * size) / (KB * s));
	}
E 12
E 10
}

void
D 10
context(xfers)
	int	xfers;
E 10
I 10
context(uint64 xfers)
E 10
{
	struct timeval td;
	double  s;

	tvsub(&td, &stop_tv, &start_tv);
	s = td.tv_sec + td.tv_usec / 1000000.0;
I 34
	if (!ftiming) ftiming = stderr;
E 34
D 10
	fprintf(stderr,
E 10
I 10
	fprintf(ftiming,
E 10
	    "%d context switches in %.2f secs, %.0f microsec/switch\n",
D 10
	    xfers, s, s * 1000000 / xfers);
E 10
I 10
	    (int)xfers, s, s * 1000000 / xfers);
E 10
}

void
I 4
D 10
nano(s, n)
	char	*s;
	int	n;
E 10
I 10
nano(char *s, uint64 n)
E 10
{
	struct timeval td;
D 10
	double	micro;
E 10
I 10
	double  micro;
E 10

	tvsub(&td, &stop_tv, &start_tv);
	micro = td.tv_sec * 1000000 + td.tv_usec;
	micro *= 1000;
I 34
	if (!ftiming) ftiming = stderr;
E 34
D 10
	fprintf(stderr, "%s: %.0f nanoseconds\n", s, micro / n);
E 10
I 10
	fprintf(ftiming, "%s: %.0f nanoseconds\n", s, micro / n);
E 10
}

void
E 4
D 10
micro(s, n)
	char	*s;
	int	n;
E 10
I 10
micro(char *s, uint64 n)
E 10
{
	struct timeval td;
D 10
	int	micro;
E 10
I 10
	double	micro;
E 10

	tvsub(&td, &stop_tv, &start_tv);
	micro = td.tv_sec * 1000000 + td.tv_usec;
D 10
	fprintf(stderr, "%s: %d microseconds\n", s, micro / n);
E 10
I 10
	micro /= n;
I 34
	if (!ftiming) ftiming = stderr;
E 34
D 11
	fprintf(ftiming, "%s: %.3f microseconds\n", s, micro);
E 11
I 11
D 14
	if (micro >= 10) {
		fprintf(ftiming, "%s: %.0f microseconds\n", s, micro);
	} else {
E 14
I 14
	fprintf(ftiming, "%s: %.4f microseconds\n", s, micro);
#if 0
	if (micro >= 100) {
		fprintf(ftiming, "%s: %.1f microseconds\n", s, micro);
	} else if (micro >= 10) {
E 14
		fprintf(ftiming, "%s: %.3f microseconds\n", s, micro);
I 14
	} else {
		fprintf(ftiming, "%s: %.4f microseconds\n", s, micro);
E 14
	}
I 14
#endif
E 14
E 11
E 10
}

void
I 11
micromb(uint64 sz, uint64 n)
{
	struct timeval td;
	double	mb, micro;

	tvsub(&td, &stop_tv, &start_tv);
	micro = td.tv_sec * 1000000 + td.tv_usec;
	micro /= n;
	mb = sz;
	mb /= MB;
I 34
	if (!ftiming) ftiming = stderr;
E 34
	if (micro >= 10) {
		fprintf(ftiming, "%.6f %.0f\n", mb, micro);
	} else {
		fprintf(ftiming, "%.6f %.3f\n", mb, micro);
	}
}

void
E 11
D 10
milli(s, n)
	char	*s;
	int	n;
E 10
I 10
milli(char *s, uint64 n)
E 10
{
	struct timeval td;
D 10
	int	milli;
E 10
I 10
	uint64 milli;
E 10

	tvsub(&td, &stop_tv, &start_tv);
	milli = td.tv_sec * 1000 + td.tv_usec / 1000;
D 10
	fprintf(stderr, "%s: %d milliseconds\n", s, milli / n);
E 10
I 10
	milli /= n;
I 34
	if (!ftiming) ftiming = stderr;
E 34
	fprintf(ftiming, "%s: %d milliseconds\n", s, (int)milli);
E 10
}

void
D 10
ptime(n)
	int	n;
E 10
I 10
ptime(uint64 n)
E 10
{
	struct timeval td;
	double  s;

	tvsub(&td, &stop_tv, &start_tv);
	s = td.tv_sec + td.tv_usec / 1000000.0;
I 34
	if (!ftiming) ftiming = stderr;
E 34
D 10
	fprintf(stderr,
	    "%d in %.2f secs, %.0f microseconds each\n", n, s, s * 1000000 / n);
E 10
I 10
	fprintf(ftiming,
	    "%d in %.2f secs, %.0f microseconds each\n",
	    (int)n, s, s * 1000000 / n);
E 10
}

I 15
uint64
tvdelta(struct timeval *start, struct timeval *stop)
{
	struct timeval td;
	uint64	usecs;

	tvsub(&td, stop, start);
	usecs = td.tv_sec;
	usecs *= 1000000;
	usecs += td.tv_usec;
D 37
	return (usecs);
E 37
I 37
D 40
	return usecs;
E 40
I 40
	return (usecs);
E 40
E 37
}

E 15
void
E 3
D 10
tvsub(tdiff, t1, t0)
	struct timeval *tdiff, *t1, *t0;
E 10
I 10
tvsub(struct timeval * tdiff, struct timeval * t1, struct timeval * t0)
E 10
{
D 3

E 3
	tdiff->tv_sec = t1->tv_sec - t0->tv_sec;
D 3
	if ( t0->tv_usec > t1->tv_usec ) {
		tdiff->tv_sec--; 
		tdiff->tv_usec = (1000000 - t0->tv_usec) + t1->tv_usec;
	} else
		tdiff->tv_usec = t1->tv_usec - t0->tv_usec;
	
E 3
I 3
	tdiff->tv_usec = t1->tv_usec - t0->tv_usec;
D 37
	if (tdiff->tv_usec < 0)
		tdiff->tv_sec--, tdiff->tv_usec += 1000000;
E 37
I 37
D 40
	while (tdiff->tv_usec < 0 && tdiff->tv_sec > 0) {
E 40
I 40
	if (tdiff->tv_usec < 0 && tdiff->tv_sec > 0) {
E 40
		tdiff->tv_sec--;
		tdiff->tv_usec += 1000000;
I 40
		assert(tdiff->tv_usec >= 0);
E 40
	}
I 40

E 40
	/* time shouldn't go backwards!!! */
	if (tdiff->tv_usec < 0 || t1->tv_sec < t0->tv_sec) {
		tdiff->tv_sec = 0;
		tdiff->tv_usec = 0;
	}
E 37
E 3
}
I 3

I 15
uint64
D 19
usecs_spent()
E 19
I 19
D 25
usecs_spent(void)
E 25
I 25
gettime(void)
E 25
E 19
{
	return (tvdelta(&start_tv, &stop_tv));
}

E 15
double
D 10
timespent()
E 10
I 10
D 14
timespent(void)
E 14
I 14
D 19
timespent()
E 19
I 19
timespent(void)
E 19
E 14
E 10
{
	struct timeval td;

	tvsub(&td, &stop_tv, &start_tv);
D 10
	return (td.tv_sec + td.tv_usec / 1000000);
E 10
I 10
	return (td.tv_sec + td.tv_usec / 1000000.0);
E 10
}
I 9

I 10
static	char	p64buf[10][20];
static	int	n;

char	*
p64(uint64 big)
{
	char	*s = p64buf[n++];

	if (n == 10) n = 0;
#ifdef  linux
	{
        int     *a = (int*)&big;

        if (a[1]) {
                sprintf(s, "0x%x%08x", a[1], a[0]);
        } else {
                sprintf(s, "0x%x", a[0]);
        }
	}
#endif
#ifdef	__sgi
        sprintf(s, "0x%llx", big);
#endif
	return (s);
}

char	*
p64sz(uint64 big)
{
	double	d = big;
	char	*tags = " KMGTPE";
	int	t = 0;
	char	*s = p64buf[n++];

	if (n == 10) n = 0;
	while (d > 512) t++, d /= 1024;
	if (d == 0) {
		return ("0");
	}
	if (d < 100) {
		sprintf(s, "%.4f%c", d, tags[t]);
	} else {
		sprintf(s, "%.2f%c", d, tags[t]);
	}
	return (s);
}

E 10
char
D 14
last(s)
	char	*s;
E 14
I 14
last(char *s)
E 14
{
	while (*s++)
		;
	return (s[-2]);
}

int
D 14
bytes(s)
	char	*s;
E 14
I 14
bytes(char *s)
E 14
{
	int	n = atoi(s);

	if ((last(s) == 'k') || (last(s) == 'K'))
		n *= 1024;
	if ((last(s) == 'm') || (last(s) == 'M'))
		n *= (1024 * 1024);
	return (n);
}

I 10
D 27
void
E 27
D 28
use_result(uint64 result)
{
D 26
	dummy = result;
E 26
I 26
	use_result_dummy += result;
E 26
}
E 28
I 28
void
use_int(int result) { use_result_dummy += result; }
E 28

I 18
void
I 28
use_pointer(void *result) { use_result_dummy += (int)result; }

void
E 28
D 31
insertinit(result_t *r, int n)
E 31
I 31
insertinit(result_t *r)
E 31
{
	int	i;

D 30
	for (i = 0; i < n; r[i++].u = 0);
E 30
I 30
D 31
	for (i = 0; i < n; i++) {
		r[i].u = 0;
		r[i].n = 1;
E 31
I 31
	r->N = 0;
	for (i = 0; i < TRIES; i++) {
		r->u[i] = 0;
		r->n[i] = 1;
E 31
	}
E 30
}

E 18
I 14
D 15
#if 0
E 15
/* biggest to smallest */
I 16
void
E 16
D 18
insertsort(double *d, int l, double val)
E 18
I 18
D 31
insertsort(uint64 u, uint64 n, result_t *r, int l)
E 31
I 31
insertsort(uint64 u, uint64 n, result_t *r)
E 31
E 18
{
	int	i, j;

I 40
	if (u == 0) return;

E 40
D 31
	for (i = 0; i < l; ++i) {
D 18
		if (val > d[i]) {
E 18
I 18
D 30
		if (u > r[i].u) {
E 30
I 30
		if (u/(double)n > r[i].u/(double)r[i].n) {
E 30
E 18
			for (j = l-1; j > i; --j) {
D 18
				d[j] = d[j-1];
E 18
I 18
				r[j] = r[j-1];
E 31
I 31
	for (i = 0; i < r->N; ++i) {
		if (u/(double)n > r->u[i]/(double)r->n[i]) {
			for (j = r->N; j > i; --j) {
				r->u[j] = r->u[j-1];
				r->n[j] = r->n[j-1];
E 31
E 18
			}
D 18
			d[i] = val;
E 18
I 18
D 31
			r[i].u = u;
			r[i].n = n;
E 18
			return;
E 31
I 31
			break;
E 31
		}
	}
I 31
	r->u[i] = u;
	r->n[i] = n;
	r->N++;
E 31
}
I 16
D 24

I 17
D 19
morefds()
E 19
I 19
void
morefds(void)
E 19
{
#ifdef	RLIMIT_NOFILE
	struct	rlimit r;

	getrlimit(RLIMIT_NOFILE, &r);
	r.rlim_cur = r.rlim_max;
	setrlimit(RLIMIT_NOFILE, &r);
#endif
}

E 24
E 17
D 31
/*
I 17
 * Fake one for timing_overhead
 */
static void
timing_start(struct timeval *tv)
E 31
I 31

static result_t results;

void
I 36
print_results(void)
{
	int	i;

	for (i = 0; i < results.N; ++i) {
		fprintf(stderr, "%.2f ", (double)results.u[i]/results.n[i]);
	}
}

void
E 36
get_results(result_t *r)
E 31
{
D 31
	if (tv == NULL) {
		tv = &dummy_tv;
E 31
I 31
	*r = results;
}

void
save_results(result_t *r)
{
	results = *r;
	save_median();
}

void
save_minimum()
{
D 37
	save_n(results.n[results.N - 1]);
	settime(results.u[results.N - 1]);
E 37
I 37
	if (results.N == 0) {
		save_n(1);
		settime(0);
	} else {
		save_n(results.n[results.N - 1]);
		settime(results.u[results.N - 1]);
	}
E 37
}

void
save_median()
{
	int	i = results.N / 2;
	uint64	u, n;

D 37
	if (results.N % 2) {
E 37
I 37
	if (results.N == 0) {
		n = 1;
		u = 0;
	} else if (results.N % 2) {
E 37
		n = results.n[i];
		u = results.u[i];
	} else {
		n = (results.n[i] + results.n[i-1]) / 2;
		u = (results.u[i] + results.u[i-1]) / 2;
E 31
	}
D 31
	(void) gettimeofday(tv, (struct timezone *) 0);
E 31
I 31
	save_n(n); settime(u);
E 31
}

I 18
D 31
#define	LTRIES	(TRIES * 1)
E 31
E 18
/*
I 18
 * The inner loop tracks bench.h but uses a different results array.
 */
static long *
D 25
one_op(long *p)
E 25
I 25
one_op(register long *p)
E 25
{
D 31
	result_t r[LTRIES];
	int	i;

	insertinit(r, LTRIES);
	for (i = 0; i < LTRIES; ++i) {
		BENCH1(p = (long *)*p, 0);
D 25
		insertsort(usecs_spent(), get_n(), r, LTRIES);
E 25
I 25
		insertsort(gettime(), get_n(), r, LTRIES);
E 25
	}
D 25
	save_n(r[0].n); settime(r[0].u);
E 25
I 25
	/*
	for (i = 0; i < LTRIES; ++i) 
		printf("%d\t%d\t%f%s\n",
		    (int)r[i].n, (int)r[i].u, (double)r[i].u/r[i].n,
		    i==LTRIES/2?" *":"");
	*/
	save_n(r[LTRIES/2].n); settime(r[LTRIES/2].u);
E 31
I 31
	BENCH_INNER(p = (long *)*p, 0);
E 31
E 25
	return (p);
}

static long *
D 25
two_op(long *p)
E 25
I 25
two_op(register long *p, register long *q)
E 25
{
D 31
	result_t r[LTRIES];
	int	i;

	insertinit(r, LTRIES);
	for (i = 0; i < LTRIES; ++i) {
D 25
		BENCH1(p = (long *)*p; p = (long*)*p, 0);
		insertsort(usecs_spent(), get_n(), r, LTRIES);
E 25
I 25
		BENCH1(p = (long *)*q; q = (long*)*p, 0);
		insertsort(gettime(), get_n(), r, LTRIES);
E 25
	}
D 25
	save_n(r[0].n); settime(r[0].u);
E 25
I 25
	/*
	for (i = 0; i < LTRIES; ++i) 
		printf("%d\t%d\t%f%s\n",
		    (int)r[i].n, (int)r[i].u, (double)r[i].u/r[i].n,
		    i==LTRIES/2?" *":"");
	*/
	save_n(r[LTRIES/2].n); settime(r[LTRIES/2].u);
E 31
I 31
	BENCH_INNER(p = (long *)*q; q = (long*)*p, 0);
E 31
E 25
	return (p);
}

I 25
static long	*p = (long *)&p;
static long	*q = (long *)&q;

D 31
/*
 * Carl - this was busted in the follwing ways:
 *	The compiler optimized the p = *, p = *p into one op.
 *	We want the variables to be statics at fixed addresses in each run.
D 27
 *	I also changed it to take the mean, not the min.
E 27
I 27
 *	I also changed it to take the median, not the min.
E 27
 */
E 31
E 25
double
D 19
l_overhead()
E 19
I 19
l_overhead(void)
E 19
{
D 31
	uint64	u1, u2, n1, n2;
D 25
	long	*p = (long *)&p;
E 25
	double	tmp;
	static	double o;
	static	int done = 0;
E 31
I 31
D 33
	int	i, j;
E 33
I 33
	int	i;
E 33
	uint64	N_save, u_save;
	static	double overhead;
	static	int initialized = 0;
	result_t one, two, r_save;
E 31

	init_timing();
D 31
	if (done) { return (o); }
E 31
I 31
D 40
	if (initialized) return overhead;
E 40
I 40
	if (initialized) return (overhead);
E 40
E 31

D 31
	done = 1;
E 31
I 31
	initialized = 1;
E 31
	if (getenv("LOOP_O")) {
D 31
		o = atof(getenv("LOOP_O"));
		return (o);
	}
D 27
	use_result((int)one_op(p));
E 27
I 27
D 28
	use_result((uint64)one_op(p));
E 28
I 28
	use_pointer((void *)one_op(p));
E 28
E 27
D 25
	u1 = usecs_spent();
E 25
I 25
	u1 = gettime();
E 25
	n1 = get_n();
D 25
	use_result((int)two_op(p));
	u2 = usecs_spent();
E 25
I 25
D 27
	use_result((int)two_op(p, q));
E 27
I 27
D 28
	use_result((uint64)two_op(p, q));
E 28
I 28
	use_pointer((void *)two_op(p, q));
E 28
E 27
	u2 = gettime();
E 25
	n2 = get_n();
I 25
	/*
	fprintf(stderr, "%lld %lld  %f  %lld  %lld  %f  ",
	    u1,n1,(double)u1/n1,u2,n2,(double)u2/n2);
	fprintf(stderr, "%f  %f  ", (double)u1/n1,(double)u2/n2);
    	*/
E 31
I 31
		overhead = atof(getenv("LOOP_O"));
	} else {
		get_results(&r_save); N_save = get_n(); u_save = gettime(); 
		insertinit(&one);
		insertinit(&two);
		for (i = 0; i < TRIES; ++i) {
			use_pointer((void*)one_op(p));
D 37
			insertsort(gettime() - t_overhead(), get_n(), &one);
E 37
I 37
D 40
			if (gettime() > 0 && gettime() > t_overhead())
E 40
I 40
			if (gettime() > t_overhead())
E 40
				insertsort(gettime() - t_overhead(), get_n(), &one);
E 37
			use_pointer((void *)two_op(p, q));
D 37
			insertsort(gettime() - t_overhead(), get_n(), &two);
E 37
I 37
D 40
			if (gettime() > 0 && gettime() > t_overhead())
E 40
I 40
			if (gettime() > t_overhead())
E 40
				insertsort(gettime() - t_overhead(), get_n(), &two);
E 37
		}
		/*
		 * u1 = (n1 * (overhead + work))
		 * u2 = (n2 * (overhead + 2 * work))
		 * ==> overhead = 2. * u1 / n1 - u2 / n2
		 */
		save_results(&one); save_minimum();
		overhead = 2. * gettime() / (double)get_n();
		
		save_results(&two); save_minimum();
		overhead -= gettime() / (double)get_n();
		
		if (overhead < 0.) overhead = 0.;	/* Gag */
E 31
E 25

D 31
	/*
	 * u1 = (n1 * (overhead + work))
	 * u2 = (n2 * (overhead + 2 * work))
D 25
	 * this yields
	 * o = 2 * u1 / n1 - u2 / n2
E 25
	 */
	o = 2 * u1;
	o /= n1;
	tmp = u2;
	tmp /= n2;
	o -= tmp;
D 25
	if (o < 0) o = 0;

E 25
I 25
	if (o < 0) o = 0;	/* Gag */
E 25
	return (o);
E 31
I 31
		save_results(&r_save); save_n(N_save); settime(u_save); 
	}
D 40
	return overhead;
E 40
I 40
	return (overhead);
E 40
E 31
}
I 31

E 31
/*
E 18
E 17
 * Figure out the timing overhead.  This has to track bench.h
 */
D 31
double
E 31
I 31
uint64
E 31
D 19
t_overhead()
E 19
I 19
t_overhead(void)
E 19
{
D 17
	struct timeval foo;
	int	N, usecs;
E 17
I 17
D 25
	int		N, usecs;
E 25
I 25
D 31
	uint64		N, usecs;
E 31
I 31
	uint64		N_save, u_save;
E 31
E 25
	static int	initialized = 0;
D 31
	static double	overhead = 0.0;
E 31
I 31
	static uint64	overhead = 0;
	struct timeval	tv;
	result_t	r_save;
E 31
E 17

I 18
	init_timing();
E 18
D 17
	if (timing_overhead) return (timing_overhead);
	if (getenv("TIMING_O")) {
		timing_overhead = atof(getenv("TIMING_O"));
		return (timing_overhead);
E 17
I 17
D 30
	if (overhead == 0.0) {
E 30
I 30
D 31
	if (!initialized) {
		initialized = 1;
E 30
		if (getenv("TIMING_O")) {
			overhead = atof(getenv("TIMING_O"));
D 30
		} else if (!initialized) {
			initialized = 1;
D 25
			N = get_n(); usecs = usecs_spent();
E 25
I 25
D 27
			N = get_n(); usecs = gettime();
E 25
			BENCH(timing_start(0), 0);
D 25
			overhead = usecs_spent();
E 25
I 25
			overhead = gettime();
E 25
			overhead /= get_n();
D 25
			save_n((uint64)N); settime(usecs);
E 25
I 25
			save_n(N); settime(usecs);
E 27
I 27
			if (get_enough(0) > 50000) {
				/* it is in the noise, so ignore it */
				overhead = 0.0;
			} else {
				N = get_n(); usecs = gettime();
				BENCH(timing_start(0), 0);
				overhead = gettime();
				overhead /= get_n();
				save_n(N); settime(usecs);
			}
E 30
I 30
		} else if (get_enough(0) <= 50000) {
			/* it is not in the noise, so compute it */
			N = get_n(); usecs = gettime();
E 31
I 31
D 40
	if (initialized) return overhead;
E 40
I 40
	if (initialized) return (overhead);
E 40

	initialized = 1;
	if (getenv("TIMING_O")) {
		overhead = atof(getenv("TIMING_O"));
	} else if (get_enough(0) <= 50000) {
		/* it is not in the noise, so compute it */
		int		i;
		result_t	r;

E 31
D 31
			BENCH(timing_start(0), 0);
			overhead = gettime();
			overhead /= get_n();
			save_n(N); settime(usecs);
E 31
I 31
		get_results(&r_save); N_save = get_n(); u_save = gettime(); 
		insertinit(&r);
		for (i = 0; i < TRIES; ++i) {
			BENCH_INNER(gettimeofday(&tv, 0), 0);
D 37
			insertsort(gettime(), get_n(), &r);
E 37
I 37
D 40
			if (gettime() > 0) 
				insertsort(gettime(), get_n(), &r);
E 40
I 40
			insertsort(gettime(), get_n(), &r);
E 40
E 37
E 31
E 30
E 27
E 25
		}
I 31
		save_results(&r);
		save_minimum();
		overhead = gettime() / get_n();

		save_results(&r_save); save_n(N_save); settime(u_save); 
E 31
E 17
	}
D 17
	timing_start(0);
	LOOP_FIRST(N, usecs, SHORT);
	timing_start(0);
	LOOP_LAST(N, usecs, SHORT);
	timing_overhead = usecs;
	timing_overhead /= N;
	return (timing_overhead);
E 17
I 17
D 40
	return overhead;
E 40
I 40
	return (overhead);
E 40
E 17
}

/*
 * Figure out how long to run it.
 * If enough == 0, then they want us to figure it out.
 * If enough is !0 then return it unless we think it is too short.
 */
I 18
static	int	long_enough;
I 23
D 27
static	int	compute_enough(int tries);
E 27
I 27
static	int	compute_enough();
E 27
E 23

E 18
int
D 18
get_enough(int enough)
E 18
I 18
get_enough(int e)
E 18
{
D 17
	static	int e = 0;
E 17
I 17
D 18
	static	e = 0;
E 18
I 18
	init_timing();
	return (long_enough > e ? long_enough : e);
}
E 18
E 17

D 17
	if (!e) {
E 17
I 17
D 18
	if (!enough) {
		if (e) return (e);
E 17
		if (getenv("ENOUGH")) {
D 17
			e = atoi(getenv("ENOUGH"));
E 17
I 17
			return e = atoi(getenv("ENOUGH"));
E 18
I 18

D 19
init_timing()
E 19
I 19
static void
init_timing(void)
E 19
{
	static	int done = 0;
D 23
	static int compute_enough(int tries);
E 23

	if (done) return;
	done = 1;
D 27
	long_enough = compute_enough(9);
E 27
I 27
	long_enough = compute_enough();
E 27
	t_overhead();
	l_overhead();
}

typedef long TYPE;

static TYPE **
enough_duration(register long N, register TYPE ** p)
{
#define	ENOUGH_DURATION_TEN(one)	one one one one one one one one one one
	while (N-- > 0) {
		ENOUGH_DURATION_TEN(p = (TYPE **) *p;);
	}
D 40
	return p;
E 40
I 40
	return (p);
E 40
}

D 37
static int
duration(int N)
E 37
I 37
static uint64
duration(long N)
E 37
{
D 37
	int     usecs;
E 37
I 37
	uint64	usecs;
E 37
	TYPE   *x = (TYPE *)&x;
	TYPE  **p = (TYPE **)&x;

	start(0);
	p = enough_duration(N, p);
	usecs = stop(0, 0);
D 27
	use_result((int)p);
E 27
I 27
D 28
	use_result((uint64)p);
E 28
I 28
	use_pointer((void *)p);
E 28
E 27
D 40
	return usecs;
E 40
I 40
	return (usecs);
E 40
}

/*
D 27
 * find the minimum time that work "N" takes in "tries" tests
E 27
I 27
D 31
 * find the median time that work "N" takes in "tries" tests
E 31
I 31
 * find the minimum time that work "N" takes in "tries" tests
E 31
E 27
 */
D 37
static int
E 37
I 37
static uint64
E 37
D 27
time_N(int tries, long N)
E 27
I 27
time_N(long N)
E 27
{
D 33
	int     i, usecs;
E 33
I 33
	int     i;
I 37
	uint64	usecs;
E 37
E 33
I 27
D 31
	result_t r[LTRIES];
E 31
I 31
	result_t r;
E 31
E 27

D 27
	usecs = duration(N);
	for (i = 1; i < tries; ++i) {
		int     tmp = duration(N);

		if (tmp < usecs)
			usecs = tmp;
E 27
I 27
D 31
	insertinit(r, LTRIES);
	for (i = 1; i < LTRIES; ++i) {
		insertsort(duration(N), N, r, LTRIES);
E 31
I 31
	insertinit(&r);
	for (i = 1; i < TRIES; ++i) {
D 37
		insertsort(duration(N), N, &r);
E 37
I 37
		usecs = duration(N);
D 40
		if (usecs > 0)
			insertsort(usecs, N, &r);
E 40
I 40
		insertsort(usecs, N, &r);
E 40
E 37
E 31
E 27
	}
D 27
	return usecs;
E 27
I 27
D 31
	return r[TRIES/2].u;
E 31
I 31
	save_results(&r);
	save_minimum();
D 40
	return gettime();
E 40
I 40
	return (gettime());
E 40
E 31
E 27
}

/*
 * return the amount of work needed to run "enough" microseconds
 */
D 37
static int
E 37
I 37
static long
E 37
find_N(int enough)
{
D 19
	int     i, N;
E 19
I 19
D 21
	int     N;
E 21
I 21
D 27
	int     N, tries;
E 27
I 27
D 37
	int	tries;
	static int N = 10000;
	static int usecs = 0;
E 37
I 37
	int		tries;
	static long	N = 10000;
	static uint64	usecs = 0;
E 37
E 27
E 21
E 19

D 21
	for (N = 1;;) {
E 21
I 21
D 27
	for (N = 1, tries = 0; ; tries++) {
E 21
		/*
		 * XXX - prevent infinite loops? 
		 */
		int     usecs = duration(N);
E 27
I 27
D 30
	if (usecs = 0) usecs = time_N(N);
E 30
I 30
	if (!usecs) usecs = time_N(N);
E 30
E 27

I 27
	for (tries = 0; tries < 10; ++tries) {
E 27
		if (0.98 * enough < usecs && usecs < 1.02 * enough)
D 27
			break;
		if (usecs < 150)
E 27
I 27
D 40
			return N;
E 40
I 40
			return (N);
E 40
		if (usecs < 1000)
E 27
			N *= 10;
		else {
			double  n = N;

			n /= usecs;
			n *= enough;
			N = n + 1;
E 18
E 17
		}
I 21
D 27
		if (tries > 100) return (-1);
E 27
I 27
		usecs = time_N(N);
E 27
E 21
D 17
		e = REAL_SHORT;
E 17
I 17
D 18
		return (e = SHORT);
E 18
E 17
	}
D 17
	if (!enough || enough < e) {
		return (e);
	}
E 17
I 17
D 18
	if (enough < 50000) return (50000);
E 17
	return (enough);
E 18
I 18
D 27
	return N;
E 27
I 27
D 40
	return -1;
E 40
I 40
	return (-1);
E 40
E 27
E 18
}
I 18

/*
 * We want to verify that small modifications proportionally affect the runtime
 */
D 32
#define	POINTS	4
E 32
I 32
static double test_points[] = {1.015, 1.02, 1.035};
E 32
static int
D 27
test_time(int tries, int enough)
E 27
I 27
test_time(int enough)
E 27
{
D 32
	int     i, j, N = find_N(enough);
	int     n[POINTS], usecs[POINTS];
I 27
	int	expected[POINTS];
E 27
	double  rate[POINTS];
E 32
I 32
D 37
	int     i, N, usecs, expected, baseline;
E 37
I 37
	int     i;
	long	N;
D 38
	uint64	usecs, expected, baseline;
E 38
I 38
	uint64	usecs, expected, baseline, diff;
E 38
E 37
E 32

D 32
	if (N <= 0)
E 32
I 32
	if ((N = find_N(enough)) <= 0)
E 32
D 40
		return 0;
E 40
I 40
		return (0);
E 40

D 32
	for (i = 0; i < POINTS; ++i) {
D 27
		n[i] = (int) ((double) N * (1.0 + (double) i * 0.01));
		usecs[i] = time_N(tries, n[i]);
E 27
I 27
		double fraction = 1.0 + (double) i * 0.005;
		n[i] = (int)((double) N * fraction);
		usecs[i] = time_N(n[i]);
		expected[i] = (int)((double)usecs[0] * fraction);
E 27
		rate[i] = (double) usecs[i] / n[i];
I 27
D 29
		if (ABS(usecs[i] - expected[i]) / (double)expected[i] > 0.001 ||
		    ABS(enough - usecs[i]) * fraction / (double)enough > 0.03)
				return 0;
E 29
I 29
		if (ABS(enough - usecs[i]) * fraction / (double)enough > 0.03)
E 32
I 32
	baseline = time_N(N);

	for (i = 0; i < sizeof(test_points) / sizeof(double); ++i) {
		usecs = time_N((int)((double) N * test_points[i]));
D 37
		expected = (int)((double)baseline * test_points[i]);
E 37
I 37
		expected = (uint64)((double)baseline * test_points[i]);
E 37
D 38
		if (ABS(expected - usecs) / (double)expected > 0.0025)
E 38
I 38
		diff = expected > usecs ? expected - usecs : usecs - expected;
		if (diff / (double)expected > 0.0025)
E 38
E 32
D 40
			return 0;
E 40
I 40
			return (0);
E 40
E 29
E 27
D 32
		for (j = 0; j < i; ++j) {
D 23
			if (ABS(rate[i] - rate[j]) > 0.01)
E 23
I 23
			if (ABS(rate[i] - rate[j]) > 0.001)
E 23
				return 0;
		}
E 32
	}
D 40
	return 1;
E 40
I 40
	return (1);
E 40
}

D 23
int     possibilities[] =
{
D 22
    1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000,
E 22
I 22
    5000, 6000, 7000, 8000, 9000,
E 22
    10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000,
    100000, 200000, 300000, 400000, 500000
};
E 23
I 23
D 25
static	int     possibilities[] = { 1000, 5000, 10000, 50000, 100000 };
E 25
I 25
D 32
static	int     possibilities[] = { 5000, 10000, 50000, 100000 };
E 32
E 25
E 23

/*
 * We want to find the smallest timing interval that has accurate timing
 */
I 32
static int     possibilities[] = { 5000, 10000, 50000, 100000 };
E 32
static int
D 27
compute_enough(int tries)
E 27
I 27
compute_enough()
E 27
{
	int     i;

I 21
	if (getenv("ENOUGH")) {
		return (atoi(getenv("ENOUGH")));
	}
E 21
	for (i = 0; i < sizeof(possibilities) / sizeof(int); ++i) {
D 27
		if (test_time(tries, possibilities[i]))
E 27
I 27
		if (test_time(possibilities[i]))
E 27
D 40
			return possibilities[i];
E 40
I 40
			return (possibilities[i]);
E 40
	}

D 27
	return possibilities[sizeof(possibilities) / sizeof(int) - 1];
E 27
I 27
	/* 
	 * if we can't find a timing interval that is sufficient, 
	 * then use SHORT as a default.
	 */
D 40
	return SHORT;
E 40
I 40
	return (SHORT);
E 40
E 27
}
I 24

/*
 * This stuff isn't really lib_timing, but ...
 */
void
morefds(void)
{
#ifdef	RLIMIT_NOFILE
	struct	rlimit r;

	getrlimit(RLIMIT_NOFILE, &r);
	r.rlim_cur = r.rlim_max;
	setrlimit(RLIMIT_NOFILE, &r);
#endif
}

I 33
void
E 33
touch(char *buf, int nbytes)
{
	static	psize;

	if (!psize) {
I 30
D 31
#if defined(hpux) || defined(__hpux)
#define getpagesize()	4096
#endif
E 31
E 30
		psize = getpagesize();
	}
	while (nbytes > 0) {
		*buf = 1;
		buf += psize;
		nbytes -= psize;
	}
}
I 31

I 41
D 42
#if defined(srand48) && srand48 == srand
double
drand48(void)
{
	return (double)rand() / RAND_MAX;
}
#endif

E 42
E 41
#if defined(hpux) || defined(__hpux)
int
getpagesize()
{
D 40
	return sysconf(_SC_PAGE_SIZE);
E 40
I 40
	return (sysconf(_SC_PAGE_SIZE));
E 40
I 37
}
#endif

#ifdef WIN32
int
getpagesize()
{
	SYSTEM_INFO s;

	GetSystemInfo(&s);
D 40
	return (int)s.dwPageSize;
E 40
I 40
	return ((int)s.dwPageSize);
E 40
}

LARGE_INTEGER
getFILETIMEoffset()
{
	SYSTEMTIME s;
	FILETIME f;
	LARGE_INTEGER t;

	s.wYear = 1970;
	s.wMonth = 1;
	s.wDay = 1;
	s.wHour = 0;
	s.wMinute = 0;
	s.wSecond = 0;
	s.wMilliseconds = 0;
	SystemTimeToFileTime(&s, &f);
	t.QuadPart = f.dwHighDateTime;
	t.QuadPart <<= 32;
	t.QuadPart |= f.dwLowDateTime;
D 40
	return t;
E 40
I 40
	return (t);
E 40
}

int
gettimeofday(struct timeval *tv, struct timezone *tz)
{
	LARGE_INTEGER			t;
	FILETIME			f;
	double					microseconds;
	static LARGE_INTEGER	offset;
	static double			frequencyToMicroseconds;
	static int				initialized = 0;
	static BOOL				usePerformanceCounter = 0;

	if (!initialized) {
		LARGE_INTEGER performanceFrequency;
		initialized = 1;
		usePerformanceCounter = QueryPerformanceFrequency(&performanceFrequency);
		if (usePerformanceCounter) {
			QueryPerformanceCounter(&offset);
			frequencyToMicroseconds = (double)performanceFrequency.QuadPart / 1000000.;
		} else {
			offset = getFILETIMEoffset();
			frequencyToMicroseconds = 10.;
		}
	}
	if (usePerformanceCounter) QueryPerformanceCounter(&t);
	else {
		GetSystemTimeAsFileTime(&f);
		t.QuadPart = f.dwHighDateTime;
		t.QuadPart <<= 32;
		t.QuadPart |= f.dwLowDateTime;
	}

	t.QuadPart -= offset.QuadPart;
	microseconds = (double)t.QuadPart / frequencyToMicroseconds;
	t.QuadPart = microseconds;
	tv->tv_sec = t.QuadPart / 1000000;
	tv->tv_usec = t.QuadPart % 1000000;
D 40
	return 0;
E 40
I 40
	return (0);
E 40
E 37
}
#endif
E 31
E 24
E 18
E 16
D 15
#endif

E 14
#define RUSAGE
#ifdef	RUSAGE
#include <sys/resource.h>
#define	secs(tv)	(tv.tv_sec + tv.tv_usec / 1000000.0)
#define	mine(f)		(int)(ru_stop.f - ru_start.f)

static struct rusage ru_start, ru_stop;

void
rusage(void)
{
	double  sys, user, idle;
	double  per;
D 14
	double  timespent();
E 14

	sys = secs(ru_stop.ru_stime) - secs(ru_start.ru_stime);
	user = secs(ru_stop.ru_utime) - secs(ru_start.ru_utime);
	idle = timespent() - (sys + user);
	per = idle / timespent() * 100;
	fprintf(ftiming, "real=%.2f sys=%.2f user=%.2f idle=%.2f stall=%.0f%% ",
	    timespent(), sys, user, idle, per);
	fprintf(ftiming, "rd=%d wr=%d min=%d maj=%d ctx=%d\n",
	    mine(ru_inblock), mine(ru_oublock),
	    mine(ru_minflt), mine(ru_majflt),
	    mine(ru_nvcsw) + mine(ru_nivcsw));
}

#endif	/* RUSAGE */
E 15
E 10
E 9
E 3
E 2
I 1
E 1
