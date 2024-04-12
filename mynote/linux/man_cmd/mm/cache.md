# 1、linux清理cache：

```bash
# 仅清理页缓存：
sync; sudo sh -c 'echo 1 > /proc/sys/vm/drop_caches'
# 清理目录项和inode：
sync; sudo sh -c 'echo 2 > /proc/sys/vm/drop_caches'
# 清理页缓存、目录项和inode：
sync; sudo sh -c 'echo 3 > /proc/sys/vm/drop_caches'
```

# 2、清理swap空间：

```bash
sudo sh -c 'swapoff -a && swapon -a'
```

