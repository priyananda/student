CFLAGS=-nostdinc -fno-builtin -m32 -fno-stack-protector
LDFLAGS=-T$(LDSCRIPT)
INCDIR=include
BUILDDIR=../../build
BUILDDIRFS=$(BUILDDIR)/fs

$(BUILDDIR)/fs.a : $(BUILDDIRFS)/cache.o $(BUILDDIRFS)/dir.o $(BUILDDIRFS)/diskette.o $(BUILDDIRFS)/error.o $(BUILDDIRFS)/fnode.o $(BUILDDIRFS)/global.o $(BUILDDIRFS)/init.o $(BUILDDIRFS)/link.o $(BUILDDIRFS)/login.o $(BUILDDIRFS)/misc.o $(BUILDDIRFS)/mkfs.o $(BUILDDIRFS)/mount.o $(BUILDDIRFS)/open.o $(BUILDDIRFS)/path.o $(BUILDDIRFS)/perm.o $(BUILDDIRFS)/read.o $(BUILDDIRFS)/write.o $(BUILDDIRFS)/dostar.o $(BUILDDIRFS)/fileio.o $(BUILDDIRFS)/shell.o $(BUILDDIRFS)/dohelp.o $(BUILDDIRFS)/norm.o
	ar cr $@ $<

$(BUILDDIRFS)/%.o : %.c
	gcc $(CFLAGS) -I$(INCDIR) -c -o$@ $<

clean:e
	rm -f $(BUILDDIRFS)/*.o
	rm -f $(BUILDDIR)/fs.a
