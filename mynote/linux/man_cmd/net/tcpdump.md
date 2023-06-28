# 1、命令参数：

```bash
tcpdump 
    -i eth0                                           # 指定监听网卡
    -nn                                               # 显示ip和端口
    -nn 'icmp'                                        # 监听icmp协议(ping)
    -nn 'host 192.168.0.13'                           # 监听指定主机
    -nn 'src 192.168.0.13'                            # 监听来自指定主机的包
    -nn 'dst 192.168.0.13'                            # 监听发往指定主机的包
    -nnA 'port 80'                                    # 监听指定端口
    -nnA 'port 80 and src host 192.18.0.13'           # 监听来自指定主机和端口的包
    -nnA '!port 22'                                   # 监听除22端口以外的端口
    -e                                                # 打印mac地址
    -xx                                               # 打印网络包内容

ARP：Address Resolution Protocol，地址解析协议，询问目标IP对应的MAC地址
```

# 2、常见用法：

```bash
# 监听来自或发放指定地址的所有包
tcpdump -i eth1 -nn 'src or dst 10.42.0.23'
# 监听来自或发放指定地址的icmp(ping)包
tcpdump -i eth1 -nn 'icmp and src or dst 10.42.0.23'
# 只监听来自指定ip的icmp request包
tcpdump -i eth1 -nn 'icmp[icmptype] == icmp-echo and src 10.42.0.23'
# 只监听来自指定ip的icmp reply包
tcpdump -i eth1 -nn 'icmp[icmptype] == icmp-echoreply and src 10.42.0.23'
# 监听来自或发放指定地址的arp包
tcpdump -i eth1 -nn 'arp and src or dst 10.42.0.23'
```

# 3、打印含义：

```bash
#
17:42:43.871486 IP 10.42.0.23 > 239.255.0.1: ip-proto-17
#
17:42:43.953094 ARP, Request who-has 10.42.0.24 tell 10.42.0.23, length 28
#
17:42:44.223398 IP 10.42.0.23.49268 > 239.255.0.1.26000: UDP, length 368
#
17:42:44.393770 IP 10.42.0.23.33293 > 239.255.0.1.26000: UDP, bad length 5524 > 1432
# icmp请求(ping)
17:47:31.186347 IP 10.42.0.21 > 10.42.0.22: ICMP echo request, id 5667, seq 1, length 64
# icmp应答(ping)
17:47:31.187494 IP 10.42.0.22 > 10.42.0.21: ICMP echo reply, id 5667, seq 1, length 64
```

