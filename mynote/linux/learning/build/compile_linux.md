# 1、Host配置：

- 交叉工具链：

```bash
sudo apt install gcc qemu libncurses5-dev openssl libssl-dev build-essential pkg-config libc6-dev bison flex libelf-dev
```

# 2、编译arm：

```bash
make -C ../ O=`pwd` ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- vexpress_defconfig
```

# 3、编译aarch64：

```bash

```

