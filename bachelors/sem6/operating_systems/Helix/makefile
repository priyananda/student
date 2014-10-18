LDSCRIPT=kernel.ld
CFLAGS=-nostdinclude -fno-builtin
LDFLAGS=-T$(LDSCRIPT)
INCDIR=include
AFLAGS=-f coff -i$(INCDIR)


kernel.bin : kernel.out
	objcopy --output-target=binary kernel.out kernel.bin

kernel.out :source/main.o output/startup.o output/keyb.o output/int.a output/io.a output/klib.a output/fs.a
	ld $(LDFLAGS) -o kernel.out output/startup.o source/main.o output/keyb.o output/*.a

output/klib.a : source/klib/atoi.o source/klib/ctype.o source/klib/key.o source/klib/printf.o source/klib/string.o
	ar cr output/klib.a source/klib/atoi.o source/klib/ctype.o source/klib/key.o source/klib/printf.o source/klib/string.o

output/io.a : source/io/io.o source/io/video.o source/io/pic.o source/io/keymap.o source/io/keyboard.o source/io/floppy.o source/io/ports.o
	ar cr output/io.a source/io/io.o source/io/video.o source/io/pic.o source/io/keymap.o source/io/keyboard.o source/io/floppy.o source/io/ports.o

output/int.a : source/int/intrfun.o source/int/intrutil.o
	ar cr output/int.a source/int/intrfun.o source/int/intrutil.o

output/startup.o :: source/asm/startup.asm
	nasm source/asm/real.asm
	nasm source/asm/prot16.asm
	bin source\asm\real real.bin
	bin source\asm\prot16 prot16.bin
	nasm $(AFLAGS) -o$@ $<

output/keyb.o : source/asm/keyb.asm
	nasm $(AFLAGS) -o$@ $<

clean ::
	@del output\*.o
	@del output\*.a > nul
	@del source\io\*.o > nul
	@del source\int\*.o > nul
	@del source\fs\*.o > nul
	@del source\klib\*.o > nul
	@del source\asm\real > nul
	@del source\asm\prot16 > nul
	@del source\main.o > nul
	@del *.bin > nul
	@del *.out > nul

.c.o:
	gcc $(CFLAGS) -I$(INCDIR) -c -o$@ $<

.asm.o:
	nasm $(AFLAGS) -o$@ $<

