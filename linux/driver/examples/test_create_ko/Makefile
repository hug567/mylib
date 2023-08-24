obj-m += test_create_ko.o

CROSS_COMPILE = /opt/pkg/petalinux/tools/xsct/gnu/aarch32/lin/gcc-arm-none-eabi/bin/arm-none-eabi-
YOCTO_TOP = ${HOME}/workspace/yocto
YOCTO_WORK = ${YOCTO_TOP}/build/tmp/work
LINUX_DIR = ${YOCTO_WORK}/plnx_zynq7-xilinx-linux-gnueabi/linux-xlnx
KERNEL_BUILD := ${LINUX_DIR}/4.19-xilinx-v2019.1+gitAUTOINC+cae6ff5218-r0/linux-plnx_zynq7-standard-build/

all:
	make ARCH=arm CROSS_COMPILE=${CROSS_COMPILE} M=${PWD} -C ${KERNEL_BUILD} modules

clean:
	rm -rf *.order *.symvers *.ko *.mod.c *.o .*.cmd .tmp_versions
