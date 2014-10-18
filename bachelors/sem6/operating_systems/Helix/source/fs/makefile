CFLAGS=-nostdinclude -fno-builtin
LDFLAGS=-T$(LDSCRIPT)
INCDIR=include

.c.o:
	gcc $(CFLAGS) -I$(INCDIR) -c -o$@ $<

..\..\output\fs.a : cache.o dir.o diskette.o error.o fnode.o global.o init.o link.o login.o misc.o mkfs.o mount.o open.o path.o perm.o read.o write.o dostar.o fileio.o shell.o dohelp.o norm.o
	ar cr ..\..\output\fs.a *.o
