# 1、命令参数：

```bash
sudo apt install unzip

unzip
	-l       # 列出文件
	-d dir   # 提取文件到目录
```

# 2、常见用法：

```bash
# 解压文件到当前目录
unzip file.zip
# 解压文件到指定目录
unzip file.zip -d dir
# 解压部分内容到指定目录
unzip file.zip "aaa/bbb" -d dir

# 查看压缩包中文件
unzip -l file.zip
# 查看压缩包中顶层目录文件
unzip -l file.zip | sed '1,3d' | awk '{print$4}' | awk -F '/' '{print$1}' | sed '/^\s*$/d' | sort -u
```
