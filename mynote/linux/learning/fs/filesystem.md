# 1、文件系统注册：

- 注册：向系统注册各类文件系统，一种只需要注册一次

	- 常见文件系统类型有：sysfs、tmpfs、bdev、proc、cgroup、cgroup2、cpuset 等；

```c
int register_filesystem(struct file_system_type * fs)  //fs/filesystems.c
```
- 所有注册的文件系统，以链表形式存储在全局变量file_systems中：
```c
static struct file_system_type *file_systems;  //fs/filesystems.c
```

- 读取/proc/filesystems可查看所有已注册的文件系统：

```bash
cat /proc/filesystems
```

# 2、挂载：

- struct dentry：目录项，表示目录或文件；

  - 判断dentry是否是挂载点：

  ```c
  static inline bool d_mountpoint(const struct dentry *dentry)
  {
          return dentry->d_flags & DCACHE_MOUNTED;
  }  
  ```
  
  - dentry_hashtable：存储所有的dentry对象；
  - dentry_unused：

- struct mount：挂载实例，每一个挂载的文件系统都有一个对应的struct mount；

- struct mountpoint：挂载点，struct mount的一个成员；

- mount_hashtable：

- mountpoint_hashtable：

- struct super_block：超级块，