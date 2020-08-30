# obj-y: 编译进内核
# obj-m: 编译成ko模块

obj-m += test_char.o
obj-m += test_char2.o

KERNEL = ~/code/linux/linux-4.15
#KERNEL = /lib/modules/`uname -r`/build
PWD = $(shell pwd)

modules:
	#make M=${PWD} -C ${KERNEL} modules
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- M=${PWD} -C ${KERNEL} modules
	rm -rf modules.order Module.symvers .cache.mk .tmp_versions
	rm -rf .*.ko.cmd .*.o.cmd *.o *.mod.c

.PHONEY: clean
clean:
	rm -f *.o *.ko
