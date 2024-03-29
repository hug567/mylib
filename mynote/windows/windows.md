## 1、powershell

```bash
echo $pshome                     # 查看powershell home目录
echo $profile                    # 查看powershell配置文件
test-path $profile               # 测试配置文件是否存在

# Windows创建软连接:
mklink /j leetcode_0026.c G:\MyProgram\Git\mylib\c\leetcode\leetcode_0026.c
```

## 2、Linux挂载Windows目录：

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

## 3、Windows挂载linux目录：

### 1)、ubunt安装samba：
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

## 4、网卡连不上无线网络：

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

## 5、win10时间显示秒数：

```bash
# 打开注册表：
Win+R -> regedit
# 打开添加注册表项：
HKEY_CURRENT_USER\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\Advanced
# 添加DWORD类型值，并修改数据值为：1
ShowSecondsInSystemClock    REG_DWORD    0x00000001 (1)
# 最后重启电脑
```