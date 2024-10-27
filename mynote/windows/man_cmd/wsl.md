# 1、WSL运行docker：

- 安装wsl2：控制面板 -> 程序和功能 -> 启动或关闭Windows功能 -> 适用于Linux的Windows子系统 + 虚拟机平台 -> 确定

```bash
# 查看当前安全的linux发行版
wsl -l -v
# 关闭运行的linux(关闭虚拟机进程Vmmem)
wsl --shutdown
# 更新wsl
wsl --update
# 安装ubuntu
wsl --install -d <Ubuntu-18.04>
# 设置wsl2运行linux发行版
wsl --set-version <Ubuntu-18.04> 2
# 启动linux发行版
wsl -d <Ubuntu-18.04>
# 终止linux发行版
wsl -4 <Ubuntu-18.04>

# 若wsl卡住，以管理员身份运行powershell/cmd
netsh winsock reset  # 然后重启
```

- 安装docker：

```bash
# 添加docker源
sudo vim /etc/apt/source.list
#-ubuntu 18.04-----------------------------------------#
deb     https://mirrors.cloud.tencent.com/docker-ce/linux/ubuntu/ bionic stable
deb-src https://mirrors.cloud.tencent.com/docker-ce/linux/ubuntu/ bionic stable
#------------------------------------------------------#
curl -fsSL https://mirrors.cloud.tencent.com/docker-ce/linux/ubuntu/gpg | sudo apt-key add -
sudo apt-get update
# 安装docker-ce
apt-cache search docker-ce
sudo apt-get install docker-ce

# 启动docker
sudo /etc/init.d/docker start
# 重启docker
sudo /etc/init.d/docker restart
# 或
sudo service docker start/stop/restart
```

- 命令行安装wsl发行版：

```bash
# 安装或更新wsl
wsl --update
# 查看发行部
wsl --list --online
# 安装发行版
wsl --install --d Ubuntu-18.04
```

- 其他可用的apt源：

```bash
# ubuntu 18
deb     https://mirrors.cloud.tencent.com/ubuntu/ bionic           main universe restricted multiverse
deb     https://mirrors.cloud.tencent.com/ubuntu/ bionic-security  main universe restricted multiverse
deb     https://mirrors.cloud.tencent.com/ubuntu/ bionic-updates   main universe restricted multiverse
deb     https://mirrors.cloud.tencent.com/ubuntu/ bionic-backports main universe restricted multiverse
deb-src https://mirrors.cloud.tencent.com/ubuntu/ bionic           main universe restricted multiverse
deb-src https://mirrors.cloud.tencent.com/ubuntu/ bionic-security  main universe restricted multiverse
deb-src https://mirrors.cloud.tencent.com/ubuntu/ bionic-updates   main universe restricted multiverse
deb-src https://mirrors.cloud.tencent.com/ubuntu/ bionic-backports main universe restricted multiverse
deb     https://mirrors.cloud.tencent.com/docker-ce/linux/ubuntu/ bionic stable
deb-src https://mirrors.cloud.tencent.com/docker-ce/linux/ubuntu/ bionic stable
```

# 2、wsl中ubuntu 18：

## 1）、使能ssh server：

```bash
# 启动sshd
cd /etc/ssh
sudo ssh-keygen -A
sudo vim sshd_config
#------------------------------------------------------#
Port 22
ListenAddress 0.0.0.0
PasswordAuthentication yes
#------------------------------------------------------#
sudo service ssh start  # start/restart/stop
```

# 3、wsl2修改内存和swap大小：

```bash
# 关闭wsl：
wsl --shutdown
# 创建文件：
C:\Users\rhosoon\.wslconfig
# 增加配置：
#------------------------------------------------------#
[wsl2]
memory=2.5G
swap=8G
localhostForwarding=true
#------------------------------------------------------#
# 重启wsl
```

# 4、FAQ

## 1)、wsl2网络：
- wsl2网络受VPN软件影响，如OpenVPN，需卸载VPN软件后重启Windows；