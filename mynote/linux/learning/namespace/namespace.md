# 1、各种命名空间：

```c
/*
 * 用户命名空间：
 *   允许在不同的用户命名空间使用相同值的用户ID和组ID
 *   主要用于隔离用户权限
 */
struct user_namespace
struct mnt_namespace
```

- linux支持的namespace：
```c
名称			宏定义				隔离内容
Cgroup	CLONE_NEWCGROUP	Cgroup root directory (since Linux 4.6)
IPC		CLONE_NEWIPC	System V IPC, POSIX message queues (since Linux 2.6.19)
Network	CLONE_NEWNET	Network devices, stacks, ports, etc. (since Linux 2.6.24)
Mount	CLONE_NEWNS		Mount points (since Linux 2.4.19)
PID		CLONE_NEWPID	Process IDs (since Linux 2.6.24)
User	CLONE_NEWUSER	User and group IDs (started in Linux 2.6.23 and completed in Linux 3.8)
UTS		CLONE_NEWUTS	Hostname and NIS domain name (since Linux 2.6.19)
```