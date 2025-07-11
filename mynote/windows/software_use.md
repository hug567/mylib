## 1、端口转发：

### 1)、Linux设置端口转发：

```shell
sudo apt install socat
sudo socat TCP4-LISTEN:1234,reuseaddr,fork TCP4:192.168.0.1:80 &     # 设置端口转发
http://101.45.74.234:1234                                            # 访问端口
netstat -antup                                                       # 查看所有转发端口
ps aux | grep socat                                                  # 查看端口转发后台进程
kill <PID>                                                           # 终止转发进程
```

### 2)、Windows设置端口转发：

```shell
# 以管理员身份打开powershell:
# 远程主机设置端口转发
netsh interface portproxy add v4tov4 listenport=1234 connectaddress=192.168.0.1 connectport=80
# 查看所有端口转发
netsh interface portproxy show all
# 删除转发的端口
netsh interface portproxy delete v4tov4 listenport=1234
# 本机打开远程主机映射端口
http://101.45.92.102:1234
```

### 3)、ssh设置端口转发：需可ssh连接远程主机

```shell
ssh -L 0.0.0.0:1234:192.168.0.1:80 user@101.45.92.102                # 本机转发远程主机端口
http://localhost:1234                                                # 本机浏览器打开
```

### 4)、Windows安装ssh:

- 在线安装：

```bash
设置 -> 应用 -> 应用和功能 -> 可选功能 -> 添加功能 -> OpenSSH 服务器 -> 安装
设置 -> 应用 -> 应用和功能 -> 系统组件 -> 可选功能 -> 添加功能 -> OpenSSH 服务器 -> 安装
设置 -> 系统 -> 可选功能 -> ......

# 以管理员身份运行powershell:
Start-Service sshd                                            # 启动sshd
Set-Service -Name sshd -StartupType 'Automatic'               # 设置sshd自启动
# 其他常用操作：
Get-Service sshd                                              # 查看sshd状态
Stop-Service sshd                                             # 关闭sshd服务
Restart-Service sshd                                          # 重启sshd服务
```

- 离线安装：

```bash
https://github.com/PowerShell/Win32-OpenSSH/releases          # 下载opensSSH
C:\Program Files\OpenSSH                                      # 解压到安装目录
# 将OpenSSH路径添加到系统路径
# 启动ssh-agnet
服务 -> OpenSSH Authentication Agent -> 启动类型改为“手动” -> 右键设置启动
# 报错：packet_write_wait: Connection to 10.151.150.233 port 22: Broken pipe
# 以管理员身份运行powershell并进入OpenSSH安装目录：
.\FixHostFilePermissions.ps1                                  # 执行修复脚本

ssh user@101.45.92.102                                        # ssh连接Windows

# ssh免密登录Windows：
cat ~/.ssh/id_rsa.pub                                         # 拷贝登录机ssh公钥到Windows机器的 C:\Users\xxx\.ssh\authorized_keys
# 修改sshd配置文件：C:\ProgramData\ssh\sshd_config
# 确保以下3条没有被注释
PubkeyAuthentication yes
AuthorizedKeysFile	.ssh/authorized_keys
PasswordAuthentication no
# 确保以下2条有注释掉
#Match Group administrators
#       AuthorizedKeysFile __PROGRAMDATA__/ssh/administrators_authorized_keys
Restart-Service sshd                                          # 重启sshd服务
```

- 常见问题：
  - 1）、问题：OpenSSH SSH Server 服务无法启动，发生系统错误1067；
    - 解决： 删除目录C:\ProgramData\ssh，卸载OpenSSH Server后重装；

## 2、gitbash

```c
//显示中文乱码：
Right Click -> Options... -> Text -> Locale:zh_CN -> Character set:UTF-8 -> Save
git config --global core.quotepath false
git config --global i18n.commitencoding utf-8
git config --global i18n.logoutputencoding utf-8
```

## 3、cmder

```shell
Ctrl+Tab                                              # 跳转到下一个窗口
Ctrl+Shift+Tab                                        # 跳转到上一个窗口
Ctrl+num                                              # 跳转到指定序号窗口
Ctr+T                                                 # 新建创建
```



