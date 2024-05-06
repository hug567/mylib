# 1、命令参数：

```bash
netsh
	-h                                  # 查看帮助
```

# 2、常见用法：

## 1）、端口相关：

```bash
netsh interface

# 查看路由
netsh interface ipv4 show route

# 以管理员身份打开powershell:
# 查看所有端口转发
netsh interface portproxy show all
# 远程主机设置端口转发
netsh interface portproxy add v4tov4 listenport=10022 connectaddress=192.168.255.230 connectport=22
# 删除转发的端口
netsh interface portproxy delete v4tov4 listenport=10022 listenaddress=192.168.255.230
# 本机打开远程主机映射端口
http://101.45.92.102:1234
```

## 2）、网桥相关：

```bash
# 查看帮助
netsh bridge help
#
netsh bridge show adapter
```

