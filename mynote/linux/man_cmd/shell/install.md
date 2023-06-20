# 1、命令参数：

```bash
install
    -d xxx    # 参数视为目录
	-D        # 创建目标目录
	-m xxx    # 设置权限
	-p        # 修改源文件的访问/修改时间与目标文件一致
```

# 2、常用方式：

```bash
# 创建目录
install -d aaa/bbb/ccc

install -D file.txt aaa/bbb/file.txt
install -m 755 file.txt dst/dir
```

