# 1、命令参数：

```bash
readelf
    -h    # 查看文件头信息
    -l    # 显示段头信息
    -S    # 显示节头信息
    -t    # 显示节详细信息
    -s    # 显示所有符号
    -g    # 显示节组信息
```

# 2、常见用法：

```bash
readelf -S vmlinux                   # 查看节头信息
readelf -s vmlinux                   # 查看所有符号
```

