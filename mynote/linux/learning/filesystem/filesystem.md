# 1、文件系统注册：

- 注册：向系统注册各类文件系统，一种只需要注册一次

	- 常见文件系统类型有：sysfs、tmpfs、bdev、proc、cgroup、cgroup2、cpuset 等；

```c
int register_filesystem(struct file_system_type * fs)  //fs/filesystems.c
```
- 所有注册的文件系统，已链表形式存储在file_systems中：
```c
static struct file_system_type *file_systems;  //fs/filesystems.c
```

- 读取cat /proc/filesystems可查看所有已注册的文件系统：

```bash
cat /proc/filesystems
```















安装：mount



mount_hashtable