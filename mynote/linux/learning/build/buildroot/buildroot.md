# 1、编译buildroot主线：

## 1）、在线编译：

```bash
git clone https://git.busybox.net/buildroot
git clone https://github.com/buildroot/buildroot.git
cd buildroot
# 图形化配置：
make menuconfig
......

# 使用默认配置：
make qemu_arm_vexpress_defconfig
# 编译：
make -j12

# 使用qemu运行编译成功的镜像：
qemu-system-arm \
	-M vexpress-a9 -smp 2 -m 1024M \
	-kernel output/images/zImage \
	-append "root=/dev/mmcblk0 console=ttyAMA0 loglevel=8" \
	-dtb output/images/vexpress-v2p-ca9.dtb \
	-drive if=sd,format=raw,file=output/images/rootfs.ext2 \
	-nographic

# 使用buildroot编译出的qemu运行linux镜像：
output/build/host-qemu-9.2.0/build/qemu-system-arm \
        -M vexpress-a9 -smp 2 -m 1024M \
        -kernel output/images/zImage \
        -append "root=/dev/mmcblk0 console=ttyAMA0 loglevel=8" \
        -dtb output/images/vexpress-v2p-ca9.dtb \
        -drive if=sd,format=raw,file=output/images/rootfs.ext2 \
        -nographic
```

## 2）、离线编译：

```bash
# 在线编译成功后，将下载的dl目录复制到新代码目录中，即可离线编译：
cd buildroot
cp -r .../dl ./
make qemu_arm_vexpress_defconfig
make -j12
```

# 2、添加recipe：

```bash
# 创建包目录：
cd package
mkdir mypackage
cd mypackage
# 创建配置文件：
touch Config.in mypackage.hash mypackage.mk

# 设置配置文件：
vim Config.in
#--------------------------------------------------------------#
config BR2_PACKAGE_MYPACKAGE
        bool "mypackage"
        depends on BR2_TOOLCHAIN_GCC
        help
          mypackage
#--------------------------------------------------------------#

# 设置哈希文件：
vim mypackage.hash
#--------------------------------------------------------------#
# 忽略哈希检查时可不写
#--------------------------------------------------------------#

# 设置编译文件：
vim mypackage.mk
#--------------------------------------------------------------#
# 通过git从本地目录拉取代码，分支为main
MYPACKAGE_VERSION = main
MYPACKAGE_SITE = $(TOPDIR)/../mypackage
MYPACKAGE_SITE_METHOD = git
# 忽略哈希检查
BR_NO_CHECK_HASH_FOR += $(MYPACKAGE_SOURCE)
# 使用cmake编译源码
$(eval $(cmake-package))
#--------------------------------------------------------------#

# 单独编译recipe：
make mypackage
```

- 清理下载的文件：

```bash
rm -rf dl/mypackage
```

- 清理编译目录：

```bash
rm -rf output/build/mypackage-main
```

