# 1、petalinux安装：

```bash
# 以非root用户登录
sudo apt install xterm build-essential

# ubuntu16
sudo dpkg --add-architecture i386
sudo apt-get update
sudo apt-get install zlib1g-dev:i386
sudo apt-get install tofrodos gawk xvfb git libncurses5-dev tftpd zlib1g-dev libssl-dev flex bison chrpath socat autoconf libtool texinfo gcc-multilib libsdl1.2-dev libglib2.0-dev screen pax

cd /opt
sudo mkdir -p pkg/petalinux
sudo chown -R hx:hx pkg
cd ...
./petalinux-v2017.4-final-installer.run /opt/pkg/petalinux
```

# 2、petalinux创建linux工程：

## 1)、新建工程：

```bash
mkdir workspace
cd workspace
cp -r .../linux_base.sdk ./

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

# 生成产物
-rw-rw-r-- 1 hx hx 2.0M Jul 31 18:11 images/linux/BOOT.BIN
-rw-r--r-- 1 hx hx 9.1M Jul 31 07:49 images/linux/image.ub
```

## 2)、已有工程手动配置config：

```bash
git clone http://10.110.0.3:9002/linux/yocto.git
cd yocto
source /opt/pkg/petalinux/settings.sh
petalinux-config
petalinux-config -c kernel
petalinux-config -c rootfs
petalinux-build
petalinux-package --boot --fsbl ./images/linux/zynq_fsbl.elf --fpga --u-boot --force
```

## 3)、使用旧config：

- 可在脚本中自动化构建已有工程；

```bash
git clone http://10.110.0.3:9002/linux/yocto.git
cd yocto
source /opt/pkg/petalinux/settings.sh
petalinux-config --oldconfig
petalinux-config -c kernel --defconfig xilinx_zynq_defconfig
petalinux-config -c rootfs --oldconfig
petalinux-build
petalinux-package --boot --fsbl ./images/linux/zynq_fsbl.elf --fpga --u-boot --force
```

## 4)、单独编译一个组件：

```bash
bash
source /opt/pkg/petalinux/settings.sh
petalinux-build -c linux-xlnx
petalinux-build -c device-tree-generation -x cleanall
petalinux-build -c petalinux-image -x cleanall
```

## 5)、使用bitbake：

```bash
source /opt/pkg/petalinux/settings.sh
source /opt/pkg/petalinux/components/yocto/source/arm/environment-setup-cortexa9hf-neon-xilinx-linux-gnueabi
source /opt/pkg/petalinux/components/yocto/source/arm/layers/core/oe-init-build-env
export PATH=/opt/pkg/petalinux/tools/hsm/bin:$PATH
export BB_ENV_EXTRAWHITE="$BB_ENV_EXTRAWHITE PETALINUX"
```

## 6)、petalinux一个app：

- 参考资料：UG1144 PetaLinux Tools Documentation Reference Guide: Creating and Adding Custom Applications

```bash
```

## 7)、petalinux一个内核模块(驱动)：

- 参考资料：UG1144 PetaLinux Tools Documentation Reference Guide: Creating and Adding Custom Modules
