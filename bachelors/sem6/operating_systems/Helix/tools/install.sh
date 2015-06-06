# Create a floppy image formatted as FAT
rm -f ../output/floppy.img
#cp ./fdboot.img ../output/floppy.img 
#mkfs.fat -F 16 -C ../output/floppy.img

dd if=/dev/zero of=../output/floppy.img bs=1024 count=1440
sudo losetup /dev/loop0 ../output/floppy.img
sudo mkdosfs /dev/loop0 -F 12 -c -v
sudo losetup -D

# Populate the boot sector
dd if=../output/boot0.bin of=../output/floppy.img bs=1 count=3 conv=notrunc
dd if=../output/boot0.bin of=../output/floppy.img bs=1 count=450 seek=62 skip=62 conv=notrunc

# Copy the second boot loader and kernel as files
mkdir -p /tmp/floppy_mount
sudo mount -oloop,uid=$UID -t msdos -o "fat=12" ../output/floppy.img /tmp/floppy_mount
rm -Rf /tmp/floppy_mount/*
cp -R ../output/boot1.bin /tmp/floppy_mount/
cp -R ../output/kernel.bin /tmp/floppy_mount/
sudo umount /tmp/floppy_mount
