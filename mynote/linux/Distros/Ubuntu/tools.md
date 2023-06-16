## 1、htop

```shell
htop mem条目颜色含义：
绿色：已用内存
蓝色：缓冲区
黄色：缓存

# 清理缓存：
sudo sh -c 'echo 1 > /proc/sys/vm/drop_caches'    #仅清除页面缓存
sudo sh -c 'echo 2 > /proc/sys/vm/drop_caches'    #清除目录项和inode
sudo sh -c 'echo 3 > /proc/sys/vm/drop_caches'    #清除页面缓存、目录项以及inode
```

