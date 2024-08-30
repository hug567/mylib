#!/bin/bash
# 编译linux主线
# 编译arm vexpress
# 2024-08-30

# 生成.config配置文件
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabihf- vexpress_defconfig

# 编译内核
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabihf- -j3

# 编译内核模块(.ko)
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabihf- modules -j3

# 编译dts文件(生成dtb文件)
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabihf- dtbs -j3
