# 1、常用参数：

```bash
# 安装
sudo apt install binwalk lzop

binwalk
	-e                       # 自动提取已知的文件类型
	-M                       # 递归提取
		-d <depth>               # 递归深度，默认8
```

# 2、常见用方式：

```bash
# 提取文件
sudo binwalk -e <Image>
```

