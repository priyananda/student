h00527
s 00009/00007/00051
d D 1.15 00/12/24 10:39:32 staelin 16 15
c - Add references to new man pages in src/Makefile
cC
cHhpli8.hpli.hpl.hp.com
cK44041
cZ+02:00
e
s 00001/00001/00057
d D 1.14 00/01/31 16:29:28 lm 15 14
c Updates for BitKeeper.
cC
cHlm.bitmover.com
cK27316
e
s 00006/00006/00052
d D 1.13 98/03/30 01:04:05 lm 14 13
c SCCS
cC
cHwork.home
cK27034
cZ-08:00
e
s 00006/00006/00052
d D 1.12 97/10/25 10:52:56 lm 13 12
c carl.
cK32092
cZ-07:00
e
s 00004/00003/00054
d D 1.11 95/11/14 00:55:01 lm 12 11
c text support
cK31258
e
s 00003/00003/00054
d D 1.10 95/11/01 22:26:06 lm 11 10
c eqn.
cK28537
cZ-08:00
e
s 00005/00010/00052
d D 1.9 95/10/25 09:50:57 lm 10 9
c *** empty log message ***
cK28003
e
s 00008/00018/00054
d D 1.8 95/10/25 09:45:31 lm 9 8
c paper.
cK34808
e
s 00020/00013/00052
d D 1.7 95/10/05 13:16:18 lm 8 7
c *** empty log message ***
cK57009
e
s 00009/00002/00056
d D 1.6 95/09/29 15:35:03 staelin 7 6
c added rules for two new graphs
cK40312
e
s 00003/00003/00055
d D 1.5 95/09/28 11:22:31 lm 6 5
c tbl.
cK18800
e
s 00024/00011/00034
d D 1.4 95/09/27 18:38:41 staelin 5 4
c usenix
cK18221
cZ-07:00
e
s 00003/00002/00042
d D 1.3 94/11/25 16:33:03 lm 4 3
c scripts.
cK64656
e
s 00001/00001/00043
d D 1.2 94/11/23 18:00:27 lm 3 2
c upating to include pagefault.
cK61669
e
s 00044/00000/00000
d D 1.1 94/11/23 17:45:40 lm 2 1
c Initial revision
cK60166
e
s 00000/00000/00000
d D 1.0 94/11/23 17:45:39 lm 1 0
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHlm.bitmover.com
cK03739
cPdoc/Makefile
cR9262ecd1cb60d077
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
# Makefile for lmbench doc subdir.
# $Id$

I 12
SHELL=/bin/sh
E 12
D 5
MS = description.ms 
E 5
I 5
DESC = description.ms 
D 10
USENIX = usenix96.ms
E 10
I 10
USENIX = tmac.usenix usenix96.ms 
E 10
E 5
D 7
PIC = ctx.pic mem.pic
E 7
I 7
PIC = ctx.pic mem.pic 
D 9
GRAPHS = bw.pic memrd_bcopy_comp.pic
E 7
I 5
REFER = references.i
E 9
I 9
D 10
GRAPHS = 
#REFER = references.i
E 10
E 9
E 5
I 4
SCRIPTS = ../scripts/
E 4

D 16
MAN = lmbench.8 \
	lat_proc.8 lat_mmap.8 lat_ctx.8 lat_syscall.8 lat_pipe.8 	\
	lat_tcp.8 lat_udp.8 lat_rpc.8 lat_connect.8 lat_fs.8		\
D 3
	lat_mem_rd.8 \
E 3
I 3
	lat_pagefault.8 lat_mem_rd.8 \
E 3
	bw_file_rd.8 bw_mem_cp.8 bw_mem_rd.8 bw_mem_wr.8 bw_mmap_rd.8	\
	bw_pipe.8 bw_tcp.8 \
	mhz.8 lmdd.8 \
