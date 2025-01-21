# 使用最新版本yocto

## 1、yocto 5.0：

- 2025-01-04

- 编译arm版sdk：

```bash
# 下载源码：
git clone https://git.yoctoproject.org/poky
cd poky
git checkout yocto-5.0

# 默认架构改为arm
vim meta-poky/conf/templates/default/local.conf.sample
#-----------------------------------------------#
MACHINE ?= "qemuarm"
#-----------------------------------------------#

# 编译sdk
source oe-init-build-env
bitbake core-image-minimal -c populate_sdk
```

