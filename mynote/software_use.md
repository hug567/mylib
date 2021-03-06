## 1、Mobaxterm：

```shell
# 常用快捷键：
Ctrl + Shift + B                                                     # 显示/隐藏侧边栏
Ctrl + L                                                             # 清除画面
Ctrl + Tab                                                           # 向前导航窗口
Ctrl + Shift + Tab                                                   # 向后导航
```

## 2、端口转发：

### 1)、Linux设置端口转发：

```shell
socat TCP4-LISTEN:1234,reuseaddr,fork TCP4:192.168.0.1:80 &          # 设置端口转发
netstat -antup                                                       # 查看所有转发端口
ps aux | grep socat                                                  # 查看端口转发后台进程
kill <PID>                                                           # 终止转发进程
```

### 2)、Windows设置端口转发：

```shell
# 以管理员身份打开powershell:
# 远程主机设置端口转发
netsh interface portproxy add v4tov4 listenport=1234 connectaddress=192.168.0.1 connectport=80
netsh interface portproxy show all                                   # 查看所有端口转发
netsh interface portproxy delete v4tov4 listenport=1234              # 删除转发的端口
http://101.45.92.102:1234                                            # 本机打开远程主机映射端口
```

### 3)、ssh设置端口转发：需可ssh连接远程主机

```shell
ssh -L 0.0.0.0:1234:192.168.0.1:80 user@101.45.92.102                # 本机转发远程主机端口
http://localhost:1234                                                # 本机浏览器打开
```

### 4)、Windows安装ssh:

```shell
# 在线安装：
设置 -> 应用 -> 应用和功能 -> 可选功能 -> 添加功能 -> OpenSSH 服务器 -> 安装

# 离线安装：
https://github.com/PowerShell/Win32-OpenSSH/releases                 # 下载opensSSH
C:\Program Files\OpenSSH                                             # 解压到安装目录
# 启动ssh-agnet
服务 -> OpenSSH Authentication Agent -> 启动类型改为“手动” -> 右键设置启动
# 以管理员身份运行powershell并进入OpenSSH安装目录：
.\FixHostFilePermissions.ps1                                         # 执行修复脚本
Start-Service sshd                                                   # 启动sshd
Set-Service -Name ssh -StartupType 'Automatic'                       # 设置自启动

ssh user@101.45.92.102                                               # ssh连接Windows
```