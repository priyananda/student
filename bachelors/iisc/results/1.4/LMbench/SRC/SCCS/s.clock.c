h36252
s 00008/00007/00017
d D 1.4 00/12/11 16:14:55 staelin 5 4
c - Debug clock.c so that it works with current timing harness
cC
cHhpli8.hpli.hpl.hp.com
cK42089
cZ+02:00
e
s 00000/00002/00024
d D 1.3 97/06/12 21:30:06 lm 4 3
c new bench.h macros.
cC
cK47171
cSAlpha2.11
e
s 00018/00073/00008
d D 1.2 97/06/10 20:46:41 lm 3 2
c carl's version.
cK50448
e
s 00081/00000/00000
d D 1.1 97/06/10 20:46:18 lm 2 1
c Initial revision
cK46174
e
s 00000/00000/00000
d D 1.0 97/06/10 20:46:17 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK27314
cPsrc/clock.c
cRc65f836be45c53d8
cV4
cX0x21
cZ-07:00
e
u
U
f e 0
f x 0x21
t
first pass.
T
I 2
D 3
#include "timing.h"
#include "bench.h"

struct	timeval tv, tv2;

E 3
/*
D 3
 * returns the number of microseconds between begin and end
E 3
I 3
 * clock.c
 *
 * calculate the minimum timing loop length that gives us significant results
E 3
 */
D 3
uint64
tvdelta(struct timeval *begin, struct timeval *end)
{
	uint64 m;
	struct timeval tdiff;
E 3
I 3
#include "bench.h"
I 5
#include "version.h"
E 5
D 4
#include "timing.h"
#include "stats.h"
E 4
E 3

D 3
	tvsub(&tdiff, end, begin);
	m = tdiff.tv_sec;
	m *= 1000000;
	m += tdiff.tv_usec;
E 3
I 3
char	*id = "$Id$";
char	*revision = "$Revision$";
E 3

D 3
	return m;
}

double
doit(enough)
{
	int	usecs, N;

	LOOP_FIRST(N, usecs, enough);
	start(&tv);
	LOOP_LAST(N, usecs, enough);
	return ((double)usecs / (double)N);
}

int
E 3
main()
{
D 3
	int	tries, usecs;
	double	predict, got, diff, percent;
	double	results[5];
E 3
I 3
	uint64	enough;
D 5
	double	t_overhead, l_overhead;
E 5
I 5
	double	timing, loop;
E 5
E 3

D 3
	for (tries = 0; tries < 5; ++tries) {
		results[tries] = -1;
	}
	for (tries = 0; tries < 5; ++tries) {
		predict = doit(200000);
		insertsort(results, 5, predict);
	}
	predict = results[4];
	for (tries = 0; tries < 10; ++tries) {
		usecs = 200000;
		/*
		 * OK, now we know that it takes N iterations to usecs usecs.
		 * Start going down.
		 */
		while (usecs > 100) {
			usecs /= 10;
			got = doit(usecs);
			diff = got - predict;
			if (diff < 0) diff = -diff;
			percent = diff/predict * 100;
			/*
			printf("%6.3f %6.3f %6.3f %2.0f%% %6d\n",
			    predict, got, diff, percent, usecs);
			*/
			if (percent >= 1) break;
		}

		/*
		 * Verify our theory.
		 */
		usecs *= 10;	
		got = doit(usecs);
		diff = got - predict;
		if (diff < 0) diff = -diff;
		if (diff/predict <= .01) {
			printf("%.2f (%.2f)\n", usecs/1000., predict);
			exit(0);
		}
	}
	printf("System too busy, we didn't converge after 10 tries.\n");
E 3
I 3
D 5
	enough = compute_enough(15);
E 5
I 5
	enough = get_enough(0);
E 5
	printf("ENOUGH=%lu\n", (unsigned long)enough); fflush(stdout);
D 5
	t_overhead = timing_overhead(enough);
	printf("TIMING_OVERHEAD=%f\n", t_overhead); fflush(stdout);
	l_overhead = loop_overhead(enough, t_overhead);
	printf("LOOP_OVERHEAD=%f\n", l_overhead);
	printf("# version [%s]\n", revision);
E 5
I 5
	timing = t_overhead();
	printf("TIMING_OVERHEAD=%f\n", timing); fflush(stdout);
	loop = l_overhead();
	printf("LOOP_OVERHEAD=%f\n", loop);
	printf("# version %d.%d\n", MAJOR, MINOR);
E 5
	exit(0);
E 3
}
E 2
I 1
E 1
