# 1、命令参数：

```bash
scp
	-p <port>                     # 指定端口(默认22)
```

# 2、常见用法：

```bash
# 拷贝目录到远端（软连接将被转换成实体文件）
scp -r dir user@192.168.0.101:~
# 从远端拷贝多个文件
scp hx@10.110.0.3:~/temp/tftpboot/\{BOOT.BIN,image.ub\} .
```

