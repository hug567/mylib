# Linux启动过程：

## 1、启动过程中驱动加载：

```c
// 内核启动时的线程
start_kernel -> cpu_idle(pid=0)
    |
    -> kernel_init -> init(pid=1)
	|
    -> kthreadd(pid=2) 

先加载驱动,使能磁盘 -> 再挂载根文件系统 -> 再读取各种启动文件

start_kernel()
    vfs_caches_init()  //挂载根文件系统
        mnt_init()
    		init_rootfs()
    		init_mount_tree()
    arch_call_rest_init()
    	rest_init()
    		pid = kernel_thread(kernel_init, NULL, CLONE_FS);
			pid = kernel_thread(kthreadd, NULL, CLONE_FS | CLONE_FILES);

kernel_init()
	kernel_init_freeable()
    	do_basic_setup()
    		do_initcalls()  //包括加载驱动
```

## 2、注册驱动流程：

```c
platform_driver_register()
    __platform_driver_register()
    	driver_register()
    		bus_add_driver()
    			driver_attach()
    				bus_for_each_dev()
					    __driver_attach()
    						device_driver_attach()
    							driver_probe_device()
    								really_probe()
									    ret = drv->probe(dev);
```

## 3、挂载根文件系统：

```c
rootfs是基于内存的文件系统，不需要驱动参与，linux启动阶段使用rootfs文件系统；
磁盘驱动程序和磁盘文件系统成功加载后，linux将系统根目录从rootfs切换到磁盘文件系统；

command line：
	root=/dev/xxx：挂载/dev/xxx设备作为根文件系统；
    initrd：bootloader将较小的根文件系统装载到内存中，启动阶段mount内存中的initrd作为根文件系统；
```

initrd

​	rdinit=/linuxrc

initramfs

default

```c
内核启动时先挂载位于内存中的根文件系统rootfs，后续切换到启动参数中root=xxx指定的磁盘文件系统；

init_rootfs
    
CONFIG_BLK_DEV_INITRD：
    ramfs，由bootloader加载到内存，内核启动时加载为rootfs，直至加载磁盘中的根文件系统
```

* kernel挂载根文件系统：

  1、根文件系统位于磁盘：

  ​		启动参数中指定root=/dev/xxx

  2、根文件系统位于软驱等较慢的设备：

  ​		root=/dev/fd0，内核将文件系统映像复制到ramdisk，

  ​		（ramdisk：在内存中模拟的磁盘文件系统）

  3、使用initrd作为根文件系统：

  ​		bootloader将initrd复制到内存，然后将initrd在内存中的起始地址和大小传递给内核，或者在编译内核时指定initrd在内存中的起始位置和大小；

  ​		若指定root=/dev/ram0，表示将内存中的initrd一直作为根文件系统，后续不切换到磁盘；

```c
start_kernel
    ↓
vfs_caches_init--------------> mnt_init
    ↓                              ↓
rest_init -> kernel_init      sysfs_init
    ↓             ↓                ↓
   init     do_basic_setup    init_rootfs
                  ↓                ↓
             do_initcalls   init_mount_tree
                  ↓
            populate_rootfs
```

