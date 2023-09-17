## 1、下载busybox：

```shell
git clone https://git.busybox.net/busybox
git clone https://github.com/mirror/busybox.git
git clone https://gitee.com/mirrors/busyboxsource.git

git checkout 1_27_stable
make clean; make mrproper
```



## 2、编译arm版本busybox：



## 3、编译aarch64版本busybox：

### 1）、编译静态链接busybox：

```shell
make menuconfig

Busybox Settings  --->
    [*] Build BusyBox as a static binary (no shared libs)

make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- all -j4

make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- install

ls _install
```

### 2）、编译动态链接busybox：