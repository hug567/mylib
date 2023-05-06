# 1、命令参数：

```bash
sed
	-i               # 修改文件
```

# 2、常见用法：

```bash
# 删除首行
sed -i '1d' file.txt
# 删除1-100行
sed -i '1,100d' file.txt
# 删除尾行
sed -i '$d' file.txt
# 删除空行
sed -i '/^\s\+$/d' file.txt
```

