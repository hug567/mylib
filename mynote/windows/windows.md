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

## 7、文档资源管理器导航栏不显示部分目录：

- 不显示“3D对象”等目录：

```bash
Win+R -> regedit -> 定位到项：HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\FolderDescriptions\
# 将以下项中的“ThisPCPolicy”值改为“Hide”：
#-----------------------------------------------------------#
3D对象：{31C0DD25-9439-4F12-BF41-7FF4EDA38722}\PropertyBag
视频：{35286a68-3c57-41a1-bbb1-0eae73d76c95}\PropertyBag
图片：{0ddd015d-b06c-45d5-8c4c-f59713854639}\PropertyBag
文档：{f42ee2d3-909f-4907-8871-4c22fc0bf756}\PropertyBag
下载：{7d83ee9b-2244-4e70-b1f5-5393042af1e4}\PropertyBag
音乐：{a0c69a99-21c8-4671-8703-7934162fcf1d}\PropertyBag
桌面：{B4BFCC3A-DB2C-424C-B029-7FE99A87C641}\PropertyBag
#-----------------------------------------------------------#
# 若没有字符串值“PropertyBag\ThisPCPolicy”，则新建，并设置值为“Hide”；
# 都设置完成后重启“windows资源管理器”
```

- 不显示OneDrive：

```bash
Win+R -> regedit -> 定位到项：HKEY_CLASSES_ROOT\CLSID\{018D5C66-4533-4307-9B53-224DE2ED1FE6}\ShellFolder
将“Attributes”的值由“f080004d”改为“f090004d” -> 设置完成后重启“windows资源管理器”
```

- 不显示常用文件夹：

```bash
控制面板 -> 文件资源管理器选项 -> 常规 -> 取消勾选：在“快速访问”中显示最近使用的文件 -> 取消勾选：在“快速访问”中显示常用文件夹 -> 确定
```

