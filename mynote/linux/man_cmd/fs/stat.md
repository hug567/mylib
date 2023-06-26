# 1、命令参数：

```bash
stat    # 显示文件或文件系统详细信息
    -f <file>     # 显示文件所在文件系统信息
    -L <file>     # 显示软连接指向的实体文件的信息
    -c <format>   # 以指定格式显示文件信息

# 指定格式信息 - 文件
  %a   # 八进制格式访问时间
  %A   # 易读方式访问时间
  %b   # 分配的块数
  %B   # 每块字节数
  %C   # SELinux安全上下文字符串
  %d   # 十进制格式设备号
  %D   # 十六进制格式设备号
  %f   # 十六进制格式原始模式
  %F   # 文件类型
  %g   # 所有者组ID
  %G   # 所有者组名称
  %h   # 硬链接编号
  %i   # inode号
  %m   # 挂载点
  %n   # 文件名
  %N   quoted file name with dereference if symbolic link
  %o   optimal I/O transfer size hint
  %s   total size, in bytes
  %t   major device type in hex, for character/block device special files
  %T   minor device type in hex, for character/block device special files
  %u   user ID of owner
  %U   user name of owner
  %w   time of file birth, human-readable; - if unknown
  %W   time of file birth, seconds since Epoch; 0 if unknown
  %x   time of last access, human-readable
  %X   time of last access, seconds since Epoch
  %y   time of last data modification, human-readable
  %Y   time of last data modification, seconds since Epoch
  %z   time of last status change, human-readable
  %Z   time of last status change, seconds since Epoch

# 指定格式信息 - 文件系统
  %a   free blocks available to non-superuser
  %b   total data blocks in file system
  %c   total file nodes in file system
  %d   free file nodes in file system
  %f   free blocks in file system
  %i   file system ID in hex
  %l   maximum length of filenames
  %n   file name
  %s   block size (for faster transfers)
  %S   fundamental block size (for block counts)
  %t   file system type in hex
  %T   file system type in human readable form
```

# 2、常见用法：

```bash
stat <file>          # 查看文件inode信息
stat -f <file>       # 显示文件所在文件系统信息
stat -L <link>       # 显示软连接指向的实体文件的信息
stat -c "" <file>    # 以指定格式显示文件信息
```

# 3、命令结果：

```bash
[qemu@linux]: /tmp $ stat test_io.ko
  File: test_io.ko
  Size: 72528           Blocks: 144        IO Block: 4096   regular file
Device: 2h/2d   Inode: 6           Links: 1
Access: (0664/-rw-rw-r--)  Uid: ( 1001/ UNKNOWN)   Gid: ( 1001/ UNKNOWN)
Access: 2023-06-15 14:42:50.000000000 +0000
Modify: 2023-06-15 14:42:50.000000000 +0000
Change: 1970-01-01 00:00:00.332000000 +0000

[qemu@linux]: /tmp $ stat -f test_io.ko
  File: "test_io.ko"
    ID: abd48c9b4348dfff Namelen: 255     Type: tmpfs
Block size: 4096
Blocks: Total: 22217      Free: 13279      Available: 13279
Inodes: Total: 22217      Free: 21785
```

