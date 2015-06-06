h44019
s 00004/00000/00279
d D 1.6 00/07/31 16:41:16 staelin 7 6
c - Add calls to use_pointer((void*)p) to most of the benchmarks to ensure that the
c   inner loops don't get optimized away
cC
cHhpli8.hpli.hpl.hp.com
cK21654
cZ+03:00
e
s 00000/00001/00279
d D 1.5 98/06/29 22:37:23 lm 6 5
c Redo to compile clean with -Wall.
cC
cK13554
cSAlpha2.11
cZ-07:00
e
s 00002/00002/00278
d D 1.4 98/03/06 12:00:15 lm 5 4
c lint.
cK15295
e
s 00003/00003/00277
d D 1.3 97/10/31 18:06:23 lm 4 3
c use_result -> use_int/pointer
cK11953
cZ-08:00
e
s 00002/00000/00278
d D 1.2 97/10/19 23:41:50 lm 3 2
c looks like I needed to move the destination pointer too :-)
cK14878
e
s 00278/00000/00000
d D 1.1 97/07/07 23:18:00 lm 2 1
c Initial revision
cK13396
e
s 00000/00000/00000
d D 1.0 97/07/07 23:17:59 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK19200
cPsrc/bw_mem.c
cR6b79a80385eb9ec7
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
 * bw_mem_wr.c - simple memory write bandwidth benchmark
 *
 * Usage: bw_mem_wr size
 *
 * This benchmark is directly comparable to the bw_mem_rd benchmark because
 * both do a load/store and an add per word.
 *
 * Copyright (c) 1994-1996 Larry McVoy.  Distributed under the FSF GPL with
 * additional restriction that results may published only if
 * (1) the benchmark is unmodified, and
 * (2) the version in the sccsid below is included in the report.
 * Support for this development by Sun Microsystems is gratefully acknowledged.
 */
char	*id = "$Id$";

#include "bench.h"

#define TYPE    int

/*
 * rd - 4 byte read, 32 byte stride
 * wr - 4 byte write, 32 byte stride
 * rdwr - 4 byte read followed by 4 byte write to same place, 32 byte stride
 * cp - 4 byte read then 4 byte write to different place, 32 byte stride
 * fwr - write every 4 byte word
 * frd - read every 4 byte word
 * fcp - copy every 4 byte word
 *
 * All tests do 512 byte chunks in a loop.
 *
 * XXX - do a 64bit version of this.
 */
void	rd(TYPE *buf, TYPE *lastone);
void	wr(TYPE *buf, TYPE *lastone);
void	rdwr(TYPE *buf, TYPE *lastone);
void	cp(TYPE *buf, TYPE *dst, TYPE *lastone);
void	fwr(TYPE *buf, TYPE *lastone);
void	frd(TYPE *buf, TYPE *lastone);
void	fcp(TYPE *buf, TYPE *dst, TYPE *lastone);

