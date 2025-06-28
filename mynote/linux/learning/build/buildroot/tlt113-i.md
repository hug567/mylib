# 1、TLT113-i编译镜像：

## 1）、需要的文件：

- LinuxSDK-v1.4.tar.gz (5.5G)
- dl.tar.gz (1.2G)

## 2）、制作docker镜像：

```bash
# 基础镜像：
ubuntu 18.04
# 安装工具：
sudo apt install texinfo pkg-config nfs-kernel-server samba ssh gcc autoconf patch wget texinfo zlib1g-dev dos2unix git gnupg flex bison gperf build-essential zip curl libc6-dev libncurses5-dev:i386 x11proto-core-dev libx11-dev:i386 libreadline6-dev:i386 libgl1-mesa-glx:i386 libgl1-mesa-dev g++-multilib tofrodos python-markdown libxml2-utils xsltproc zlib1g-dev:i386 gawk libssl-dev u-boot-tools:i386 mingw32
sudo apt install bc u-boot-tools kmod cpio liblzo2-2 busybox rsync
```

## 3）、在docker中编译：

```bash
# 解压文件：
mkdir test01
cd test01
tar -xvf ../LinuxSDK-v1.4.tar.gz
tar -xvf ../dl.tar.gz -C T113-i_v1.0/buildroot/buildroot-201902
# 编译：
cd T113-i_v1.0
source ./build/envsetup.sh
./build.sh
# 生成linux系统镜像：
./build.sh pack

# 编译出的镜像位置：
ls out/t113_i/tlt113-evm-nand/longan/
ls out/t113_i_linux_tlt113-evm-nand_uart0.img
ls out/t113_i_linux_tlt113-evm-nand-sdboot_uart0.img
```

- 单独编译部分组件：

```bash
# SPL和u-boot：
./build.sh bootloader
# linux内核：
./build.sh kernel
# 文件系统：
./build.sh buildroot_rootfs

# 编译完后打包：
./build.sh pack
```

### 3.1）、单独编译u-boot环境变量文件env.fex

```bash
# 修改文件：
T113-i_v1.0/device/config/chips/t113_i/configs/tlt113-evm-nand/longan/env.cfg
# 打包时会编译env.fex文件：
./build.sh pack
# 验证：
head -c 1000 out/pack_out/env.fex
# 烧写env.fex(sd卡启动):
dd if=env.fex of=/dev/mmcblk0p2
# 重启：
reboot
```

### 3.2）、单独编译u-boot：

```bash
# 编译：
./build.sh brandy
# 打包：
./build.sh pack
# 镜像文件：包含u-boot、设备树、sys_config配置
ls -lh out/pack_out/boot_package.fex

dd if=boot_package.fex of=/dev/mmcblk0p1
reboot
```

## 4）、刷写到开发板中：

```bash
```

# 2、sd卡启动时分区信息：

```bash
# 分区大小(8G卡)：
Device           Start      End  Sectors  Size Type
/dev/mmcblk0p1   43008    53247    10240    5M Microsoft basic data
/dev/mmcblk0p2   53248    55295     2048    1M Microsoft basic data
/dev/mmcblk0p3   55296    57343     2048    1M Microsoft basic data
/dev/mmcblk0p4   57344    98303    40960   20M Microsoft basic data
/dev/mmcblk0p5   98304  2195455  2097152    1G Microsoft basic data
/dev/mmcblk0p6 2195456  2197503     2048    1M Microsoft basic data
/dev/mmcblk0p7 2197504  2199551     2048    1M Microsoft basic data
/dev/mmcblk0p8 2199552  2330623   131072   64M Microsoft basic data
/dev/mmcblk0p9 2330624 15120383 12789760  6.1G Microsoft basic data

/dev/mmcblk0p1: bootlogo等资源
/dev/mmcblk0p2: u-boot环境变量env.fex
/dev/mmcblk0p3: u-boot环境变量env.fex
/dev/mmcblk0p4: 内核镜像boot.fex
/dev/mmcblk0p5: 文件系统镜像rootfs.fex
/dev/mmcblk0p6: dsp镜像dfs0.fex
/dev/mmcblk0p7: 暂未使用
/dev/mmcblk0p8: 用户数据分区
/dev/mmcblk0p9: sd卡剩余空间分区
```

