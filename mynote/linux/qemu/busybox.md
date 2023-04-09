## Busybox init进程学习

学习版本：busybox 1.34.0

源码文件：init/init.c

对应二进制文件：/sbin/init，linux启动拉起的第一个用户进程

入口函数：

```c
int init_main(int argc UNUSED_PARAM, char **argv)
```

增加一个信号到信号集：

```c
/* 将信号signum加入到信号集set中 */
int sigaddset(sigset_t *set,int signum);
```

查询或设置信号屏蔽集：

```c
/*
 * how:
 *   SIG_BLOCK 新的信号屏蔽集由目前的信号屏蔽集和set指定的信号屏蔽集的组合
 *   SIG_UNBLOCK 目前信号屏蔽集中删除set指定的屏蔽集
 *   SIG_SETMASK 使用set指定的信号屏蔽集
 * oldset: 不为NULL时，存储原信号屏蔽集
 */
int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
```

查询或设置信号处理方式：

```c
/*
 * struct sigaction {
 *     void (*sa_handler) (int);
 *     sigset_t sa_mask;
 *     int sa_flags;
 *     void (*sa_restorer) (void);
 * }
 */
int sigaction(int signum, const struct sigaction*act, struct sigaction *oldact);
```

修改当前工作目录：

```c
int chdir(const char * path);
```

