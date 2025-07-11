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

## 1)、查看状态：

```bash
# 扫描所有wifi信号：
nmcli device wifi list
# 连接wifi：
sudo nmcli device wifi connect "<SSID>" password "<password>" ifname wlx502b731c5285

# 查看网口连接状态：
nmcli device status
# 查看可用的网络连接：
nmcli con show
# 查看活动的网络连接
nmcli con show -active
# 查看网络设备详情：
nmcli dev show
nmcli dev show <ens160>
```

## 2)、设置开机自动配置静态ip：

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
## 3)、wifi连接：

```bash
# 查看可用的wifi网络：
nmcli device wifi list
# 指定网卡连接到wifi网络：
sudo nmcli device wifi connect <SSID> password <password> wep-key-type key ifname <eth0>
# 查看连接：
nmcli connection show
# 查看生成的配置文件：
ls /etc/NetworkManager/system-connections
```

## 4)、修改指定网卡的dns：

- 添加dns：

```bash
# 查看网卡对应的连接：
nmcli connection show
# 修改指定连接的dns：
sudo nmcli con mod 'Wired connection 3' ipv4.dns "119.29.29.29"
sudo nmcli con mod <UUID> ipv4.dns "119.29.29.29"
# 使配置生效：
sudo nmcli con up 'Wired connection 3'
sudo nmcli con up <UUID>
# 查看网卡对应的dns：
nmcli dev show
resolvectl status
systemd-resolve --status
```

- 删除dns：

```bash
sudo nmcli con mod eth0 -ipv4.dns 8.8.8.8
```

