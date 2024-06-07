## 1、Linux挂载Windows目录：

```bash
# 1. Windows目录设置共享:
文件夹右键 -> 属性 -> 共享 -> ......

# 2. Linux查看当前用户gid与uid:
id

# 3. Linux挂载Windows目录:
sudo mount -t cifs -o username=Administrator,password=****,gid=1000,uid=1000 //192.168.1.26/share ~/share

# 4. 卸载目录:
sudo umount ~/share
```

## 2、Windows挂载linux目录：

### 1)、ubuntu安装samba：
```bash
# 安装samba：
sudo apt install samba
# 在配置文件末尾添加：
sudo vim /etc/samba/smb.conf
#-----------------------------------------------#
[samba]
  comment = samba home direction
  path=/disk/sda
  browseable = yes
  writeable = yes
  available = yes
  valid users = hx
  write list = hx
  directory mask = 0755
  create mask = 0755
#-----------------------------------------------#
# 重启smbd：
sudo systemctl restart smbd
# 设置密码：
sudo smbpasswd -a hx
```

### 2)、windows映射网络驱动器：

```bash
此电脑 -> 右键 -> 映射网络驱动器(N)...
文件夹：\\10.110.0.3\samba -> 完成
```

## 3、网卡连不上无线网络：

- 休眠一下电脑再启动；

### 1）、浏览器能上网但网卡显示无法连接到internet：

- 原因：无法连接微软默认的用于确认网络状态的DNS服务器 dns.msftncsi.com；

- 修复：修改为阿里云公共云地址即可；

- 修改注册表：Win + R -> regedit -> 计算机\HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\NlaSvc\Parameters\

- 修改以下几项值：

```bash
ActiveDnsProbeContent		REG_SZ		131.107.255.255
ActiveDnsProbeContentV6		REG_SZ		fd3e:4f5a:5b81::1
ActiveDnsProbeHost			REG_SZ		dns.msftncsi.com
ActiveDnsProbeHostV6		REG_SZ		dns.msftncsi.com
```

- 修改为：

```bash
ActiveDnsProbeContent		REG_SZ		223.5.5.5
ActiveDnsProbeContentV6		REG_SZ		2400:3200::1
ActiveDnsProbeHost			REG_SZ		dns.alidns.com
ActiveDnsProbeHostV6		REG_SZ		dns.alidns.com
```

- 修改后重启电脑；

## 4、win10时间显示秒数：

```bash
# 打开注册表：
Win+R -> regedit
# 打开添加注册表项：
HKEY_CURRENT_USER\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\Advanced
# 添加DWORD类型值，并修改数据值为：1
ShowSecondsInSystemClock    REG_DWORD    0x00000001 (1)
# 最后重启电脑
```

## 5、win10允许被ping：

- 控制面板 -> Windows Defender 防火墙 -> 高级设置
  - 入站规则：核心网络诊断 - ICMP 回显请求(ICMPv4-In) -> 允许
  - 出栈规则：核心网络诊断 - ICMP 回显请求(ICMPv4-Out) -> 允许

## 6、允许应用通过防火墙：

- 控制面板 -> Windows Defender 防火墙 -> 允许应用或功能通过Windows Defender防火墙 -> 选中应用，勾选“专用”和“公用” -> 确定
