# 1、常见用法：

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
```

