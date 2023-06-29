# 1、命令参数：

```bash
mii-tool
	-R                 # 复位MII
	-r                 # 重启自协商
	-w                 # 监控连接状态
	-v                 # 查看连接详细信息
	-p                 # 指定phy地址(0-31)
```

# 2、常见用法：

```bash
# 查看mii连接详细信息
mii-tool -v eth1
```

