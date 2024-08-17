# 1、gzip：

```bash
gzip
    -k                    # 保留源文件
    -d                    # 解压
    -1                    # 压缩最快
    -9                    # 压缩最小

# gzip不能压缩目录
gzip test                  # 压缩test文件为test.gz
gzip -k test               # 保留原文件压缩
# 压缩目录：先用tar打包，再用gzip压缩
tar -cvf file.tar file
gzip -k file.tar

gzip -d test.gz            # 解压test.gz文件为test
```

# 2、gunzip：

```bash
gunzip
    -h                    # 查看帮助
    -k                    # 保留源文件
    -c                    # 解压后的内容输出到stdout，同时保留原文件

gunzip test.gz             # 解压test.gz文件为test
gunzip -k test.gz          # 保留原文件解压，解压后文件名为test
# 解压到指定文件，同时保留原文件
gunzip -c test.gz > test.log
```
