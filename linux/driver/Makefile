# obj-y: 编译进内核
# obj-m: 编译成ko模块

obj-m += test_char.o

KERNEL := /lib/modules/`uname -r`/build
PWD = $(shell pwd)

	#make ARCH=${ARCH} CROSS_COMPILE=$(CROSS_COMPILE) M=$(PWD) -C $(KERNEL) modules
modules:
	make M=$(PWD) -C $(KERNEL) modules
	rm -rf modules.order Module.symvers .cache.mk .tmp_versions
	rm -rf .*.ko.cmd .*.o.cmd *.o *.mod.c

.PHONEY: clean
clean:
	rm -f *.o *.ko
