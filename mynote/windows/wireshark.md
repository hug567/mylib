# 1、下载：

## 1）、安装npcap：

- https://npcap.com/#download

## 2）、下载wireshark：

- https://www.wireshark.org/download.html

# 2、常见用法：

```bash
# 过滤指定源ip的包
ip.src == 192.168.0.1
# 过滤指定目的ip的包
ip.dst == 192.168.1.1
# 条件：与
ip.src == 192.168.0.1 and ip.dst == 192.168.1.1
```

