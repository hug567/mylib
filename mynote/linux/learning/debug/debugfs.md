# 1、挂载：

```bash
# CONFIG_DEBUG_FS=y
mount -t debugfs none /sys/kernel/debug
```

# 2、创建节点：

```c
/*
 * 创建debugfs文件：/sys/kernel/debug/test
 * struct dentry *debugfs_create_file(const char *name, umode_t mode,
 *                                    struct dentry *parent, void *data,
 *                                    const struct file_operations *fops);
 */
dentry = debugfs_create_file("test", 0644, NULL, NULL, *g_fops);
```

