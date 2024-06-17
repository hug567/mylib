# 1、常用参数：

- nmcli：Network Manager Command Line Interface

```bash
nmcli
	-h                           # 查看帮助
```

- NetworkManager配置文件位置：/etc/NetworkManager/system-connections，每个文件代表一个网络连接；
- 配置文件的权限需是：660；
- 修改配置文件后生效：

```bash
# 重新启动NetworkManager：
sudo systemctl restart NetworkManager
```

# 2、常见用法：

```bash
# 扫描所有wifi信号：
nmcli device wifi list
# 连接wifi：
sudo nmcli device wifi connect "<SSID>" password "<password>" ifname wlx502b731c5285

# 查看可用的网络接口：
nmcli device status
# 查看可用的网络连接：
nmcli connection show
```

- 设置开机自动配置静态ip：

```bash
# 有线网卡设置静态ip：
# 创建连接配置：
sudo nmcli con add type ethernet con-name ens160 ifname ens160
# 设置静态ip：
sudo nmcli connection modify ens160 ipv4.addresses 192.168.99.50/24
sudo nmcli connection modify ens160 ipv4.gateway 192.168.99.1
sudo nmcli connection modify ens160 ipv4.dns 192.168.99.1
sudo nmcli connection modify ens160 ipv4.method manual
sudo nmcli connection modify ens160 connection.autoconnect yes
sudo nmcli connection up ens160
# 查看配置文件内容：
sudo cat /etc/NetworkManager/system-connections/ens160
# 重新启动NetworkManager：
sudo systemctl restart NetworkManager
```

