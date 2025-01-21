# 1、编译buildroot主线：

```bash
git clone https://git.busybox.net/buildroot
cd buildroot
# 图形化配置：
make menuconfig
......

# 编译：
make qemu_arm_vexpress_defconfig
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

#--------------------------------------------------------------#
# 设置编译文件：
vim mypackage.mk
#--------------------------------------------------------------#

#--------------------------------------------------------------#

# 单独编译recipe：
make mypackage
```

