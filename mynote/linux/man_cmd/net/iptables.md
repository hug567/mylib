# 1、命令参数：

```bash
iptables
    -A <chain>             # 增加新规则
        PREROUTING             # 数据包进入路由表之前
        INPUT                  # 通过路由表后目的地为本机
        FORWARDING             # 通过路由表后，目的地不为本机
        OUTPUT                 # 由本机产生，向外转发
        POSTROUTIONG           # 发送到网卡接口之前
    -D                     # 删除规则
    -R                     # 修改规则
    -I                     # 插入规则
    -L                     # 查看规则
    -s 192.168.0.100/24    # 源地址
    -d 192.168.0.1/24      # 目的地址
    -j <target>            # 执行目标
        DNAT                   # 仅用于nat表
            --to-destination 192.168.0.101:22    #
        SNAT                   # 仅用于nat表
            --to-source 192.168.0.100:22
        NETMAP                 # 仅用于nat表
            --to 192.168.0.100/24
        MASQUERADE             # 仅用于nat POSTROUTING, 只用于动态ip连接，静态ip连接使用SNAT
    -i <eth>               # 输入接口
    -o <eth>               # 输出接口
    -n                     # 使用数字格式打印ip地址和端口
    -p <protocol>          # 协议类型：tcp/udp/icmp... 或 all
    -t <table>             # 指定转换表：filter/nat/mangle/raw/security
                               # filter: INPUT, OUTPUT, FORWARD
                               # nat: PREROUTING, INPUT, OUTPUT, POSTROUTING
                               # raw: PREROUTING, OUTPUT
                               # security: INPUT, OUTPUT, FORWARD
    -v                     # 查看详细信息
    --dport <port>         # 目的端口
    --sport <port>         # 源端口
```

- SNAT：Source Network Address Translation，源地址转换，根据指定条件修改数据包的源IP地址；
  - SNAT转换地址的过程中，网关服务器会根据之前建立的 SNAT映射，将响应数据包正确返回局域网中的源主机；只要连接的第一个包被SNAT处理了，这连接及对应数据流的其他包会自动的被进行 SNAT 处理;
  - Internet中的服务器其实不知道局域网PC的IP地址，其中间的转换完全由网关主机完成，可起到内网保护的作用；
  - SNAT 策略用在nat表的POSTROUTING链；
- DNAT：Destination Network Address Translation，目标地址转换；
  - 用来修改目标IP地址和目标端口，用在 nat 表的PREROUTING链和OUTPUT链中；

# 2、常见用法：

```bash
# 查看nat规则
sudo iptables -L -t nat -n -v --line-number
# 查看过滤规则：INPUT, OUTPUT, FORWARD
sudo iptables -L -t filter -n -v --line-number

# 删除nat表路由后规则：1
sudo iptables -t nat -D POSTROUTING 1

# 删除filter表转发规则：1
sudo iptables -t filter -D FORWARD 1

# 设置filter表FORWARD规则默认行为为ACCEPT：
# filter表规则有：INPUT、OUTPUT、FORWARD
# 规则行为有：ACCEPT、DROP
sudo iptables -P FORWARD ACCEPT

# 将80端口的流量转发到8080端口
sudo iptables -t nat -A PREROUTING -p tcp --dport 80 -j REDIRECT --to-port 8080
```

# 3、相关概念：

## 3.1、规则作用位置：

```bash
PREROUTING             # 数据包进入路由表之前
INPUT                  # 通过路由表后目的地为本机
FORWARDING             # 通过路由表后，目的地不为本机
OUTPUT                 # 由本机产生，向外转发
POSTROUTIONG           # 发送到网卡接口之前
```

## 3.2、策略类型：

- ACCEPT：接受；
- REJECT：拒绝并回传拒绝包；
- LOG：记录；
- DROP：丢弃，不相应；

# 4、内网访问外网：

## 1）、环境介绍：

- 共有2台机器：
- A机器有两个网卡：

  - 可访问外网网卡：192.168.100.252；
  - 可访问内网网卡：192.168.99.106；
- B机器只有一个网卡：
  - 可访问内网网卡：192.168.99.141；

## 2）、A机器配置：

```bash
# 在A机器中打开转发：
sudo vim /etc/sysctl.conf
#-------------------------------------------#
net.ipv4.ip_forward = 1
net.ipv6.conf.all.forwarding=1
#-------------------------------------------#
sudo sysctl -p
# 确认转发已打开：
sudo sysctl -a | grep 'net.ipv4.ip_forward'
# 值为1表示打开了转发：
net.ipv4.ip_forward = 1

# 表链策略设为ACCEPT：
sudo iptables -I FORWARD -s 192.168.99.141 -j ACCEPT
sudo iptables -I FORWARD -d 192.168.99.141 -j ACCEPT
# 或将FORWARD链默认规则改为ACCEPT：
sudo iptables -P FORWARD ACCEPT
# 添加SANT转发规则：
sudo iptables -t nat -A POSTROUTING -s 192.168.99.141 -j SNAT --to 192.168.100.252
```

## 3）、B机器配置：

