# 1、常用参数：

- nmcli：Network Manager Command Line Interface

```bash
nmcli
	-h                           # 查看帮助
```

# 2、常见用法：

```bash
# 扫描所有wifi信号：
nmcli device wifi list
# 连接wifi：
sudo nmcli device wifi connect "<SSID>" password "<password>" ifname wlx502b731c5285
```

