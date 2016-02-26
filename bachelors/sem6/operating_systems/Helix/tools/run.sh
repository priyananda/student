EXTRA_OPTIONS=
if [ "$1" == "d" ]; then
	EXTRA_OPTIONS="-s -S"
fi

qemu-system-i386 -fda ../output/floppy.img -hdachs 1,2,18,lba $EXTRA_OPTIONS
