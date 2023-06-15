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
gunzip test.gz             # 解压test.gz文件为test
gunzip -k test.gz          # 保留原文件解压
```
