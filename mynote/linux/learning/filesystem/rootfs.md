# 1、挂载根文件系统：

```c
//注册根文件系统

//挂载根文件系统
start_kernel()
    vfs_caches_init_early();
	vfs_caches_init();
		mnt_init()  //fs/namespace.c
            init_mount_tree()
                mnt = vfs_kern_mount(&rootfs_fs_type, 0, "rootfs", NULL);
                root.mnt = mnt;
                set_fs_root(current->fs, &root);

//挂载块设备作为rootfs
start_kernel()
	arch_call_rest_init()
		rest_init()
			kernel_init()
				kernel_init_freeable()
					prepare_namespace()
					    mount_root()
							mount_block_root()
							    do_mount_root()
```

- 数据结构：

```c
static struct hlist_head *inode_hashtable __read_mostly;  //fs/inode.c
static struct hlist_bl_head *dentry_hashtable __read_mostly;  //fs/dcache.c
static struct hlist_head *mount_hashtable __read_mostly;
static struct hlist_head *mountpoint_hashtable __read_mostly;
```

# 2、initrd/initramfs：

```c
rootfs_initcall(populate_rootfs);
	populate_rootfs()
		do_populate_rootfs()
			unpack_to_rootfs((char *)initrd_start, initrd_end - initrd_start);  //解压到一个tmpfs中
```

- CONFIG_BLK_DEV_INITRD：initramfs/initrd

## 1）、initrd：

- ~~CONFIG_BLK_DEV_RAM~~
- initrd是一个单独的文件，通常是gzip压缩的ext文件系统镜像；
- uboot将initrd加载到内存，将dtb传递给内核(x0)，内核从dtb中读取initrd起止位置，存储在变量 **initrd_start** 和 **initrd_end** 中；
```c
//arch/arm64/kernel/head.S
SYM_CODE_START_LOCAL(preserve_boot_args)
	mov	x21, x0				// x21=FDT

SYM_FUNC_START_LOCAL(__primary_switched)
	str_l	x21, __fdt_pointer, x5		// Save FDT pointer(dtb地址，u-boot传递)

start_kernel()  //init/main.c
	setup_arch(char **cmdline_p)  //arch/arm64/kernel/setup.c
		setup_machine_fdt(__fdt_pointer)
    		dt_virt = fixmap_remap_fdt(dt_phys, &size, PAGE_KERNEL);
			early_init_dt_scan(dt_virt)
               	early_init_dt_verify(params);
	               	initial_boot_params = params;
				early_init_dt_scan_nodes();
					of_scan_flat_dt()
						early_init_dt_scan_chosen()
							early_init_dt_check_for_initrd()  //drivers/of/fdt.c
								phys_initrd_start = start;
								phys_initrd_size = end - start;

arm64_memblock_init()  //arch/arm64/mm/init.c
		initrd_start = __phys_to_virt(phys_initrd_start);
		initrd_end = initrd_start + phys_initrd_size;
```

## 2）、initramfs：

- 一个cpio格式的文件系统镜像，直接与内核Image链接在一起，启动是自动被解压和挂载；
- 在链接时其起始位置和大小存储到\_\_initramfs_start、\_\_initramfs_size中；
```c
#ifdef CONFIG_BLK_DEV_INITRD
#define INIT_RAM_FS							\
	. = ALIGN(4);							\
	__initramfs_start = .;						\
	KEEP(*(.init.ramfs))						\
	. = ALIGN(8);							\
	KEEP(*(.init.ramfs.info))
#else
#define INIT_RAM_FS
#endif
```
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