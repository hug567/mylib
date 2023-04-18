# 1、入门：

```bash
sudo apt-get install gawk wget git-core diffstat unzip texinfo gcc-multilib \
     build-essential chrpath socat libsdl1.2-dev xterm

# 在线编译，需VPN
git clone git://git.yoctoproject.org/poky
git clone https://git.yoctoproject.org/poky
git clone https://github.com/yoctoproject/poky.git

cd poky
git checkout tags/yocto-4.0 -b yocto-4.0

source oe-init-build-env
bitbake core-image-minimal
# 完整版镜像
bitbake core-image-full-cmdline

# yocto使用的kernel代码
git clone https://git.yoctoproject.org/linux-yocto
git clone https://git.yoctoproject.org/yocto-kernel-cache

# 修改代码后编译kernel
./tmp/work/qemuarm64-poky-linux/linux-yocto/5.15.32+gitAUTOINC+meta_machine-r0/temp/run.do_compile
```

# 1）、需下载的包：

```bash
cd downloads
wget http://downloads.yoctoproject.org/releases/uninative/3.6/x86_64-nativesdk-libc-3.6.tar.xz

# 尝试是否可以不联网编译yocto
BB_NO_NETWORK
```

## 2）、源码位置：

```bash
# kernel：
tmp/work-shared/qemuarm64/kernel-source
git://git.yoctoproject.org/linux-yocto.git
git clone https://git.yoctoproject.org/linux-yocto
```

# 2、bitbake：

## 1）、基本用法：

```bash
bitbake <target>                             # 执行指定target的所有任务
bitbake -c <task> <target>                   # 执行指定target的指定任务
bitbake -c do_configure <target>             # 执行指定target的do_configure任务
bitbake -c clean <target>                    # 清除指定target的所有输出文件
bitbake -c cleansstate <target>              # 清除指定target的所有输出文件和共享状态缓存
bitbake -c cleanall <target>                 # 清除指定target的所有输出文件、共享状态缓存和下载的源文件
bitbake -c listtasks <target>                # 显示指定target的可执行任务
bitbake -s                                   # 显示所有可执行的包
bitbake -e <target>                          # 显示指定target当前执行环境
bitbake -g <target>                          # 显示指定任务的所有依赖
bitbake -b <xx.bb>                           # 直接执行指定bb文件
bitbake -v <target>                          # 打印一些调试信息
bitbake -vDDD <target>                       # 打印一些调试信息，可以跟多个D

# 修改tmp/work-shared/qemuarm64/kernel-source中的代码后重新编译linux
bitbake -C compile linux-yocto               # 推荐使用
bitbake -f -c compile linux-yocto
```

## 2）、创建layer：

```bash
# 创建layer
cd poky
source oe-init-build-env
cd ..
bitbake-layers create-layer meta-qemu

# 添加layer
cd build
bitbake-layers add-layer ../meta-qemu

# 查看使能的layer
bitbake-layers show-layers
```

# 3、recipe：

## 1）、打印：

```bash
# 匿名函数打印调试信息
python() {
    bb.note("[hx-debug] hello world")  # 使用空格缩进
    bb.plain("[hx-debug] xxx")
    bb.note("[hx-debug] PN = %s" % d.getVar('PN'))
    bb.warn("[hx-debug] PN = %s" % d.getVar('PN'))  # warn级别打印
    bb.error("[hx-debug] xxx")
    
    # 只能打印一行时：
    bb.note("\n[hx-debug]:\n",
        "KERNEL_DEBUG_OPTIONS = %s" % d.getVar("KERNEL_DEBUG_OPTIONS"), "\n",
        "KBRANCH = %s" % d.getVar("KBRANCH"), "\n",
    )
}

# 在.bbclass文件函数中打印变量，需加大括号
bbnote "[hx-debug] S = ${S}"
```

## 2）、receipe语法：

```bash
# 从本地或者github下载代码
SRC_URI = "file://${TOPDIR}/../packages/netplan_0.101.tar.gz \
           git://github.com/canonical/netplan.git;protocol=https;branch=main \
          "
# github下载代码对应的commit id
SRCREV = "3e522b7255310bdecca6c781137741dfc4abc021"

# 从本地拉取git仓库，修改的代码需提交commit
SRC_URI = "git:///home/hx/repo/all-repos/mazu;protocol=file" # 默认是master分支
SRC_URI = "git:///home/hx/repo/all-repos/mazu;protocol=file;branch=xxx"
SRCREV = "${AUTOREV}"
PV = "1.0"

# 从本地拉取代码目录，修改的代码不需要提交commit
LOCAL_REPO="/home/hx/repo/all-repos/mazu"
SRC_URI = "file://${LOCAL_REPO};protocol=file"
S = "${WORKDIR}/${LOCAL_REPO}"
```

## 3）、常见变量：

```bash
# 常用变量
libdir       = /usr/lib
includedir   = /usr/include
base_libdir  = /lib
docdir       = /usr/share/doc
datadir      = /usr/share
sysconfdir   = /etc
base_bindir  = /bin
base_sbindir = /sbin
bindir       = /usr/bin
mandir       = /usr/share/man

WORKDIR = .../netplan/0.101-r0
S =
B =
D =
SDK_DIR = None
DEPLOY_DIR = .../build/tmp/deploy
SYSROOT_DESTDIR = .../netplan/0.101-r0/sysroot-destdir
STAGING_DIR = .../build/tmp/sysroots
STAGING_DIR_NATIVE = .../netplan/0.101-r0/recipe-sysroot-native
STAGING_DIR_TARGET = .../netplan/0.101-r0/recipe-sysroot
STAGING_INCDIR = .../netplan/0.101-r0/recipe-sysroot/usr/include
STAGING_LIBDIR = .../netplan/0.101-r0/recipe-sysroot/usr/lib
TOPDIR = .../poky/build-aarch64
TMPDIR = 
DL_DIR ?= "${BSPDIR}/downloads"    # local.conf
```

## 4）、相关目录：

```bash
# do_fetch git clone后存储的位置：
build/downloads/git2/disk.sda.code.linux-qemu.poky.build-aarch64.......linux-yocto

# 任务执行顺序：log.task_order
tmp/work/qemuarm64-poky-linux/linux-yocto/5.15.32+gitAUTOINC+meta_machine-r0/temp/log.task_order
```

# 4、sysroot：

- recipe-sysroot：目标架构sysroot
- recipr-sysroot：host架构sysroot
- 安装：do_install时，将文件安装到${D}指定的目录中(一般是image目录)；
- 填充：do_populate_sysroot时，将安装到${D}中的内容，填充到sysroot目录；
- SYSROOT_DIRS：要填充到sysroot中的目录列表；

- do_prepare_recipe_sysroot与do_populate_sysroot是staging.bbclass类中关键任务，用于共享配方之间成果物；${SYSROOT_DESTDIR}目录最终会放置到共享区（默认为build/tmp/sysroots-components）暂存，其他配方构建时就可以从共享区拷贝；
- ${D}目录下自动拷贝的目录由三个变量指定，分别为SYSROOT_DIRS（目标设备需要保存的子目录）、SYSROOT_DIRS_BLACKLIST（目标设备不需要保存的子目录）、SYSROOT_DIRS_NATIVE（本机设备需要保存的目录）；