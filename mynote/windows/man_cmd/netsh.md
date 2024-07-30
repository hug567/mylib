# 1、命令参数：

```bash
netsh
	-h/help/?                                  # 查看帮助
```

# 2、常见用法：

## 1）、端口相关：

```bash
netsh interface

# 查看路由
netsh interface ipv4 show route

# 以管理员身份打开powershell:
# 查看所有端口转发：
netsh interface portproxy show all
# 远程主机设置端口转发：
netsh interface portproxy add v4tov4 listenport=23578 connectaddress=192.168.255.230 connectport=80
# 转发指定ip的端口到内部指定机器：
netsh interface portproxy add v4tov4 listenaddress=101.45.92.102 listenport=23578 connectaddress=192.168.255.230 connectport=80
# 防火墙开启端口转发：
netsh advfirewall firewall add rule name="开启23578端口" dir=in action=allow protocol=TCP localport=23578
# 本机打开远程主机映射端口：
http://101.45.92.102:23578

# 删除转发的端口：
netsh interface portproxy delete v4tov4 listenport=23578 listenaddress=192.168.255.230
netsh interface portproxy delete v4tov4 listenport=23578

# 删除防火墙规则：
netsh advfirewall firewall del rule name="开启23578端口"
```

- 不建议使用的端口：10080等，最好使用不常见端口；

## 2）、网桥相关：

```bash
# 查看帮助
netsh bridge help
#
netsh bridge show adapter
```

## 3）、防火墙相关：

```bash
# 查看所有防火墙规则：
netsh advfirewall firewall show rule
# 过滤查看：
netsh advfirewall firewall show rule all | findstr 10080

# 防火墙添加端口开启规则：
netsh advfirewall firewall add rule name="开启23578端口" dir=in action=allow protocol=TCP localport=23578

# 删除防火墙规则：
netsh advfirewall firewall del rule name="开启23578端口"
```

