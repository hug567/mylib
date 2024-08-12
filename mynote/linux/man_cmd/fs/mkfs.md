# 1、命令参数：

```bash
mkfs    # 创建文件系统
    -V           # 详细显示模式
    -t <type>    # 指定文件系统类型，默认ext2
    -c           # 制作前先检查是否有坏块
```

# 2、常用方式：

```bash
# 创建ext4文件系统
sudo mkfs -V -t ext4 /dev/sda
# 创建前检查坏块
sudo mkfs -V -c -t ext4 /dev/sda
# 格式化为fat32文件系统
sudo mkfs.fat -F 32 /dev/sdc
```



 