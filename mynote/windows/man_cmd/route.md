# 1、命令参数：

```bash
route
```

# 2、常见用法：

```bash
# 查看路由表
route print
# 添加路由
route add 172.22.195.0 mask 255.255.255.0 172.22.192.1
# 添加默认路由
route add 0.0.0.0 mask 0.0.0.0 192.168.99.106

# 删除路由
route delete 172.22.195.0
# 修改路由
route change ...
```