int
main(ac, av)
        char  **av;
{
	int	nbytes;
	TYPE   *buf = 0, *buf2 = 0, *lastone;
D 6
	double	overhead = 0;
E 6

	if (ac < 3) {
usage:		fprintf(stderr, "Usage: %s size what [conflict]\n", av[0]);
		fprintf(stderr, 
		    "what: rd wr rdwr cp fwr frd fcp bzero bcopy\n");
		exit(1);
	}
	nbytes = bytes(av[1]);
	if (nbytes < 512) {	/* this is the number of bytes in the loop */
		exit(1);
	}
        buf = (TYPE *)valloc(nbytes);
	lastone = (TYPE*)((char *)buf + nbytes - 512);
	if (!buf) {
		perror("malloc");
		exit(1);
	}
	if (streq(av[2], "cp") ||
	    streq(av[2], "fcp") || streq(av[2], "bcopy")) {
        	buf2 = (TYPE *)valloc(nbytes + 2048);
		if (!buf2) {
			perror("malloc");
			exit(1);
		}
		/* default is to have stuff unaligned wrt each other */
		/* XXX - this is not well tested or thought out */
		if (ac == 3) {
			char	*tmp = (char *)buf2;

			tmp += 2048 - 128;
			buf2 = (TYPE *)tmp;
		}
	}
		
	bzero((void*)buf, nbytes);
	if (streq(av[2], "rd")) {
		BENCHO(rd(buf, lastone), rd(buf, 0), 0);
	} else if (streq(av[2], "wr")) {
		BENCHO(wr(buf, lastone), wr(buf, 0), 0);
	} else if (streq(av[2], "rdwr")) {
		BENCHO(rdwr(buf, lastone), rdwr(buf, 0), 0);
	} else if (streq(av[2], "cp")) {
		BENCHO(cp(buf, buf2, lastone), cp(buf, buf2, 0), 0);
	} else if (streq(av[2], "frd")) {
		BENCHO(frd(buf, lastone), frd(buf, 0), 0);
	} else if (streq(av[2], "fwr")) {
		BENCHO(fwr(buf, lastone), fwr(buf, 0), 0);
	} else if (streq(av[2], "fcp")) {
		BENCHO(fcp(buf, buf2, lastone), fcp(buf, buf2, 0), 0);
	} else if (streq(av[2], "bzero")) {
D 5
		BENCHO(bzero(buf, nbytes), bzero(buf, 1), 0);
E 5
I 5
		BENCHO(bzero((void*)buf, nbytes), bzero((void*)buf, 1), 0);
E 5
	} else if (streq(av[2], "bcopy")) {
		/* XXX - if gcc inlines this the numbers could be off */
		/* But they are off in a good way - the bcopy will appear
		 * to cost around 0...
		 */
D 5
		BENCHO(bcopy(buf, buf2, nbytes), bcopy(buf, buf2, 1), 0);
E 5
I 5
		BENCHO(bcopy((void*)buf, (void*)buf2, nbytes), bcopy((void*)buf, (void*)buf2, 1), 0);
E 5
	} else {
		goto usage;
	}
	bandwidth(nbytes, get_n(), 0);
	return(0);
}

void
rd(register TYPE *p, register TYPE *lastone)
{	
	register int sum = 0;

	while (p <= lastone) {
		sum += 
#define	DOIT(i)	p[i]+
		DOIT(0) DOIT(4) DOIT(8) DOIT(12) DOIT(16) DOIT(20) DOIT(24)
		DOIT(28) DOIT(32) DOIT(36) DOIT(40) DOIT(44) DOIT(48) DOIT(52)
		DOIT(56) DOIT(60) DOIT(64) DOIT(68) DOIT(72) DOIT(76)
		DOIT(80) DOIT(84) DOIT(88) DOIT(92) DOIT(96) DOIT(100)
		DOIT(104) DOIT(108) DOIT(112) DOIT(116) DOIT(120) 
		p[124];
		p +=  128;
	}
D 4
	use_result((uint64)sum);
E 4
I 4
	use_int(sum);
E 4
}
#undef	DOIT

void
wr(register TYPE *p, register TYPE *lastone)
{	
	while (p <= lastone) {
#define	DOIT(i)	p[i] = 1;
		DOIT(0) DOIT(4) DOIT(8) DOIT(12) DOIT(16) DOIT(20) DOIT(24)
		DOIT(28) DOIT(32) DOIT(36) DOIT(40) DOIT(44) DOIT(48) DOIT(52)
		DOIT(56) DOIT(60) DOIT(64) DOIT(68) DOIT(72) DOIT(76)
		DOIT(80) DOIT(84) DOIT(88) DOIT(92) DOIT(96) DOIT(100)
		DOIT(104) DOIT(108) DOIT(112) DOIT(116) DOIT(120) DOIT(124);
		p +=  128;
	}
I 7
	use_pointer((void*)p);
E 7
}
#undef	DOIT

void
rdwr(register TYPE *p, register TYPE *lastone)
{	
	register int sum = 0;

	while (p <= lastone) {
#define	DOIT(i)	sum += p[i]; p[i] = 1;
		DOIT(0) DOIT(4) DOIT(8) DOIT(12) DOIT(16) DOIT(20) DOIT(24)
		DOIT(28) DOIT(32) DOIT(36) DOIT(40) DOIT(44) DOIT(48) DOIT(52)
		DOIT(56) DOIT(60) DOIT(64) DOIT(68) DOIT(72) DOIT(76)
		DOIT(80) DOIT(84) DOIT(88) DOIT(92) DOIT(96) DOIT(100)
		DOIT(104) DOIT(108) DOIT(112) DOIT(116) DOIT(120) DOIT(124);
		p +=  128;
	}
D 4
	use_result((uint64)sum);
E 4
I 4
	use_int(sum);
E 4
}
#undef	DOIT

