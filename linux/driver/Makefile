# obj-y: 编译进内核
# obj-m: 编译成ko模块

obj-m += test_char.o

KERNEL := /lib/modules/`uname -r`/build
PWD = $(shell pwd)

modules:
	make -C $(KERNEL) M=$(PWD) modules
	rm -rf modules.order Module.symvers .cache.mk .tmp_versions
	rm -rf .*.ko.cmd .*.o.cmd *.o *.mod.c

.PHONEY: clean
clean:
	rm -f *.o *.ko
