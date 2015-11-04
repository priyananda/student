LDSCRIPT=boot.ld
CFLAGS=-nostdinc -fno-builtin -fno-stack-protector -fno-builtin -fno-unit-at-a-time -fno-toplevel-reorder -m16
LDFLAGS=-T$(LDSCRIPT) -m elf_i386
DEL=rm
OUTDIR=../output
BUILDDIR=../build

all: $(OUTDIR)/boot0.bin $(OUTDIR)/boot1.bin

$(OUTDIR)/boot0.bin : boot0.asm
	nasm -f bin -o$@ $<
	
$(OUTDIR)/boot1.bin : $(BUILDDIR)/boot1.elf
#	objcopy -O binary $< $@
	
	
$(BUILDDIR)/boot1.elf : $(BUILDDIR)/boot_startup.o $(BUILDDIR)/boot_main.o $(BUILDDIR)/fat12.o $(BUILDDIR)/graphics.o $(BUILDDIR)/boot1.o
	ld $(LDFLAGS) -o$@ $?
	
$(BUILDDIR)/boot_startup.o : boot_startup.asm
	nasm -f elf32 -o$@ $<

$(BUILDDIR)/graphics.o : graphics.asm
	nasm -f elf32 -o$@ $<

$(BUILDDIR)/%.o : %.c
	gcc $(CFLAGS) -c -o$@ $<

clean:
	$(DEL) -f $(BUILDDIR)/*.*
	$(DEL) -f $(OUTDIR)/*.*