E 16
I 16
MAN =	bargraph.1 graph.1 pgraph.1 rccs.1				\
	lmbench.3 reporting.3 results.3 timing.3			\
	bw_file_rd.8 bw_mem.8 bw_pipe.8 bw_pipe.8 bw_tcp.8 bw_unix.8	\
	lat_connect.8 lat_ctx.8 lat_fcntl.8 lat_fifo.8 lat_fs.8 	\
	lat_http.8 lat_mem_rd.8 lat_mmap.8 lat_pagefault.8 lat_pipe.8 	\
	lat_proc.8 lat_rpc.8 lat_select.8 lat_sig.8 lat_syscall.8 	\
	lat_tcp.8 lat_udp.8 lat_unix.8 lat_unix_connect.8		\
	lmbench.8 disk.8 lmdd.8 mhz.8 					\
	clock.8 enough.8 loop_o.8 timing_o.8				\
E 16
	bargraph.1 graph.1

D 5
PS: $(MS) $(MAN) $(PIC)
	groff -s -p -mgs $(MS) > MS.PS
E 5
I 5
D 7
ALL = $(DESC) $(USENIX) $(PIC) $(MAN) $(REFER)
E 7
I 7
D 10
ALL = $(DESC) $(USENIX) $(PIC) $(MAN) $(REFER) $(GRAPHS)
E 10
I 10
ALL = $(DESC) $(USENIX) $(PIC) $(MAN) $(REFER) references
E 10
E 7

PS ps: $(ALL)
D 6
	groff -s -p -R -mgs $(USENIX) > USENIX.PS
E 6
I 6
D 9
	groff -t -s -p -R -mgs $(USENIX) > USENIX.PS
E 9
I 9
	gindxbib references
D 10
	groff -t -s -p -R tmac.usenix $(USENIX) > USENIX.PS
E 10
I 10
D 11
	groff -t -s -p -R $(USENIX) > USENIX.PS
E 11
I 11
	groff -t -e -s -p -R $(USENIX) > USENIX.PS
E 11
E 10
E 9
E 6
D 8
	groff -s -p -mgs $(DESC) > DESC.PS
E 5
	groff -fH -man $(MAN) > MAN.PS
E 8
I 8
	#groff -s -p -mgs $(DESC) > DESC.PS
	#groff -fH -man $(MAN) > MAN.PS
E 8

D 5
X x: $(MS) $(MAN) $(PIC)
D 4
	xroff -s -p -mgs $(MS) 
	xroff -man -fH $(MAN) 
E 4
I 4
	$(SCRIPTS)xroff -s -p -mgs $(MS) 
E 5
I 5
X x: $(ALL)
D 6
	$(SCRIPTS)xroff -s -p -R -mgs $(USENIX) 
E 6
I 6
D 9
	$(SCRIPTS)xroff -t -s -p -R -mgs $(USENIX) 
E 9
I 9
	gindxbib references
D 10
	$(SCRIPTS)xroff -t -s -p -R tmac.usenix $(USENIX) 
E 10
I 10
D 11
	$(SCRIPTS)xroff -t -s -p -R $(USENIX) 
E 11
I 11
	$(SCRIPTS)xroff -t -e -s -p -R $(USENIX) 
E 11
E 10
E 9
E 6
D 8
	$(SCRIPTS)xroff -s -p -mgs $(DESC) 
E 5
	$(SCRIPTS)xroff -man -fH $(MAN) 
E 8
I 8
	#$(SCRIPTS)xroff -s -p -mgs $(DESC) 
	#$(SCRIPTS)xroff -man -fH $(MAN) 
E 8
E 4

D 5
text: $(MS) $(MAN) $(PIC)
	nroff -s -p -ms $(MS) | colcrt - | more
E 5
I 5
text: $(ALL)
D 6
	nroff -s -p -R -ms $(USENIX) | colcrt - | more
E 6
I 6
D 8
	nroff -t -s -p -R -ms $(USENIX) | colcrt - | more
E 6
	nroff -s -p -ms $(DESC) | colcrt - | more
E 5
	nroff -man $(MAN) | more
