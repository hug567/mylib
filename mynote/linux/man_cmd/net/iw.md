# 1、iw：

```bash
# 扫描所有wifi信号：
sudo iw dev wlx502b73089fc9 scan | grep SSID:
```

# 2、iwlist：

```bash
# 扫描所有wifi信号：
sudo iwlist WLAN0 scan | grep ESSID
```

# 3、iwconfig：

```bash
# 连接wifi：
sudo iwconfig WLAN0 essid "<SSID>" key s:<password>
# 动态获取ip：
sudo dhclient WLAN0
```

