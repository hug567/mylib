# 1、命令参数：

```bash
ifconfig
```

# 2、常见用法：

```bash
ifconfig
ifconfig -a
ifconfig eth0

# 开启/关闭网卡
sudo ifconfig eth0 up/down
# 设置ip及掩码
sudo ifconfig eth0 192.168.1.100 netmask 255.255.255.0
# 设置mac地址
sudo ifconfig eth0 hw ether 11:22:33:44:55:66
```

