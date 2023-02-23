# 1、gzip：

```bash
# gzip不能压缩目录
gzip test                  # 压缩test文件为test.gz
gzip -k test               # 保留原文件压缩

gzip -d test.gz            # 解压test.gz文件为test
```

# 2、gunzip：

```bash
gunzip test.gz             # 解压test.gz文件为test
gunzip -k test.gz          # 保留原文件解压
```
