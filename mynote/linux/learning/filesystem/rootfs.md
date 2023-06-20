# 1、挂载根文件系统：

```c
start_kernel()
    vfs_caches_init_early();
	vfs_caches_init();
		mnt_init()
            init_mount_tree()
                mnt = vfs_kern_mount(&rootfs_fs_type, 0, "rootfs", NULL);
                root.mnt = mnt;
                set_fs_root(current->fs, &root);
```



数据解构：

```c
static struct hlist_head *inode_hashtable __read_mostly;  //fs/inode.c
static struct hlist_bl_head *dentry_hashtable __read_mostly;  //fs/dcache.c
static struct hlist_head *mount_hashtable __read_mostly;
static struct hlist_head *mountpoint_hashtable __read_mostly;
```

