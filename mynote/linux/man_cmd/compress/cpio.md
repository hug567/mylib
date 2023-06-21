# 1、命令参数：

```bash
cpio
	-o                              #
```

# 2、常用命令：

```bash
# cpio解包
cpio -idv < file.cpio

# 当前目录下所有文件打包成cpio包
find . | cpio -o --format=newc > ../file.cpio
find . | cpio -o -H newc > ../file.cpio
```

