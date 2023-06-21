# 1、简介：

- 基于内存的文件系统，创建是不需要使用mkfs等初始化；

- tmpfs文件系统注册：
```c
//mm/shmem.c
static struct file_system_type shmem_fs_type = {
	.name		= "tmpfs",
};

shmem_init()
	register_filesystem(&shmem_fs_type)
```