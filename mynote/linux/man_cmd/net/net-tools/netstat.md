# 1、命令参数：

```bash
netstat
    -a    # 显示所有socket
    -l    # 显示监听服务的socket
    -t
    -u
    -n    # 以数字形式显示
    -p    # 显示socket的PID和程序名
    -r    # 显示路由表
```

# 2、常用方式：

```bash
netstat -l
# 查看所有端口监听
netstat -nlp
# 查看所有tcp端口监听
netstat -nltp
# 查看所有udp端口监听
netstat -nlup
```

