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

# 2、initramfs：

```bash
rootfs_initcall(populate_rootfs);
	populate_rootfs()
		do_populate_rootfs()
			unpack_to_rootfs((char *)initrd_start, initrd_end - initrd_start);
```

- CONFIG_BLK_DEV_INITRD：initramfs/initrd

## 1）、initrd：

- ~~CONFIG_BLK_DEV_RAM~~
- initrd是一个单独的文件，通常是gzip压缩的ext文件系统镜像；
- uboot将initrd加载到内存，并将起始和结束地址传递给内核，内存存储在变量 **initrd_start** 和 **initrd_end** 中；
```c
early_init_dt_check_for_initrd()  //drivers/of/fdt.c
	phys_initrd_start = start;
	phys_initrd_size = end - start;

arm64_memblock_init()  //arch/arm64/mm/init.c
		initrd_start = __phys_to_virt(phys_initrd_start);
		initrd_end = initrd_start + phys_initrd_size;
```

## 2）、initramfs：

- 一个cpio格式的文件系统镜像，直接与内核Image链接在一起，启动是自动被解压和挂载；
- 在链接是其起始位置和大小存储到\_\_initramfs_start、\_\_initramfs_size中；
- 从Image中dump initramfs：
```bash
sudo apt install binwalk lzop
binwalk -e Image | grep cpio
# dd提取
# gunzip解压
# cpio解包
```

- 查看当前挂载的根文件系统：
```bash
cat /proc/mounts | grep " / "
```