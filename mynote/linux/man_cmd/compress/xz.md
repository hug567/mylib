# 1、命令参数：

```bash
xz
    -k            # 不删除输入文件
    -e            # 用更久时间提高压缩比
    -T <num>      # 多线程，默认1
    -z            # 压缩文件
    -d            # 解压文件
    -l            # 列出压缩包文件
    -0...-9       # 压缩率，默认-6
    -H            # 显示更详细的帮助
```

# 2、常用方式：

## 1)、压缩：

```bash
# 压缩文件，并保留源文件
xz -k <file>

# 压缩目录：先用tar打包，再用xz压缩
tar -cvf <dir.tar> <dir>
xz -k <dir.tar>
```

## 2)、解压：

```bash
xz -k -d <file.xz>
```

## 3)、查看：

```bash
xz -l <file.xz>
```

