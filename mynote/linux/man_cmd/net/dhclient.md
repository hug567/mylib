# 1、常见用法：

```bash
# 动态获取ip地址
sudo dhclient eth0
# 向dhcp请求指定ip
sudo dhclient eth0 -s 192.168.0.100
# 使用动态ip
sudo dhclient -r
```

