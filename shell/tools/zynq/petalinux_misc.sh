#!/bin/bash

exit 0

# 创建petalinux工程：
# 不能使用zsh
bash
source /opt/pkg/petalinux/settings.sh
petalinux-create --type project --template zynq --name ax_peta
cd ax_peta/
petalinux-config --get-hw-description ../linux_base.sdk
petalinux-config -c kernel
petalinux-config -c rootfs
petalinux-build
petalinux-package --boot --fsbl ./images/linux/zynq_fsbl.elf --fpga --u-boot --force
# 不打包fpga程序
petalinux-package --boot --fsbl ./images/linux/zynq_fsbl.elf --u-boot --force

# download source code
mkdir workspace
cd workspace
repo init -u http://192.168.99.221:3000/Rhosoon_RD/manifest.git -b main --no-repo-verify
repo sync
repo start main --all
repo forall -c "git lfs pull"

# using bitbake
source /opt/pkg/petalinux/settings.sh
source /opt/pkg/petalinux/components/yocto/source/arm/environment-setup-cortexa9hf-neon-xilinx-linux-gnueabi
source /opt/pkg/petalinux/components/yocto/source/arm/layers/core/oe-init-build-env
export PATH=/opt/pkg/petalinux/tools/hsm/bin:$PATH
export BB_ENV_EXTRAWHITE="$BB_ENV_EXTRAWHITE PETALINUX"

# using bitbake in petalinux 2019.1
source /opt/pkg/petalinux/settings.sh
source /opt/pkg/petalinux/components/yocto/source/arm/environment-setup-cortexa9t2hf-neon-xilinx-linux-gnueabi
source /opt/pkg/petalinux/components/yocto/source/arm/layers/core/oe-init-build-env
export PATH=/opt/pkg/petalinux/tools/xsct/bin:$PATH
export BB_ENV_EXTRAWHITE="$BB_ENV_EXTRAWHITE PETALINUX"

# tftp get file to sd card
setenv serverip 10.110.0.3
saveenv
tftpboot 0x00000000 BOOT.BIN
fatwrite mmc 0 00000000 BOOT.BIN 0x1eac08
tftpboot 0x00000000 image.ub
fatwrite mmc 0 00000000 image.ub 0x90caa8
boot

# using existing file
fatload mmc 0 0x00000000 /success/BOOT.BIN
fatwrite mmc 0 00000000 BOOT.BIN 0x1eac08
fatload mmc 0 0x00000000 /success/image.ub
fatwrite mmc 0 00000000 image.ub 0x90caa8

# ssh get file
cd /run/media/mmcblk0; scp hx@10.110.0.3:~/temp/tftpboot/\{BOOT.BIN,image.ub\} .

ifconfig eth0 10.110.0.10 netmask 255.255.255.0

# build step by step
source /opt/pkg/petalinux/settings.sh
#source /opt/Xilinx/Vivado/2017.4/settings64.sh
petalinux-config --oldconfig
petalinux-config -c kernel --defconfig xilinx_zynq_defconfig
petalinux-config -c rootfs --oldconfig
petalinux-build
petalinux-package --boot --fsbl ./images/linux/zynq_fsbl.elf --fpga --u-boot --force

kill $(ps aux | grep petalinux-2017 | grep -v grep | awk '{print$2}')

tftpboot 0x20000000 image.ub
bootm 0x20000000

# run core1 bare-metal program
echo core1.elf > /sys/class/remoteproc/remoteproc0/firmware
echo start > /sys/class/remoteproc/remoteproc0/state
modprobe rpmsg_user_dev_driver
# 创建petalinux工程：
# 不能使用zsh
bash
source /opt/pkg/petalinux/settings.sh
petalinux-create --type project --template zynq --name ax_peta
cd ax_peta/
petalinux-config --get-hw-description ../linux_base.sdk
petalinux-config -c kernel
petalinux-config -c rootfs
petalinux-build
petalinux-package --boot --fsbl ./images/linux/zynq_fsbl.elf --fpga --u-boot --force
# 不打包fpga程序
petalinux-package --boot --fsbl ./images/linux/zynq_fsbl.elf --u-boot --force

# download source code
mkdir workspace
cd workspace
repo init -u http://192.168.99.221:3000/Rhosoon_RD/manifest.git -b main --no-repo-verify
repo sync
repo start main --all
repo forall -c "git lfs pull"

# using bitbake
source /opt/pkg/petalinux/settings.sh
source /opt/pkg/petalinux/components/yocto/source/arm/environment-setup-cortexa9hf-neon-xilinx-linux-gnueabi
source /opt/pkg/petalinux/components/yocto/source/arm/layers/core/oe-init-build-env
export PATH=/opt/pkg/petalinux/tools/hsm/bin:$PATH
export BB_ENV_EXTRAWHITE="$BB_ENV_EXTRAWHITE PETALINUX"

# using bitbake in petalinux 2019.1
source /opt/pkg/petalinux/settings.sh
source /opt/pkg/petalinux/components/yocto/source/arm/environment-setup-cortexa9t2hf-neon-xilinx-linux-gnueabi
source /opt/pkg/petalinux/components/yocto/source/arm/layers/core/oe-init-build-env
export PATH=/opt/pkg/petalinux/tools/xsct/bin:$PATH
export BB_ENV_EXTRAWHITE="$BB_ENV_EXTRAWHITE PETALINUX"

# tftp get file to sd card
setenv serverip 10.110.0.3
saveenv
tftpboot 0x00000000 BOOT.BIN
fatwrite mmc 0 00000000 BOOT.BIN 0x1eac08
tftpboot 0x00000000 image.ub
fatwrite mmc 0 00000000 image.ub 0x90caa8
boot

# using existing file
fatload mmc 0 0x00000000 /success/BOOT.BIN
fatwrite mmc 0 00000000 BOOT.BIN 0x1eac08
fatload mmc 0 0x00000000 /success/image.ub
fatwrite mmc 0 00000000 image.ub 0x90caa8

# ssh get file
cd /run/media/mmcblk0; scp hx@10.110.0.3:~/temp/tftpboot/\{BOOT.BIN,image.ub\} .

ifconfig eth0 10.110.0.10 netmask 255.255.255.0

# build step by step
source /opt/pkg/petalinux/settings.sh
#source /opt/Xilinx/Vivado/2017.4/settings64.sh
petalinux-config --oldconfig
petalinux-config -c kernel --defconfig xilinx_zynq_defconfig
petalinux-config -c rootfs --oldconfig
petalinux-build
petalinux-package --boot --fsbl ./images/linux/zynq_fsbl.elf --fpga --u-boot --force

kill $(ps aux | grep petalinux-2017 | grep -v grep | awk '{print$2}')

tftpboot 0x20000000 image.ub
bootm 0x20000000

# run core1 bare-metal program
echo core1.elf > /sys/class/remoteproc/remoteproc0/firmware
echo start > /sys/class/remoteproc/remoteproc0/state
modprobe rpmsg_user_dev_driver
