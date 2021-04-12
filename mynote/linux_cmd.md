## 1、基本命令

```c
scp
    scp file user@192.168.1.1:~                         //上传本地文件至远程主机
    scp -r user@192.168.1.1:~/file ./                   //下载远程主机文件至本地
ln
    ln -s <> <>    //创建软连接
```


## 2、安装卸载

```c
apt
    apt-cache search <package>                           //搜索软件
    sudo apt install <package>                           //安装软件
    sudo apt remove <package>                            //删除软件及
    sudo apt --purge remove <package>                    //删除软件及其配置文件
dpkg
    dpkg -l                                              //查看所有已安装软件
    dpkg -l | grep -i <name>                             //查看指定相关软件
```

## 3、查找

```c
find                                                     //查找文件
    find . -name "file.c"                                //在当前目录及子目录中查找指定文件
grep
    grep -nr "string" .                                  //查找文本
```

## 4、win10通过ftp与Linux传输文件：

```c
sudo vim /etc/vsftpd.conf                                //更改ftp配置
/* 取消“#write_enable=YES”的注释，:wq */
service vsftpd restart                                   //重启ftp服务
/* win10命令行中： */
ftp <ip>                                                 //与Linux链接
get <file>                                               //从Linux下载文件
put <file>                                               //上传文件至Linux
?                                                        //查看ftp支持的命
```

## 5、压缩解压：

```c
rar
    sudo apt install rar                                 //更改ftp配置
    rar x package.rar                                    //解压rar文件
unzip
    unzip package.zip                                    //解压zip文件
```

## 6、ssh连接vm中的linux：

```c
/* 虚拟机Linux： */
sudo apt install openssh-server                          //安装ssh服务端
sudo /etc/init.d/ssh start                               //启动sshd
ps -e | grep ssh                                         //查看sshd是否启动
ip a                                                     //查看虚拟卡ip
/* 主机win10中gitbash: */
ssh hx@192.168.40.128                                    //连接虚拟机中Linux
```

## 7、网络相关：

```c
sudo dhclient -r                                        //释放ip
sudo dhclient                                           //自动获取ip

/* Ubuntu局域网设置固定ip： */
Address: 192.168.1.27                //需在路由器DHCP范围之外
Netmask: 255.255.255.0               //与自动获取时相同
Gateway: 192.168.1.1                 //与自动获取时相同
DNS: 192.168.1.1                     //与自动获取时相同

IP地址 = 网段地址 + 主机地址(Host ID)
子网掩码(Netmask)：将ip地址划分为网络地址和主机地址两部分
网络地址 = IP地址 & 子网掩码
广播地址(Broadcast) = IP地址 | (!子网掩码)，Host ID全为1的地址为广播地址，发送给广播地址的包将被转发给同一网段中的所有主机
网段：网络地址相同的IP地址属于同一网段，即同一子网
网关(Gateway)：不在同一网段的设备需要通过网关才能通讯，主机发送的网路包目的主机不在当前子网中时，将把数据包转发给网关，由网关转发给目的主机所在子网的网关。
路由：
DNS：域名系统

NAT(网络地址转换 )：
```