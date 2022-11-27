## 1、配置IP：

### 1）、配置静态ip：

```shell
# 查看网卡是否连接网线
ethtool eno1                                                # Link detected: yes/no

# 配置dns:
sudo vi /etc/resolv.conf
#--------------------------------------------------------------------#
nameserver 192.168.1.1
#--------------------------------------------------------------------#

# 查看网络守护进程：
which netplan
ps aux | grep NetworkManager                                # 查看是否启动了服务
ps aux | grep systemd-networkd                              # 查看是否启动了服务

# 安装网络管理工具：
sudo apt install netplan.io network-manager net-tools

# netplan配置静态ip:
#--------------------------------------------------------------------#
# 有线网卡设置：/etc/netplan/01-network-manager-all.yaml
network:
  version: 2
  renderer: NetworkManager                                  # NetworkManager
  renderer: networkd                                        # systemd-networkd
  ethernets:
    ens33:
      dhcp4: false
      addresses:
      - 192.168.1.28/24
      gateway4: 192.168.1.1
      nameservers:
        addresses:
        - 192.168.1.1
#--------------------------------------------------------------------#
# wifi设置：/etc/netplan/00-installer-config-wifi.yaml
network:
  version: 2
  wifis:
    wlx82771688de0a:
      dhcp4: false
      access-points:
        '1201':
          password: '1139321201'
      addresses:
      - 192.168.1.27/24
      gateway4: 192.168.1.1
      nameservers:
        addresses:
        - 192.168.1.1
#--------------------------------------------------------------------#
sudo netplan apply                                          # 应用配置信息
sudo netplan --debug apply                                  # 打印调试信息
sudo netplan generate                                       # 生成网络守护程序配置信息

# DNS：
systemd-resolve --status                                    # 查看当前使用的dns

# 配置源镜像：
sudo vi /etc/apt/sources.list
sudo apt update
```

### 2）、iproute2配置ip：

```shell
# 列出路由
ip route
ip route show
ip route list
ip route show table all

sudo ip link set dev eno1 up/down                           # 启动/关闭网卡
sudo ip addr add dev eno1 192.168.1.26/24                   # 设置ip
sudo ip addr del dev eno1 192.168.1.26/24                   # 删除ip
sudo ip route add default via 192.168.1.1 dev eno1          # 添加路由

ip link help                                                # 查看命令帮助
sudo ip link set dev ens33 address 11:22:33:44:55:66        # 设置MAC地址
sudo ip link set dev ens33 broadcast 11:22:33:44:55:66      # 设置广播地址
sudo ip link set dev ens33 mtu 1500                         # 设置MTU
```

### 3）、net-tools配置ip：

```shell
sudo apt install net-tools                                  # 安装net-tools

ifconfig -a
sudo ifconfig eth0 up                                       # 启动网卡
sudo ifconfig eth0 192.168.1.27 netmask 255.255.255.0       # 设置ip
sudo route add default gw 192.168.1.1                       # 设置网关
sudo ifconfig ens33 hw ether 11:22:33:44:55:66              # 设置MAC地址
```

### 4）、NetworkManager：

```shell
# 启动/停止NetworkManager
sudo systemctl start NetworkManager                         # 启动
sudo systemctl stop NetworkManager                          # 关闭
sudo systemctl enable NetworkManger                         # 使能开启自启动
sudo systemctl disable NetworkManager                       # 禁止开机自启动

# nmcli:
nmcli d                                                     # 显示网卡设备
nmcli c                                                     # 显示网络连接
nmcli -s                                                    # 显示网卡信息
nmcli device show                                           # 显示已生效的网卡配置信息

# 配置文件：
/run/NetworkManager/system-connections/netplan-ens33
```

### 5）、systemd-networkd：

```shell
# 启动/停止systemd-networkd
sudo systemctl start systemd-networkd                       # 启动
sudo systemctl stop systemd-networkd                        # 停止
sudo systemctl enable systemd-networkd                      # 使能开机自启动
sudo systemctl disable systemd-networkd                     # 禁止开机自启动

# 配置文件所在目录：
/usr/lib/systemd/network                                    # 最低优先级
/run/systemd/network                                        # 中等优先级
/etc/systemd/network                                        # 最高优先级

# 配置文件：
*.network                                                   # 网络设备配置文件
*.netdev                                                    # 虚拟网络设备配置文件

# 例：/run/systemd/network/10-netplan-ens33.network
[Match]
Name=ens33

[Network]
LinkLocalAddressing=ipv6
Address=192.168.58.27/24
Gateway=192.168.58.2
DNS=192.168.58.2
```

## 2、安装常用软件：

```shell
sudo apt install vim-gnome openssh-client openssh-server
sudo apt install git tmux zsh gcc g++ cmake python python3 u-boot-tools tig net-tools
sudo apt install htop ntp ntpdate
```

#### 1)、模糊搜索fzf：

```shell
cd ~
git clone https://hub.fastgit.org/junegunn/fzf.git
mv fzf .fzf
cd .fzf/bin
# 最新版本可从install文件中获取：
wget https://github.com/junegunn/fzf/releases/download/0.28.0/fzf-0.28.0-linux_amd64.tar.gz
tar
cd ..
./install

Ctrl + R                                     # 搜索历史命令
fzf                                          # 搜索当前目录下文件
vim $(fzf)                                   # vim配合fzf搜索并打开文件
cd $(find * -type d | fzf)                   # cd配合fzf搜索打开目录
git checkout $(git branch -r | fzf)          # git配合fzf切换分支
```

## 4、crontab：定时任务

```shell
crontab -e    # 编辑工作表
crontab -l    # 列出工作表中的任务
crontab -r    # 删除所有定时任务

# crontab命令：没一行是一条定时任务
分 时 日 月 周 命令

*    # 取值范围内的所有值
/    # 没隔一定时间
-    # 从a到b
,    # 散列数字

# 例：
0 * * * * echo "$(date) > /tmp/crontab.log"     # 没小时的第0分钟执行echo命令
```
