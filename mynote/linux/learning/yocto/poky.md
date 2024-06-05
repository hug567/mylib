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
cd poky
git clone https://github.com/kraj/meta-altera.git
```

