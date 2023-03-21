# 1、dumpe2fs功能：

- 打印ext2、ext3、ext4文件系统的超级快和块组信息。

# 2、选项：

```bash
dumpe2fs    # 打印超级块和块组信息
    -b    # 显示文件系统中保留的坏块
    -f    #
    -g    #
    -h    # 只打印超级块信息
    -i    # 从镜像文件中读取文件系统信息
    -m    #
    -x    #
```

# 3、常见用法：

```bash
df -T    # 查看文件系统类型

dumpe2fs /dev/hda            # 打印超级块和块组信息
dumpe2fs -h /dev/hda         # 只打印超级块信息
dumpe2fs -i file.img         # 从镜像文件中读取文件系统信息
```

