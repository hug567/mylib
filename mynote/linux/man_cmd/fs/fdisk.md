# 1、命令参数：

```bash
fdisk    # 创建和维护分区表
    -l          # 列出所有分区表
    -s <dev>    # 显示指定分区

# 菜单操作说明
    m    # 显示菜单和帮助信息
    a    # 活动分区标记/引导分区
    d    # 删除分区
    l    # 显示分区类型
    n    # 新建分区
    p    # 显示分区信息
    q    # 退出不保存
    t    # 设置分区号
    v    # 进行分区检查
    w    # 保存修改
    x    # 扩展应用，高级功能
```

# 2、常用方式：

```bash
fdisk -l                     # 查看所有分区
fdisk -l -s /dev/sda         # 查看指定分区

# 新建分区
sudo fdisk /dev/sda
```

- 例：mmcblk0中已新建了2个分区mmcblk0p1、mmcblk0p1， 但mmcblk0中还有空间

```bash
root@ax_peta:/run/media# ls -l /dev/mmcblk0*
brw-rw----    1 root     disk      179,   0 Jan  1  1970 /dev/mmcblk0
brw-rw----    1 root     disk      179,   1 Jan  1  1970 /dev/mmcblk0p1
brw-rw----    1 root     disk      179,   2 Jan  1  1970 /dev/mmcblk0p2
```

- 则可在mmcblk0中继续新建分区：

```bash
sudo fdisk /dev/mmcblk0
```

