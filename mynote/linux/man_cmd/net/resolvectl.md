# 1、常用参数：

```bash
resolvectl
	-h                                    # 查看帮助
```

# 2、常见用法：

```bash
# 查看当前DNS解析状态：
resolvectl status
# 修改指定网卡使用的DNS服务器：
sudo resolvectl dns wlx085700fdf522 119.29.29.19

# 设置全局DNS服务器：
vim /etc/systemd/resolved.conf
#--------------------------------------------------#
DNS=119.29.29.29
#--------------------------------------------------#
```

