# 1、命令参数：

```bash
mklink
	/d           # 建立目录符号链接
	/j           # 建立目录软链接
	/h           # 建立文件硬链接
```

# 2、常见用法：

```bash
# 建立文件软连接
mklink D:\link D:\sourcefile
# 建立目录符号链接
mklink /d D:\link D:\sourcedir
```