```bash
# 添加默认网关：192.168.99.106
sudo route add default gw 192.168.99.106
# 增加A机器访问外网的DNS：
sudo vim /etc/resolv.conf
#-------------------------------------------#
nameserver 192.168.100.1
#-------------------------------------------#

# 测试：
ping baidu.com
sudo apt update
```

## 4）、使用案例：

### 4.1）、3个网卡，2个转发规则：

- A机器有3个网卡：
  - 10.110.0.3：本地几个电脑的子网
  - 192.168.99.106：公司内网
  - 192.168.100.252：可访问外网
- B机器只有一个网卡：

  - 10.110.0.6：只接入了本地几个电脑的子网
- A机器中添加两个转发规则，使B机器既能访问外网，又能访问公司内网：

```bash
# 源地址是10.110.0.6，目的地址是192.168.99.0/24的网络包，转发到内网网卡192.168.99.106
sudo iptables -t nat -A POSTROUTING -s 10.110.0.6 -d 192.168.99.0/24 -j SNAT --to 192.168.99.106
# 源地址是10.110.0.6，目的地址不是192.168.99.0/24的网络包，转发到外网网卡192.168.100.252
sudo iptables -t nat -A POSTROUTING -s 10.110.0.6 '!' -d 192.168.99.0/24 -j SNAT --to 192.168.100.252
```

- B机器中同样设置默认路由和dns：

```bash
# 添加默认路由：
sudo route add default gw 10.110.0.3
# 或：
sudo ip route add default via 10.110.0.3
# 添加DNS：（访问外网需要DNS解析）
sudo vim /etc/resolv.conf
#-------------------------------------------#
nameserver 192.168.100.1
#-------------------------------------------#
```

### 4.2）、linux作为转发机器，内部机器为linux：

```bash
# 转发linux(10.110.0.3)：
sudo iptables -P FORWARD ACCEPT
sudo iptables -t nat -A POSTROUTING -s 10.110.0.5 '!' -d 10.110.0.0/24 -j SNAT --to 192.168.100.253

# 内部linux(10.110.0.5)：
sudo route add default gw 10.110.0.3
echo "nameserver 119.29.29.29" >> /etc/resolv.conf
```

### 4.3）、linux作为转发机器，内部机器为windows：

```bash
# 转发linux(10.110.0.3)：
sudo iptables -P FORWARD ACCEPT
sudo iptables -t nat -A POSTROUTING -s 10.110.0.5 '!' -d 10.110.0.0/24 -j SNAT --to 192.168.100.253

# 内部windows(10.110.0.6)：
#-------------------------------------------#
# 手动设置windows网卡ip：
IP 地址(I): 10.110.0.6
子网掩码(U): 255.255.255.0
默认网关(D): 10.110.0.3
首选DNS服务器(P): 119.29.29.29
#-------------------------------------------#
```

### 4.4）、windows作为转发机器，内部机器为linux：

```bash
# 转发windows(10.110.0.7)：
# 外网网卡：会给内网网卡自动分配一个ip，若内网网段是其他网段，则需要给内网网卡再添加一个内网ip
“WLAN”上右键 -> 属性 -> 共享 -> 允许其他网络用户通过此计算机的 Internet 连接来连接(N) -> 家庭网络连接(H): 以太网 -> 允许其他网络用户控制或禁用共享的 Internet 连接(O) -> 确定
# 内网网卡：添加一个内网ip
“以太网”上右键 -> 属性 -> Internet 协议版本 4(TCP/IPv4) -> 属性 -> 高级(V)... -> 添加(A)...
IP 地址(I): 10.110.0.7
子网掩码(S): 255.255.255.0
-> 添加(A) -> 确定 -> 确定 -> 关闭

# 内部linux(10.110.0.5)：
sudo route add default gw 10.110.0.7
echo "nameserver 119.29.29.29" >> /etc/resolv.conf
```

### 4.5）、windows作为转发机器，内部机器为windows：

```bash
# 转发windows(10.110.0.7)：
# 外网网卡：会给内网网卡自动分配一个ip，若内网网段是其他网段，则需要给内网网卡再添加一个内网ip
“WLAN”上右键 -> 属性 -> 共享 -> 允许其他网络用户通过此计算机的 Internet 连接来连接(N) -> 家庭网络连接(H): 以太网 -> 允许其他网络用户控制或禁用共享的 Internet 连接(O) -> 确定
# 内网网卡：添加一个内网ip
“以太网”上右键 -> 属性 -> Internet 协议版本 4(TCP/IPv4) -> 属性 -> 高级(V)... -> 添加(A)...
IP 地址(I): 10.110.0.7
子网掩码(S): 255.255.255.0
-> 添加(A) -> 确定 -> 确定 -> 关闭

# 内部windows(10.110.0.6)：
#-------------------------------------------#
# 手动设置windows网卡ip：
IP 地址(I): 10.110.0.6
子网掩码(U): 255.255.255.0
默认网关(D): 10.110.0.7
首选DNS服务器(P): 119.29.29.29
#-------------------------------------------#
```