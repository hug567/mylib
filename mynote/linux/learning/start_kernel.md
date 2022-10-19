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

```

