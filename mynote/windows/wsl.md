# 1、WSL运行docker：

- 安装wsl2：启动或关闭Windows功能 -> 适用于Linux的Windows子系统 -> 虚拟机平台

```bash
# 查看当前安全的linux发行版
wsl -l -v
# 关闭运行的linux(关闭虚拟机进程Vmmem)
wsl --shutdown
# 更新wsl
wsl --update
# 设置wsl2运行linux发行版
wsl --set-version Ubuntu-18.04 2

# wsl卡住，以管理员身份运行powershell/cmd
netsh winsock reset  # 然后重启

# 添加docker源
sudo vim /etc/apt/source.list
#-ubuntu 18.04-----------------------------------------#
deb     https://mirrors.ustc.edu.cn/docker-ce/linux/ubuntu/ bionic stable
deb-src https://mirrors.ustc.edu.cn/docker-ce/linux/ubuntu/ bionic stable
#------------------------------------------------------#
curl -fsSL https://mirrors.ustc.edu.cn/docker-ce/linux/ubuntu/gpg | sudo apt-key add -
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

# 3、FAQ

## 1)、wsl2网络：
- wsl2网络受VPN软件影响，如OpenVPN，需卸载VPN软件后重启Windows；