void
cp(register TYPE *p, register TYPE *dst, register TYPE *lastone)
{	
	while (p <= lastone) {
#define	DOIT(i)	dst[i] = p[i];
		DOIT(0) DOIT(4) DOIT(8) DOIT(12) DOIT(16) DOIT(20) DOIT(24)
		DOIT(28) DOIT(32) DOIT(36) DOIT(40) DOIT(44) DOIT(48) DOIT(52)
		DOIT(56) DOIT(60) DOIT(64) DOIT(68) DOIT(72) DOIT(76)
		DOIT(80) DOIT(84) DOIT(88) DOIT(92) DOIT(96) DOIT(100)
		DOIT(104) DOIT(108) DOIT(112) DOIT(116) DOIT(120) DOIT(124);
		p += 128;
I 3
		dst += 128;
E 3
	}
I 7
	use_pointer((void*)p);
E 7
}
#undef	DOIT

void
fwr(register TYPE *p, register TYPE *lastone)
{	
	while (p <= lastone) {
#define	DOIT(i)	p[i]=
		DOIT(0) DOIT(1) DOIT(2) DOIT(3) DOIT(4) DOIT(5) DOIT(6)
		DOIT(7) DOIT(8) DOIT(9) DOIT(10) DOIT(11) DOIT(12)
		DOIT(13) DOIT(14) DOIT(15) DOIT(16) DOIT(17) DOIT(18)
		DOIT(19) DOIT(20) DOIT(21) DOIT(22) DOIT(23) DOIT(24)
		DOIT(25) DOIT(26) DOIT(27) DOIT(28) DOIT(29) DOIT(30)
		DOIT(31) DOIT(32) DOIT(33) DOIT(34) DOIT(35) DOIT(36)
		DOIT(37) DOIT(38) DOIT(39) DOIT(40) DOIT(41) DOIT(42)
		DOIT(43) DOIT(44) DOIT(45) DOIT(46) DOIT(47) DOIT(48)
		DOIT(49) DOIT(50) DOIT(51) DOIT(52) DOIT(53) DOIT(54)
		DOIT(55) DOIT(56) DOIT(57) DOIT(58) DOIT(59) DOIT(60)
		DOIT(61) DOIT(62) DOIT(63) DOIT(64) DOIT(65) DOIT(66)
		DOIT(67) DOIT(68) DOIT(69) DOIT(70) DOIT(71) DOIT(72)
		DOIT(73) DOIT(74) DOIT(75) DOIT(76) DOIT(77) DOIT(78)
		DOIT(79) DOIT(80) DOIT(81) DOIT(82) DOIT(83) DOIT(84)
		DOIT(85) DOIT(86) DOIT(87) DOIT(88) DOIT(89) DOIT(90)
		DOIT(91) DOIT(92) DOIT(93) DOIT(94) DOIT(95) DOIT(96)
		DOIT(97) DOIT(98) DOIT(99) DOIT(100) DOIT(101) DOIT(102)
		DOIT(103) DOIT(104) DOIT(105) DOIT(106) DOIT(107)
		DOIT(108) DOIT(109) DOIT(110) DOIT(111) DOIT(112)
		DOIT(113) DOIT(114) DOIT(115) DOIT(116) DOIT(117)
		DOIT(118) DOIT(119) DOIT(120) DOIT(121) DOIT(122)
		DOIT(123) DOIT(124) DOIT(125) DOIT(126) DOIT(127) 1;
		p += 128;
	}
I 7
	use_pointer((void*)p);
E 7
}
#undef	DOIT

