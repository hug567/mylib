# obj-y: 编译进内核
# obj-m: 编译成ko模块

obj-m += test_char.o
obj-m += mychar2.o
obj-m += virt_net_driver.o
obj-m += vexpress/myuart.o

BUILD_DIR=mybuild
KERNEL = ${HOME}/code/linux/linux-4.18
#KERNEL = /lib/modules/`uname -r`/build
CUR_DIR = $(shell pwd)/${BUILD_DIR}

CROSS_COMPILE=arm-linux-gnueabi-
T_CC=${CROSS_COMPILE}gcc
T_CFLAGS=-Wall

prepare:
	rm -rf ${BUILD_DIR}
	mkdir ${BUILD_DIR}
	cp -rP `ls | grep -v ${BUILD_DIR}` ${BUILD_DIR}
	cd ${BUILD_DIR}
	make modules

modules: tests
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- M=${CUR_DIR} -C ${KERNEL} modules

tests:
	${T_CC} ${T_CFLAGS} ${CUR_DIR}/vexpress/test_myuart.c -o ${CUR_DIR}/test_myuart

.PHONEY: clean
clean:
	rm -rf ${BUILD_DIR}
