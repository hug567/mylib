# 1、下载：

## 1）、安装npcap：

- https://npcap.com/#download

## 2）、下载wireshark：

- https://www.wireshark.org/download.html

## 3）、使用：

```bash
菜单栏 -> 捕获 -> 选项 -> Input -> 选择网口 -> 输入捕获过滤器... -> 开始
```

# 2、常见用法：

```bash
# 过滤指定源ip的包
ip.src == 192.168.0.1
# 过滤指定目的ip的包
ip.dst == 192.168.1.1
# 条件：与
ip.src == 192.168.0.1 and ip.dst == 192.168.1.1
```

- v4.2.3：

```bash
# 指定ip
host 192.168.0.2
# 指定ip和端口
host 192.168.0.2 and port 4003
```

