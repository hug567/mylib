## 1、基本命令
----
```c
-cpu         //
-M vexpress-a9                              //模拟vexpress-a9单板
-M help                                     //获取支持的所有单板
-m 512M                                     //内存512M
-kernel ./arch/arm/boot/zImage              //内核镜像路径
-nographic                                  //不使用图形化界面，只使用串口
-append "console=ttyAMA0"                   //串口设备是哪个tty
```
## 2、qemu支持网络
----
```c
/* 首先内核中支持tap/tuns设备：CONFIG_TUN */
Device Drivers  ---> 
     Networking support  --->
        [M] Universal TUN/TAP device driver support
/* Kconfig位置: CONFIG_TUN */
linux-4.15/drivers/net/Kconfig

```

## 3、qemu help

```c
qemu-system-arm -machine help                           //查看支持的开发板
qemu-system-arm -machine virt -cpu help                 //查看开发板支持的CPU
qemu-system-arm -machine vexpress-a9 -nic model=help    //查看支持的nic模式
qemu-system-x86_64 -device help                         //查看支持的设备模块
```

```c
/* u-boot通过tftp下载镜像： */
sudo apt install tftp-hpa tftpd-hpa xinetd              //安装tftp
cd ~; mkdir tftpboot; sudo chmod 777 tftpboot           //创建tftp根目录
sudo vim /etc/default/tftpd-hpa                         //编辑配置文件
/* ------------------------------------------------------------ */
# /etc/default/tftpd-hpa

TFTP_USERNAME="tftp"
TFTP_DIRECTORY="/home/ubuntu/tftpboot"
TFTP_ADDRESS="0.0.0.0:69"
#TFTP_OPTIONS="--secure"
TFTP_OPTIONS="-l -c -s"
/* ------------------------------------------------------------ */
sudo service tftpd-hpa restart                          //重启tftp

/* 测试连接： */
cd ~
tftp localhost                                          //连接至本机
tftp>get test1.txt                                      //获取文件
tftp>put test2.txt                                      //上传文件
tftp>q                                                  //推出连接

/* 创建虚拟网口： */
```

## 4、编译qemu：

```shell
# 下载源码
git clone https://gitee.com/mirrors/qemu.git
git clone https://gitlab.com/qemu-project/qemu.git

# 环境准备
sudo apt install ninja-build libglib2.0-dev libpixman-1-dev
# 查看glibc版本
ldd --version
ls -l /lib/x86_64-linux-gnu/libc*  # /lib/x86_64-linux-gnu/libc.so.6 -> libc-2.27.so

# 编译
mkdir build-arm
cd build-arm
../configure  --target-list=arm-softmmu    #qemu-system-arm
make

```

