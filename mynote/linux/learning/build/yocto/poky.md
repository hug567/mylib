# 1、源码下载：

```bash
git clone https://git.yoctoproject.org/poky
# 学习yocto 2.2.2
cd poky
git checkout yocto-2.2.2
```

# 2、编译：

## 1）、poky主线编译linux：

- 2024-06-05: https://docs.yoctoproject.org/brief-yoctoprojectqs/index.html

```bash
sudo apt install gawk wget git diffstat unzip texinfo gcc build-essential chrpath socat cpio python3 python3-pip python3-pexpect xz-utils debianutils iputils-ping python3-git python3-jinja2 python3-subunit zstd liblz4-tool file locales libacl1 xz-utils
sudo locale-gen en_US.UTF-8

git clone https://git.yoctoproject.org/poky
cd poky
source oe-init-build-env
bitbake core-image-minimal
```

- poky编译时下载代码使用代理：

```bash
export http_proxy='http://127.0.0.1:7890/'
export https_proxy='https://127.0.0.1:7890/'
export ftp_proxy='http://127.0.0.1:7890/'
export ALL_PROXY='socks://127.0.0.1:7890/'
export all_proxy='socks://127.0.0.1:7890/'
export no_proxy='127.0.0.1'
```

## 2）、编译sdk：

```bash
bitbake core-image-minimal -c populate_sdk
```

## 3）、本地编译：

```bash
# 在layer的配置文件layer.conf中添加：
BB_NO_NETWORK = "1"
# 初始化编译环境：
source oe-init-build-env
# 复制已下载的源码文件到build目录：
cp -r .../downloads ./
# 编译平台：
bitbake core-image-minimal
```

# 3、poky添加layer：

```bash
# 下载开源layer：
cd poky
git clone https://github.com/kraj/meta-altera.git
```

# 4、常用设置：

## 1）、默认加载指定layer：

```bash
# 修改文件：meta-poky/conf/templates/default/bblayers.conf.sample
#----------------------------------------------------#
# 新增自定义layer: meta-qemu
BBLAYERS ?= " \
  ##OEROOT##/meta \
  ##OEROOT##/meta-poky \
  ##OEROOT##/meta-yocto-bsp \
  ##OEROOT##/meta-qemu \
  "
#----------------------------------------------------#
```

## 2）、设置默认平台为arm：

```bash
# 修改文件：meta-poky/conf/templates/default/local.conf.sample
#----------------------------------------------------#
MACHINE ?= "qemuarm"
#----------------------------------------------------#
```

# 5、使用本地源码：

## 1）、查看源码：

```bash
# 在recipe文件中添加匿名python函数发送使用的源码地址，如：
python() {
    bb.note("[hx-debug] SRC_URI: %s" % d.getVar('SRC_URI'))
}
# 然后执行命令打印SRC_URI：
bitbake libidn2-native -c do_recipe_qa
```

## 2）、源码为压缩包文件：

```bash
# 通过浏览器等下载压缩包文件，然后拷贝到build/downloads目录中，如：
cp ../../downloads/libidn2-2.3.7.tar.gz downloads
# 验证源码拉取：
bitbake libidn2-native -c do_fetch
# 然后重新编译recipe：
bitbake libidn2-native
```

## 3）、源码为git仓库：

```bash
# 先按1)获取到源码的路径，再执行reiepo的do_fetch任务：
bitbake e2fsprogs-native -c do_fetch
# 进入git仓库缓存目录：
cd downloas/git2
# 查看目标仓库被缓存的目录名称，如：git.kernel.org.pub.scm.fs.ext2.e2fsprogs.git
ls | grep e2fsprogs
# 通过其他途径下载仓库，并复制到downloads/git2目录中：
git clone git://git.kernel.org/pub/scm/fs/ext2/e2fsprogs.git
# 如果使用的分支不是默认分支，还需要切换到使用的目标分支：
cd e2fsprogs
git checkout xxx
# 对仓库重命名：
mv e2fsprogs git.kernel.org.pub.scm.fs.ext2.e2fsprogs.git
# 重新从本地拉取源码：
bitbake e2fsprogs-native -c do_fetch
```

## 4）、 常见仓库国内镜像：

```bash
# glibc：
git clone https://mirrors.tuna.tsinghua.edu.cn/git/glibc.git
```

## 5）、配置uninative包：

### 5.1）、网上下载：

- yocto 5.0对应的包为：https://downloads.yoctoproject.org/releases/uninative/4.6/x86_64-nativesdk-libc-4.6.tar.xz

### 5.2）、本地构建：

```bash
# 本地编译：
bitbake uninative-tarball
```
### 5.3）、使用本地nativesdk文件：

```bash
# 将编译成功后文件复制到downloads/uninative目录：
cp tmp/deploy/sdk/x86_64-nativesdk-libc.tar.xz downloads/uninative
# 查看文件sha256值：
sha256sum downloads/uninative/x86_64-nativesdk-libc.tar.xz
# 在.../conf/layer.conf中添加配置：
ENABLE_UNINATIVE = "1"
UNINATIVE_URL ?= "file://${DL_DIR}/uninative/"
UNINATIVE_DLDIR ?= "${DL_DIR}/uninative/"
UNINATIVE_TARBALL ?= "x86_64-nativesdk-libc.tar.xz"
UNINATIVE_CHECKSUM[x86_64] ?= "970827f8d836cc749ad22d347459bceccf05c29623a5621ced72226dd3c295fc"
```

## 6、运行：

### 1）、qemu运行arm镜像：

```bash
cd tmp/deploy/images/qemuarm
# 登录用户名：root，无密码
qemu-system-arm \
    -drive id=disk0,file=core-image-minimal-qemuarm.rootfs.ext4,if=none,format=raw \
    -device virtio-blk-device,drive=disk0 \
    -machine virt,highmem=off \
    -cpu cortex-a15 \
    -smp 4 -m 256 -serial mon:stdio -nographic \
    -kernel zImage \
    -append 'root=/dev/vda rw  mem=256M swiotlb=0'
```
