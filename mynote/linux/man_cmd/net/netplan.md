# 1、常见用法：

```bash
sudo netplan --debug apply

# 配置文件位置：
/etc/netplan/*.yaml
```

# 2、有线网络：

## 1)、固定ip：
```bash

```

## 2)、dhcp：

```bash

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

```

