h39805
s 00011/00000/00000
d D 1.1 00/07/31 15:26:00 staelin 2 1
cC
cK10474
cO-rwxrwxr-x
e
s 00000/00000/00000
d D 1.0 00/07/31 15:25:59 staelin 1 0
c BitKeeper file /tmp_mnt/usr/WebPaper/users/staelin/src/LMbench2/scripts/make
cBlm@lm.bitmover.com|ChangeSet|20000131225335|47351|--LMBENCH--
cHhpli8.hpli.hpl.hp.com
cK32332
cPscripts/make
cR6b5338a43982f8f8
cV4
cX0xa1
cZ+03:00
e
u
U
f e 0
f x 0xa1
t
T
I 2
#!/bin/sh

if [ X$MAKE = X ]
then	MAKE=make
	for p in `echo $PATH | sed 's/:/ /g'`
	do	if [ -f $p/gmake ]
		then	MAKE=gmake
		fi
	done
fi
echo $MAKE
E 2
I 1
E 1
