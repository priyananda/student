LDSCRIPT=kernel.ld
CFLAGS=-nostdinc -fno-builtin -m32 -fno-stack-protector
LDFLAGS=-T$(LDSCRIPT) -m elf_i386
INCDIR=include
AFLAGS=-f coff -i$(INCDIR) -isource/asm/
DEL=rm -f
BUILDDIR=build
BUILDDIRKERNEL=build/kernel

all: output/kernel.bin output/boot0.bin output/boot1.bin

output/kernel.bin : $(BUILDDIR)/kernel.out
	objcopy --output-target=binary $(BUILDDIR)/kernel.out output/kernel.bin

$(BUILDDIR)/kernel.out :source/main.o $(BUILDDIR)/startup.o $(BUILDDIR)/keyb.o $(BUILDDIR)/int.a $(BUILDDIR)/io.a $(BUILDDIR)/klib.a $(BUILDDIR)/fs.a
	ld $(LDFLAGS) -o $(BUILDDIR)/kernel.out $(BUILDDIR)/startup.o source/main.o $(BUILDDIR)/keyb.o $(BUILDDIR)/*.a

$(BUILDDIR)/klib.a : source/klib/atoi.o source/klib/ctype.o source/klib/key.o source/klib/printf.o source/klib/string.o
	ar cr $(BUILDDIR)/klib.a source/klib/atoi.o source/klib/ctype.o source/klib/key.o source/klib/printf.o source/klib/string.o

$(BUILDDIR)/io.a : source/io/io.o source/io/video.o source/io/pic.o source/io/keymap.o source/io/keyboard.o source/io/floppy.o source/io/ports.o
	ar cr $(BUILDDIR)/io.a source/io/io.o source/io/video.o source/io/pic.o source/io/keymap.o source/io/keyboard.o source/io/floppy.o source/io/ports.o

$(BUILDDIR)/int.a : source/int/intrfun.o source/int/intrutil.o
	ar cr $(BUILDDIR)/int.a source/int/intrfun.o source/int/intrutil.o

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
	$(DEL) $(BUILDDIR)/*.o
	$(DEL) $(BUILDDIR)/*.a
	$(DEL) source/io/*.o
	$(DEL) source/int/*.o
	$(DEL) source/fs/*.o
	$(DEL) source/klib/*.o
	$(DEL) source/asm/real
	$(DEL) source/asm/prot16
	$(DEL) source/main.o

.c.o:
	gcc $(CFLAGS) -I$(INCDIR) -c -o$@ $<

.asm.o:
	nasm $(AFLAGS) -o$@ $<

