#KERNEL_VERSION=2.6.27-7-generic
KERNEL_VERSION=2.6.27.5

obj-m += print_debug.o

all:
	make -C /lib/modules/$(KERNEL_VERSION)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(KERNEL_VERSION)/build M=$(PWD) clean 
