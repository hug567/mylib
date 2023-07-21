# 1、基本命令
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

# 2、qemu支持网络

----
```c
/* 首先内核中支持tap/tuns设备：CONFIG_TUN */
Device Drivers  ---> 
     Networking support  --->
        [M] Universal TUN/TAP device driver support
/* Kconfig位置: CONFIG_TUN */
linux-4.15/drivers/net/Kconfig

```

# 3、qemu help

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
tftp>q                                                  //退出连接

/* 创建虚拟网口： */
```

# 4、编译qemu：

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
../configure --target-list=arm-softmmu,aarch64-softmmu
make -j
```

# 5、添加网桥：

```bash
sudo apt install bridge-utils

# netplan设置网桥
network:
  version: 2
  renderer: networkd
  ethernets:
    enp1s0:
      dhcp4: no
  bridges:
    br0:
      dhcp4: yes
      interfaces:
         - enp1s0

# 查看网桥
brctl show
# 创建网桥
sudo brctl addbr br0
# 为网桥添加接口
sudo brctl addif br0 tap0
sudo brctl addif br0 enp0s31f6
# 删除网桥
sudo brctl delbr br0
# 启动网桥stp (Spanning Tree Protocol, 生成树协议,防止网桥网络中形成环路)
sudo brctl stp br0 on
# 关闭网桥stp
sudo brctl stp br0 off
```

# 6、iptables实现qemu访问大网：

## 1）、host配置：
```bash
# 设置host tap0 ip：
sudo ifconfig tap0 192.168.0.1 netmask 255.255.255.0
# 设置host端口转发：
sudo iptables -t nat -A POSTROUTING -s 192.168.0.101 -j SNAT --to 10.110.192.42
# 永久保存配置：
sudo apt install iptables-persistent
sudo netfilter-persitent save
```
## 2）、qemu配置
```bash
# 设置qemu镜像ip：
ifconfig eth0 192.168.0.101 netmask 255.255.255.0
# 确认qemu路由：
route
#----- default: 192.168.0.1 ------------------------------------------------#
Kernel IP routing table
Destination     Gateway         Genmask         Flags Metric Ref    Use Iface
default         192.168.0.1     0.0.0.0         UG    0      0        0 eth0
192.168.0.0     0.0.0.0         255.255.255.0   U     0      0        0 eth0
#---------------------------------------------------------------------------#
# qemu镜像设置dns：
vi /etc/resolv.conf
#---------------------------------------------------------------------------#
nameserver 172.20.4.31    # echo "nameserver 172.20.4.31" > /etc/resolv.conf
nameserver 10.110.0.15    # echo "nameserver 10.110.0.15" >> /etc/resolv.conf
#---------------------------------------------------------------------------#
# 验证网络：
ping baidu.com -c 4
```

