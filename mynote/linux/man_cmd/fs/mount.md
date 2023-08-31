# 1、命令参数：

```bash
mount    # 挂载分区 
    -a             # 挂载所有/etc/fstab中配置的文件系统
    -t <type>      # 指定文件系统格式
    -v             # 显示详细信息
    -f             # 不真实挂载，通常配合-v
    -o noatime     # 不更新访问时间
    -o nodiratime  # 不更新目录的访问时间
```

# 2、常用方式：

```bash
mount /dev/sda /var     #

# 挂载ext4镜像文件
mkdir mount_dir
sudo mount -o loop file.ext4 mount_dir

# 开机自动挂载磁盘: /etc/fstab
/dev/sda	/disk/sda	ext4	defaults	0	0
```

# 3、挂载u盘：

```bash
# 查看u盘设备及文件系统类型
sudo fdisk -l
# 挂载u盘(fat32)

```

