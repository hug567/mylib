# 1、安装：

```bash
sudo apt install iproute2

# 安装的命令：dpkg -L iproute2 | grep bin
/bin/ip
/bin/ss
/sbin/bridge
/sbin/devlink
/sbin/rtacct
/sbin/rtmon
/sbin/tc
/sbin/tipc
/usr/bin/lnstat
/usr/bin/nstat
/usr/bin/rdma
/usr/bin/routef
/usr/bin/routel
/usr/bin/ctstat
/usr/bin/rtstat
/usr/sbin/arpd
/usr/sbin/genl
```

# 2、常见用法：

```bash
# 显示所有网卡
ip a/address
# 显示指定网卡信息：
ip a show dev eno1
ip address show dev eno1
# 设置ip
ip addr add dev eno1 192.168.0.13/24
# 删除ip
ip addr del dev eno1 192.168.0.13/24

# 列出路由
ip route
ip route show
ip route list
ip route show table all

sudo ip link set dev eno1 up/down                           # 启动/关闭网卡
sudo ip addr add dev eno1 192.168.1.26/24                   # 设置ip (或：为同一网卡新增不同ip)
sudo ip addr del dev eno1 192.168.1.26/24                   # 删除ip
sudo ip route add default via 192.168.1.1 dev eno1          # 添加路由

ip link help                                                # 查看link命令帮助
sudo ip link set dev ens33 address 11:22:33:44:55:66        # 设置MAC地址
sudo ip link set dev ens33 broadcast 11:22:33:44:55:66      # 设置广播地址
sudo ip link set dev ens33 mtu 1500                         # 设置MTU

# 修改网卡名
sudo ip link set eth0 down
sudo ip link set eth0 name eth1
sudo ip link set eth1 up

# 查看ARP缓存(MAC表)
ip neighbor show
```

# 3、路由：

```bash
# 添加默认路由：
sudo ip route add default via 10.110.0.3
# 路由设置指定ip走指定网卡：
sudo ip route add 192.168.99.221/32 via 10.110.0.3 dev eno1
# 删除一个默认路由：
sudo ip route del default via 192.168.99.1 dev wlx502b731c5285
```

# 4、ipv6：

```bash
# 查看网卡ipv6地址：
ip -6 addr show
# 查看ipv6路由表：
ip -6 route show
# 添加ipv6默认路由：
sudo ip -6 route add default dev wlx82771688de0a
```





