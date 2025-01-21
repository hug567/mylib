# 1、入门：

```bash
sudo apt-get install gawk wget git-core diffstat unzip texinfo gcc-multilib \
     build-essential chrpath socat libsdl1.2-dev xterm zstd liblz4-tool

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

## 1）、需下载的包：

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

## 3）、构建native sdk：

```bash
bitbake <image> -c populate_sdk
# 如：
bitbake core-image-minimal -c populate_sdk
```

# 2、recipe：

## 1）、打印：

### 1.1)、打印：

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

### 1.2)、poky 2.2.2：

```bash
# poky 2.2.2: meta-poky/conf/distro/poky.conf
bb.note("[hx-debug] S = %s" % d.getVar('S', True))
```

## 2）、receipe语法：

- recipe中的shell代码是用sh执行的，不是用bash执行，注意二者之间的语法区别：

```bash
# 从本地或者github下载代码
SRC_URI = "file://${TOPDIR}/../packages/netplan_0.101.tar.gz \
           git://github.com/canonical/netplan.git;protocol=https;branch=main \
          "
# github下载代码对应的commit id
SRCREV = "3e522b7255310bdecca6c781137741dfc4abc021"

# 从本地拉取git仓库，修改的代码需提交commit
SRC_URI = "git:///home/hx/repo/all-repos/mytest;protocol=file" # 默认分支是master
SRC_URI = "git:///home/hx/repo/all-repos/mytest;protocol=file;branch=xxx" # 指定分支
SRC_URI = "git:///home/hx/repo/all-repos/mytest;protocol=file;usehead=1" # 不checkout，使用当前HEAD
SRCREV = "${AUTOREV}"
PV = "1.0"

# 从本地拉取代码目录，修改的代码不需要提交commit
LOCAL_REPO="/home/hx/repo/all-repos/mytest"
SRC_URI = "file://${LOCAL_REPO};protocol=file"
S = "${WORKDIR}/${LOCAL_REPO}"
# 在SRC_URI头部添加值：
SRC_URI_prepend = "file://file.tar.gz "
# 在SRC_URI尾部部添加值：
SRC_URI += " file://file.tar.gz"
SRC_URI_append = " file://file.tar.gz"
# 去除SRC_URI中的一个值：
SRC_URI_remove = "file://file.tar.gz"

# 为当前recipe提供标识，其他recipe可在DEPENDS中指定该标识，注明依赖关系
PROVIDES = "virtual/bootloader"

# 不执行do_rm_work
do_rm_work() {
    :
}
# 或
do_rm_work[noexec] = "1"
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
TOPDIR = .../poky/build
TMPDIR = .../poky/build/tmp
DL_DIR ?= "${BSPDIR}/downloads"    # local.conf
DEPLOY_DIR_IMAGE = .../build/tmp/deploy/images/plnx-zynq7
```

## 4）、相关目录：

```bash
# do_fetch git clone后存储的位置：
build/downloads/git2/disk.sda.code.linux-qemu.poky.build-aarch64.......linux-yocto

# 任务执行顺序：log.task_order
tmp/work/qemuarm64-poky-linux/linux-yocto/5.15.32+gitAUTOINC+meta_machine-r0/temp/log.task_order
```

## 5)、更新rootfs：

```bash
# 打包rootfs时删除文件，如在petalinux-user-image.bbappend中：
remove_alternative_files () {
    rm -rf ${IMAGE_ROOTFS}/usr/lib/opkg
}

ROOTFS_POSTPROCESS_COMMAND += "remove_alternative_files;"
```

## 6)、增加主机端工具：

- 在layer配置文件中增加HOSTTOOLS，如：

```bash
# 先在主机中安装相关工具：
sudo apt install python3-django expect

# meta/conf/bitbake.conf
# project-spec/meta-user/conf/petalinuxbsp.conf
HOSTTOOLS += "django-admin expect"

# hosttools所在目录
ls build/tmp/hosttools
```

## 7)、recipe间依赖：

```bash
# newrecipe.bb完全依赖oldrecipe.bb，可在newrecipe.bb文件中加上：
RDEPENDS_${PN} += "oldrecipe"
```

## 8)、插入自定义任务：

```bash
# 在recipe的各任务间插入自定义任务，如：
addtask my_deploy after do_install
addtask do_deploy before do_build after do_compile
```

## 9)、recipe中读取环境变量：

```bash
# yocto默认会过滤环境变量，若需要保留特定的环境变量，需在BB_ENV_EXTRAWHITE中声明：
# 声明后就可以在recipe中获取到指定的环境变量的值了：
export MYNEWWNVVAR="hello"
export BB_ENV_EXTRAWHITE="$BB_ENV_EXTRAWHITE MYNEWENVVAR"

# 例：
do_configure() {
    echo "MYNEWWNVVAR = ${MYNEWWNVVAR}"
}
```

## 10)、变体：

```bash
# recipe中根据MACHINE的不同，变量赋予不通的值：
MYVAR="hello"
MYVAR_plnx-zynq7="world"
# MACHINE="plnx-zynq7"时，MYVAR="world"
# 其他时候，MYVAR="hello"
# MACHINE可通过环境变量设置，待验证？
```

## 11)、强制构建：

```bash
# 不cache产物：
BB_DONT_CACHE="1"
# 每次构建时均强制执行指定任务，如：
do_configure[nostamp] = "1"
```

# 3、sysroot：

- recipe-sysroot：目标架构sysroot
- recipe-sysroot-native：host架构sysroot
- 安装：do_install时，将文件安装到${D}指定的目录中(一般是image目录)；
- 填充：do_populate_sysroot时，将安装到${D}中的内容，填充到sysroot目录；
- SYSROOT_DIRS：要填充到sysroot中的目录列表；

- do_prepare_recipe_sysroot与do_populate_sysroot是staging.bbclass类中关键任务，用于共享配方之间成果物；${SYSROOT_DESTDIR}目录最终会放置到共享区（默认为build/tmp/sysroots-components）暂存，其他配方构建时就可以从共享区拷贝；
- ${D}目录下自动拷贝的目录由三个变量指定，分别为SYSROOT_DIRS（目标设备需要保存的子目录）、SYSROOT_DIRS_BLACKLIST（目标设备不需要保存的子目录）、SYSROOT_DIRS_NATIVE（本机设备需要保存的目录）；
