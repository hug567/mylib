# 1、常用命令：

```bash
sudo apt install arp-scan

arp-scan
	--help                          # 查看帮助
```

# 2、常见用法：

```bash
# 扫描局域网中ip：
sudo arp-scan -l
# 指定网卡扫描局域网中ip，弱如果有两个相同ip，并对应不同mac地址，表示有ip地址冲突：
sudo arp-scan -l -I <eth0>
```

