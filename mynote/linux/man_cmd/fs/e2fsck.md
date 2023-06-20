# 1、命令参数：

```bash
# 查看手册
man e2fsck

e2fsck    # ext2/3/4磁盘修复
    -a/-p        # 检查分区并自动修复
    -b <num>     # 设置超级块位置
    -B <size>    # 设置块大小，如：-B
    -c           # 检查是否有坏块
    -D           # 优化目录
    -f           # 强制检查，默认clean时不检查
    -n           # 已只读方式打开块设备
    -v           # 显示详细信息
    -y           # 启用交互模式
```

# 2、常用方式：

```bash
e2fsck -pvf /dev/sda
e2fsck -yDf /dev/sda
```

