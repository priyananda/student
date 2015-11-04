LDSCRIPT=kernel.ld
CFLAGS=-nostdinc -fno-builtin -m32 -fno-stack-protector
LDFLAGS=-T$(LDSCRIPT) -m elf_i386 --verbose 
INCDIR=include
AFLAGS=-f coff -i$(INCDIR) -isource/asm/
DEL=rm -f
BUILDDIR=build
BUILDDIRINT=build/int
BUILDDIRIO=build/io
BUILDDIRKLIB=build/klib

all: output/kernel.bin output/boot0.bin output/boot1.bin

output/kernel.bin : $(BUILDDIR)/kernel.out
	objcopy --output-target=binary $(BUILDDIR)/kernel.out output/kernel.bin

$(BUILDDIR)/kernel.out : $(BUILDDIR)/main.o $(BUILDDIR)/startup.o $(BUILDDIR)/keyb.o $(BUILDDIR)/fs.a $(BUILDDIR)/io.a $(BUILDDIR)/int.a $(BUILDDIR)/klib.a
	ld $(LDFLAGS) -o $@ $?

$(BUILDDIR)/klib.a : $(BUILDDIRKLIB)/atoi.o $(BUILDDIRKLIB)/ctype.o $(BUILDDIRKLIB)/key.o $(BUILDDIRKLIB)/printf.o $(BUILDDIRKLIB)/string.o
	ar cr $@ $?

$(BUILDDIR)/io.a : $(BUILDDIRIO)/io.o $(BUILDDIRIO)/video.o $(BUILDDIRIO)/pic.o $(BUILDDIRIO)/keymap.o $(BUILDDIRIO)/keyboard.o $(BUILDDIRIO)/floppy.o $(BUILDDIRIO)/ports.o
	ar cr $@ $?

$(BUILDDIR)/int.a : $(BUILDDIRINT)/intrfun.o $(BUILDDIRINT)/intrutil.o
	ar cr $@ $?

$(BUILDDIR)/startup.o : source/asm/startup.asm $(BUILDDIR)/real.bin $(BUILDDIR)/prot16.bin
	nasm $(AFLAGS) -i$(BUILDDIR)/ -o$@ $<

$(BUILDDIR)/real.bin : source/asm/real.asm
	nasm  -o$(BUILDDIR)/real.out source/asm/real.asm
	tools/bin.exe $(BUILDDIR)/real.out $(BUILDDIR)/real.bin

$(BUILDDIR)/prot16.bin : source/asm/prot16.asm
	nasm  -o$(BUILDDIR)/prot16.out source/asm/prot16.asm
	tools/bin.exe $(BUILDDIR)/prot16.out $(BUILDDIR)/prot16.bin

$(BUILDDIR)/keyb.o : source/asm/keyb.asm
	nasm $(AFLAGS) -o$@ $<
	
$(BUILDDIR)/fs.a :
	make -C source/fs

output/boot0.bin : output/boot1.bin

output/boot1.bin :
	make -C boot

clean ::
	$(DEL) output/*.*
	$(DEL) $(BUILDDIR)/*.*
	$(DEL) $(BUILDDIRIO)/*.o
	$(DEL) $(BUILDDIRKLIB)/*.o
	$(DEL) $(BUILDDIRINT)/*.o
	$(DEL) $(BUILDDIR)/fs/*.o

$(BUILDDIRINT)/%.o : source/int/%.c
	gcc $(CFLAGS) -I$(INCDIR) -c -o$@ $<

$(BUILDDIRIO)/%.o : source/io/%.c
	gcc $(CFLAGS) -I$(INCDIR) -c -o$@ $<

$(BUILDDIRKLIB)/%.o : source/klib/%.c
	gcc $(CFLAGS) -I$(INCDIR) -c -o$@ $<

$(BUILDDIR)/%.o : source/%.c
	gcc $(CFLAGS) -I$(INCDIR) -c -o$@ $<

.asm.o:
	nasm $(AFLAGS) -o$@ $<
