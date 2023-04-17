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
    --dport <port>         # 目的端口
    --sport <port>         # 源端口
```

# 2、常见用法：

```bash
# 查看nat规则
sudo iptables -L -t nat --line-number
# 删除nat规则：1
iptables -t nat -D POSTROUTING 1
```