E 8
I 8
D 9
	groff -Tascii -t -s -p -R -mgs $(USENIX) | colcrt - | more
E 9
I 9
	gindxbib references
D 10
	groff -Tascii -t -s -p -R -ms $(USENIX) 2>/dev/null | colcrt - | more
E 10
I 10
D 11
	groff -Tascii -t -s -p -R $(USENIX) 2>/dev/null | colcrt - | more
E 11
I 11
D 12
	groff -Tascii -t -e -s -p -R $(USENIX) 2>/dev/null | colcrt - | more
E 11
E 10
E 9
	#groff -Tascii -s -p -mgs $(DESC) | colcrt - | more
	#groff -Tascii -man $(MAN) | more
E 12
I 12
	gsoelim usenix96.ms | sed "s/expand doublebox/center/" | \
	sed s/doublebox// > Fixed.ms
	groff -Tascii -t -e -s -p -R -mgs Fixed.ms 2>/dev/null | colcrt - | more
E 12
E 8

D 5
get: $(MS) $(MAN) $(PIC)
E 5
I 5
D 9
$(REFER): references
	gindxbib references
E 5

I 7
D 8
bw.pic : bw.graph
	$(SCRIPTS)graph -small -nobox -logy < bw.graph > bw.pic
E 8
I 8
bw.pic : 
	rccs get -s -kv bw.graph
	$(SCRIPTS)graph -small -nobox -logy -nodatal -nomarks < bw.graph > bw.pic
E 8

D 8
memrd_bcopy_comp.pic : memrd_bcopy_comp.graph
	$(SCRIPTS)graph -small -nobox < memrd_bcopy_comp.graph > memrd_bcopy_comp.pic
E 8
I 8
memrd_bcopy_comp.pic : 
	rccs get -s -kv memrd_bcopy_comp.graph
	$(SCRIPTS)graph -small -nobox -nodatal -nomarks < memrd_bcopy_comp.graph > memrd_bcopy_comp.pic
E 8

E 9
E 7
I 5
get: $(ALL)

E 5
edit:
D 5
	rccs edit -s $(MS) $(MAN) $(PIC)
E 5
I 5
D 13
	rccs edit -s $(ALL)
E 13
I 13
D 14
	../rccs edit -s $(ALL)
E 14
I 14
	get -e -s $(ALL)
E 14
E 13
E 5

$(MAN):
D 13
	rccs get -s -kv $(MAN)
E 13
I 13
D 14
	../rccs get -s -kv $(MAN)
E 14
I 14
	get -s $(MAN)
E 14
E 13

$(PIC):
D 13
	rccs get -s -kv $(PIC)
E 13
I 13
D 14
	../rccs get -s -kv $(PIC)
E 14
I 14
	get -s $(PIC)
E 14
E 13

D 5
$(MS):
	rccs get -s -kv $(MS)
E 5
I 5
$(DESC):
D 13
	rccs get -s -kv $(DESC)
E 13
I 13
D 14
	../rccs get -s -kv $(DESC)
E 14
I 14
	get -s $(DESC)
E 14
E 13
E 5

I 5
$(USENIX):
D 8
	rccs get -s -kv $(DESC)
E 8
I 8
D 13
	rccs get -s -kv $(USENIX)
E 13
I 13
D 14
	../rccs get -s -kv $(USENIX)
E 14
I 14
	get -s $(USENIX)
E 14
E 13
E 8

I 8
D 9
$(GRAPHS):

E 9
D 10
references:
	rccs get -s -kv references

E 10
E 8
E 5
clean:
D 13
	rccs clean -e -s
E 13
I 13
D 14
	../rccs clean -e -s
E 14
I 14
D 15
	clean 
E 15
I 15
	-bk clean 
E 15
E 14
E 13
D 8
	/bin/rm -f *.PS XXX
E 8
I 8
	/bin/rm -f *.PS XXX bw.pic memrd_bcopy_comp.pic references.i
E 8
E 2
I 1
E 1
