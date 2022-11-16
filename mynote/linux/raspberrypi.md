# 1、代码下载

```bash
git clone https://github.com/raspberrypi/linux.git
git clone https://gitee.com/xfan1024/raspberrypi_linux.git

mkdir build-rpi3b
cd build-rpi3b
make -C ../ O=`pwd` ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- bcmrpi3_defconfig
make -C ../ O=`pwd` ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -j3

qemu-system-aarch64  \
    -M raspi3b -m 1024 -nographic \
    -initrd rootfs.cpio \
    -kernel arch/arm64/boot/Image \
    -dtb ./arch/arm64/boot/dts/broadcom/bcm2710-rpi-3-b.dtb \
    --append "rw earlycon=pl011,0x3f201000 console=ttyAMA0 loglevel=8 rdinit=/linuxrc fsck.repair=yes net.ifnames=0 rootwait memtest=1 dwc_otg.fiq_fsm_enable=0"      
```

