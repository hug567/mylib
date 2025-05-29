# 1、常用命令：

```bash
sudo apt install socat
socat
	-h                             # 查看帮助
```

# 2、常见用法：

```bash
# 设置端口转发，将本地10280端口转发到内网192.168.0.2机器的80端口（不需要sudo）：
# 如需结束转发，结束对应的后台进程即可：
socat TCP4-LISTEN:10280,reuseaddr,fork TCP4:192.168.0.2:80 &
```

