# 1、常见用法：

```bash
sudo netplan --debug apply

# 配置文件位置：
/etc/netplan/*.yaml
# 查看当前配置：
netplan get

# 常见renderer：
renderer: NetworkManager
renderer: networkd                  # systemd-networkd
```

# 2、有线网络：

## 1)、固定ip：
```bash
network:
  version: 2
  renderer: NetworkManager
  ethernets:
    wlx82771688de0a:
      dhcp4: false
      addresses:
      - 192.168.1.27/24
      gateway4: 192.168.1.1
      nameservers:
        addresses:
        - 192.168.1.1

# 一个网卡设置多个ip：
network:
  version: 2
  renderer: NetworkManager
  ethernets:
    eno1:
      dhcp4: false
      addresses:
      - 10.110.0.3/24
      - 192.168.0.13/24
      gateway4: 10.110.0.1
      nameservers:
        addresses:
        - 10.110.0.1
```

## 2)、dhcp：

```bash
network:
  version: 2
  renderer: NetworkManager
  ethernets:
    eno1:
      dhcp4: true
```

## 3)、桥接：

```bash
network:
  version: 2
  renderer: NetworkManager
  ethernets:
    ens33:
      dhcp4: no
  bridges:
    br0:
      dhcp4: yes
      interfaces:
         - ens33
```

## 4）、路由/网关：

```bash
# 默认路由：
network:
  version: 2
  renderer: NetworkManager
  ethernets:
    ens33:
      addresses:
        - 192.168.100.2/24
      nameservers:
        addresses: 
          - 192.168.100.1
      routes:
        - to: defalult
          via: 192.168.100.1

# 特定网段路由：
network:
  version: 2
  renderer: NetworkManager
  ethernets:
    ens33:
      addresses:
        - 192.168.100.2/24
      nameservers:
        addresses: 
          - 192.168.100.1
      routes:
        - to: 192.168.99.0、24
          via: 192.168.99.1
```



# 3、无线网络：

## 1)、固定ip：

```bash
network:
  version: 2
  wifis:
    wlx82771688de0a:
      dhcp4: false
      access-points:
        '1201':
          password: '1139321201'
      addresses:
      - 192.168.1.27/24
      gateway4: 192.168.1.1
      nameservers:
        addresses:
        - 192.168.1.1
```

## 2)、dhcp：

```bash
network:
  version: 2
  renderer: NetworkManager
  wifis:
    wlx502b73089fc9:
      dhcp4: true
      access-points:
        'TP-LINK_9128':
          password: 'Hx123poi'

# 多个无线网卡分别连接不同wifi：
network:
  version: 2
  renderer: NetworkManager
  wifis:
    wlx502b73089fc9:
      optional: true
      dhcp4: true
      access-points:
        "TP-LINK_9128":
          auth:
            key-management: "psk"
            password: "Hx123poi"
    wlx502b731c5285:
      optional: true
      dhcp4: true
      access-points:
        "rhosoon_network":
          auth:
            key-management: "psk"
            password: "rhosoon_network"
```

