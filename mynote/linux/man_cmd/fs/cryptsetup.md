# 1、命令参数：

```bash
cryptsetup        # 创建加密分区
    -c <crypto>       # 加密方式 (cat /proc/crypto)
        LUKS               # Linux Unified Key Setup
        Plain
        loop-AES
        TCRYPT
    -h <hash>         # 散列算法
    -i <ms>           # LUKS迭代时间(ms)
    -s <size>         # 密钥长度
```

# 2、常用方式：

```bash
cryptsetup luksFormat /dev/sda                               # 已默认方式加密磁盘
cryptsetup luksOpen /dev/sda sda                             # 打开加密盘，将映射成/dev/mapper/sda
cryptsetup status /dev/mapper/sda                            # 查看加密盘方式
cryptsetup close sda                                         # 关闭加密磁盘，sda为映射名
cryptsetup luksDump /dev/mapper/sda                          # 查看加密盘key slot
```

