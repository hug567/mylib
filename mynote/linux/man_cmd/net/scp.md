# 1、命令参数：

```bash
scp
	-P <port>                     # 指定端口(默认22)
```

# 2、常见用法：

```bash
# 拷贝目录到远端（软连接将被转换成实体文件）
scp -r dir user@192.168.0.101:~
# 从远端拷贝多个文件
scp hx@10.110.0.3:~/temp/tftpboot/\{BOOT.BIN,image.ub\} .
# scp通过跳板机拷贝文件到远端
scp -P 22 -o 'ProxyJump rhosoon@192.168.99.143 -p 22' get_tag.sh hx@172.22.195.55:~
# scp通过跳板机从远端拷贝文件到本地
scp -P 22 -o 'ProxyJump rhosoon@192.168.99.143 -p 22' hx@172.22.195.55:~/get_tag.sh ./

# 从Windows scp文件：
scp Administrator@10.110.0.2:/E:/cpu1.bin .
```

