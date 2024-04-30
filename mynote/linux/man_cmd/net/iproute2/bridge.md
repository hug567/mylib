# 1、命令参数

```bash
bridge
	help               # 查看帮助
	<OBJECT> help      # 查看对象帮助，支持的OBJECT有：link, fdb, vlan, mdb, monitor
```

# 2、常见用法：

```bash
# 查看网桥接口信息：
bridge link show
# 查看网桥vlan信息：
bridge vlan show
# 查看网桥转发信息：
bridge fdb show
```

