# 1、命令参数：

```bash
sudo apt install ethtool

ethtool
	-h                         # 查看帮助
	-c <eth>                   # 显示联合选项
	-S <eth>                   # 查看统计信息
	-t <eth>                   # 执行网卡自测试
```

# 2、常见用法：

```bash
ethtool eth0
ethtool -S eth0
# 执行网卡自测试，需驱动支持
ethtool -t eth0
```