void
frd(register TYPE *p, register TYPE *lastone)
{	
	register int sum = 0;

	while (p <= lastone) {
		sum +=
#define	DOIT(i)	p[i]+
		DOIT(0) DOIT(1) DOIT(2) DOIT(3) DOIT(4) DOIT(5) DOIT(6)
		DOIT(7) DOIT(8) DOIT(9) DOIT(10) DOIT(11) DOIT(12)
		DOIT(13) DOIT(14) DOIT(15) DOIT(16) DOIT(17) DOIT(18)
		DOIT(19) DOIT(20) DOIT(21) DOIT(22) DOIT(23) DOIT(24)
		DOIT(25) DOIT(26) DOIT(27) DOIT(28) DOIT(29) DOIT(30)
		DOIT(31) DOIT(32) DOIT(33) DOIT(34) DOIT(35) DOIT(36)
		DOIT(37) DOIT(38) DOIT(39) DOIT(40) DOIT(41) DOIT(42)
		DOIT(43) DOIT(44) DOIT(45) DOIT(46) DOIT(47) DOIT(48)
		DOIT(49) DOIT(50) DOIT(51) DOIT(52) DOIT(53) DOIT(54)
		DOIT(55) DOIT(56) DOIT(57) DOIT(58) DOIT(59) DOIT(60)
		DOIT(61) DOIT(62) DOIT(63) DOIT(64) DOIT(65) DOIT(66)
		DOIT(67) DOIT(68) DOIT(69) DOIT(70) DOIT(71) DOIT(72)
		DOIT(73) DOIT(74) DOIT(75) DOIT(76) DOIT(77) DOIT(78)
		DOIT(79) DOIT(80) DOIT(81) DOIT(82) DOIT(83) DOIT(84)
		DOIT(85) DOIT(86) DOIT(87) DOIT(88) DOIT(89) DOIT(90)
		DOIT(91) DOIT(92) DOIT(93) DOIT(94) DOIT(95) DOIT(96)
		DOIT(97) DOIT(98) DOIT(99) DOIT(100) DOIT(101) DOIT(102)
		DOIT(103) DOIT(104) DOIT(105) DOIT(106) DOIT(107)
		DOIT(108) DOIT(109) DOIT(110) DOIT(111) DOIT(112)
		DOIT(113) DOIT(114) DOIT(115) DOIT(116) DOIT(117)
		DOIT(118) DOIT(119) DOIT(120) DOIT(121) DOIT(122)
		DOIT(123) DOIT(124) DOIT(125) DOIT(126) p[127];
		p += 128;
	}
D 4
	use_result((uint64)sum);
E 4
I 4
	use_int(sum);
E 4
}
#undef	DOIT

void
fcp(register TYPE *p, register TYPE *dst, register TYPE *lastone)
{	
	while (p <= lastone) {
#define	DOIT(i)	dst[i]=p[i];
		DOIT(0) DOIT(1) DOIT(2) DOIT(3) DOIT(4) DOIT(5) DOIT(6)
		DOIT(7) DOIT(8) DOIT(9) DOIT(10) DOIT(11) DOIT(12)
		DOIT(13) DOIT(14) DOIT(15) DOIT(16) DOIT(17) DOIT(18)
		DOIT(19) DOIT(20) DOIT(21) DOIT(22) DOIT(23) DOIT(24)
		DOIT(25) DOIT(26) DOIT(27) DOIT(28) DOIT(29) DOIT(30)
		DOIT(31) DOIT(32) DOIT(33) DOIT(34) DOIT(35) DOIT(36)
		DOIT(37) DOIT(38) DOIT(39) DOIT(40) DOIT(41) DOIT(42)
		DOIT(43) DOIT(44) DOIT(45) DOIT(46) DOIT(47) DOIT(48)
		DOIT(49) DOIT(50) DOIT(51) DOIT(52) DOIT(53) DOIT(54)
		DOIT(55) DOIT(56) DOIT(57) DOIT(58) DOIT(59) DOIT(60)
		DOIT(61) DOIT(62) DOIT(63) DOIT(64) DOIT(65) DOIT(66)
		DOIT(67) DOIT(68) DOIT(69) DOIT(70) DOIT(71) DOIT(72)
		DOIT(73) DOIT(74) DOIT(75) DOIT(76) DOIT(77) DOIT(78)
		DOIT(79) DOIT(80) DOIT(81) DOIT(82) DOIT(83) DOIT(84)
		DOIT(85) DOIT(86) DOIT(87) DOIT(88) DOIT(89) DOIT(90)
		DOIT(91) DOIT(92) DOIT(93) DOIT(94) DOIT(95) DOIT(96)
		DOIT(97) DOIT(98) DOIT(99) DOIT(100) DOIT(101) DOIT(102)
		DOIT(103) DOIT(104) DOIT(105) DOIT(106) DOIT(107)
		DOIT(108) DOIT(109) DOIT(110) DOIT(111) DOIT(112)
		DOIT(113) DOIT(114) DOIT(115) DOIT(116) DOIT(117)
		DOIT(118) DOIT(119) DOIT(120) DOIT(121) DOIT(122)
		DOIT(123) DOIT(124) DOIT(125) DOIT(126) DOIT(127)
		p += 128;
I 3
		dst += 128;
E 3
	}
I 7
	use_pointer((void*)p);
E 7
}
E 2
I 1
E 1
