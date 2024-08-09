obj-m += cpu0_sync.o

SRC := $(shell pwd)
ARCH := arm
CROSS_COMPILE := arm-xilinx-linux-gnueabi-

all:
	$(MAKE) ARCH=${ARCH} CROSS_COMPILE=${CROSS_COMPILE} M=$(SRC) O=$(O) -C $(KERNEL_SRC) modules

modules_install:
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC) modules_install

.PHONEY: clean
clean:
	rm -rf *.o *.ko *.cmd .*.cmd *.mod.c *.order *.symvers .tmp_versions
