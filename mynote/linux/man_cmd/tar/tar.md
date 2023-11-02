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

## 1）、解压：

```bash
# 解压全部文件
tar -xvf file.tar.gz
# 解压单个目录
tar -zxvf file.tar.gz dir01/dir02
# 解压.tar.bz2文件
tar -jxvf file.tar.bz2

# 解压到指定目录
tar -xvf file.tar.gz -C dir

# 查看压缩包内容
tar -tvf file.tar.gz
# 查看压缩包顶层目录内容
tar -tf file.tar.gz | awk -F '/' '{print$1}' | sort -u

# 解压分割的多个tar文件
cat files.tar.gz.part* | tar -zxv
```

## 2)、压缩：

```bash
# 打包但不压缩
tar -cvf file.tar file

# 压缩单个文件或目录(gz)
tar -zcvf file.tar.gz file

# 压缩多个文件或目录(gz)
tar -zcvf file.tar.gz file1 file2 ...

# 压缩后分割为多个文件：使用split命令
tar -zcvf file.tar.gz file | split -b 1024M -d -a 1 - file.tar.gz

# 压缩为bz2格式，体积更小，但压缩解压时间更长
tar -jcvf file.tar.bz2 file
```

