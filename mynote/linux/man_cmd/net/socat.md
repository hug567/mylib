# 1、常用命令：

```bash
sudo apt install socat
socat
	-h                             # 查看帮助
```

# 2、常见用法：

```bash
# 设置端口转发
sudo socat TCP4-LISTEN:1234,reuseaddr,fork TCP4:192.168.0.1:80 &
```

