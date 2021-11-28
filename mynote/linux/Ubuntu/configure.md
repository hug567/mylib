## 1、配置源镜像：

```shell
sudo vi /etc/apt/sources.list

# Ubuntu 18.04 Desktop命令行配置ip:
sudo apt install netplan.io
sudo vim /etc/netplan/01-network-manager-all.yaml
#--------------------------------------------------------------------#
network:
  version: 2
  renderer: NetworkManager
  ethernets:
    ens33:
      dhcp4: no
      addresses: [192.168.1.28/24]
      gateway4: 192.168.1.1
      nameservers:
        addresses: [192.168.1.1]
#--------------------------------------------------------------------#
sudo netplan apply                              # 应用配置信息
sudo netplan --debug apply                      # 打印调试信息
sudo netplan generate                           # 生成网络守护程序配置信息

# netplan后端网络管理工具(renderer):
# 1)、NetworkManager
sudo systemctl start NetworkManager             # 启动NetworkManager
sudo systemctl stop NetworkManager              # 停止NetworkManager
sudo systemctl enable NetworkManger             # 开启自启动
sudo systemctl disable NetworkManager           # 禁用开机自启动

service NetworkManager status                   # 查看NetworkManager状态
service NetworkManager start                    # 启动NetworkManager
service NetworkManager stop                     # 关闭NetworkManager
chkconfig NetworkManager on                     # 开机启动
chkconfig NetworkManager off                    # 禁用开机启动

# 2）、Systemd-networkd
sudo systemctl enable systemd-networkd          # 设置开机启动

# nmcli:
nmcli d                                         # 显示网卡设备
nmcli c                                         # 显示网络连接
nmcli -s                                        # 显示网卡信息
nmcli device show                               # 显示网卡设备配置信息
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
wget https://github.com/junegunn/fzf/releases/download/0.28.0/fzf-0.28.0-linux_amd64.tar.gz
tar
cd ..
./install

# 搜索历史命令：
Ctrl + R

# 搜索当前目录下文件：
fzf
```

## 3、常用配置：

```shell
# 查看时区：
#   CST：中国标准时间
#   UTC：世界标准时间，UTC=CST-8
#   GMT：格林尼治标准时间
date
timedatectl status

# 修改时区：
sudo dpkg-reconfigure tzdata                  # 改为: "Asia/Shanghai"
# 或:
timedatectl set-timezone "Asia/Shanghai"

# 时间校准：
sudo apt install ntpdate
sudo ntpdate cn.ntp.org.cn
sudo ntpdate cn.pool.ntp.org
sudo ntpdate ntp.aliyun.com
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

