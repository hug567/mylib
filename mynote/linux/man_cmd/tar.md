# 1、命令参数：

```bash
tar
    -c                 # 创建压缩文件
    -f <file.tar.gz>   # 指定压缩文件 
    -j                 # 使用bzip2属性
    -t                 # 查看压缩包中文件
    -x                 # 解压文件
    -v                 # 执行过程中显示文件
    -z                 # 使用gunzip属性
```

# 2、常用命令：

```bash
# 解压文件
tar -xvf file.tar.gz

# 解压到指定目录
tar -xvf file.tar.gz -C dir

# 压缩单个文件或目录
tar -zcvf file.tar.gz file

# 压缩多个文件或目录
tar -zcvf file.tar.gz file1 file2 ...

# 查看压缩包内容
tar -tvf file.tar.gz

# 解压分割的多个tar文件
cat files.tar.gz.part* | tar -zxv

# 压缩后分割为多个文件：使用split命令
tar -zcvf file.tar.gz file | split -b 1024M -d -a 1 - file.tar.gz
```

