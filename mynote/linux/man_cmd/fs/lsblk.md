# 1、命令参数：

```bash
lsblk    # 显示块设备
    -a            # 显示所有设备
    -b            # 以字节方式显示设备大小
    -d            # 不显示从属或所有者
    -D            # 显示丢弃的功能
    -e <major>    # 不显示指定major号的块设备
    -f            # 显示文件系类型
    -I <major>    # 只显示指定major号的块设备
    -l            # 使用列表格式显示
    -m            # 显示权限信息
    -o <title>    # 显示指定列，如：-o NAME
    -p            # 显示块设备绝对路径
    -t            # 显示拓扑图
```

# 2、常见用法：

```bash
lsblk                # 显示块设备
lsblk -a             # 显示所有块设备
lsblk -f             # 显示文件系统类型
lsblk -afmp          # 显示所有块设备，其文件系统类型及权限，并显示块设备绝对路径
```

