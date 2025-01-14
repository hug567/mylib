# 1、源码下载：

```bash
git clone https://git.yoctoproject.org/poky
# 学习yocto 2.2.2
cd poky
git checkout yocto-2.2.2
```

# 2、poky主线编译linux：

- 2024-06-05: https://docs.yoctoproject.org/brief-yoctoprojectqs/index.html

```bash
sudo apt install gawk wget git diffstat unzip texinfo gcc build-essential chrpath socat cpio python3 python3-pip python3-pexpect xz-utils debianutils iputils-ping python3-git python3-jinja2 python3-subunit zstd liblz4-tool file locales libacl1
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



