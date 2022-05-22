## linux进程相关：

## 1、基本概念：

* 进程：执行实体，PID为进程标识符；

* 进程组：一组相关的进程集合，PGID为进程组ID，等于进程组组长的PID；

* 前台进程组：可读终端输入，一个会话中只有一个前台进程组，终端输入的控制信号将被发送给前台进程组的所有进程；

* 后台进程组：不可读终端输入，一个会话中可有多个后台进程组；

* 会话：一个会话有一个前台进程组和多个后台进程组，有一个控制终端，可实现交互；

## 2、相关函数：

* 创建新session：

```c
/*
 * 功能：创建新session，sid为调用进程pid，同时创建新进程组，pgid为调用进程pid;
 * 限制：调用进程不能是进程组首进程;
 */
pid_t setsid(void);
```

* 设置进程PGID(修改所在进程组)：

```c
/*
 * 调用：
 *   1). 若pid=0, 修改当前调用进程的pgid;
 *   2). 若pgid=0, 创建新的进程组，进程pid为其首进程，新的进程组pgid=pid;
 * 限制：
 *   1). pid进程不能是会话首进程；
 *   2). pid指定的进程需为调用进程或其子进程，不能修改不相关进程的pgid;
 *   3). 若pid进程为调用进程子进程，子进程不能执行exec函数；
 *   4). 若在进程组间移动，pid进程需与目标pgid子进程在同一会话中；
 */
int setpgid(pid_t pid, pid_t pgid);
```

* 设置前台进程组：

```c
/*
 * 功能：设置pgid进程组为前台进程组
 */
int tcsetpgrp(int fd, pid_t pgid);
```

* 获取前台进程组id：

```c
pid_t tcgetpgrp(int fd);
```

* 获取会话ID：

```c
pid_t tcgetsid(int fd);
```

* 获取控制终端：

```c
/*
 * 功能：抢占控制终端，fd指向一个终端tty，执行成功返回0，失败返回-1并设置errno;
 * 限制：fd指向的控制终端不能是另一个session的控制终端，除非调用者是root;
 */
int ret = ioctl(fd, TIOCSCTTY, 1);
```

* 放弃控制终端：

```c
/*
 * 功能：放弃控制终端，fd指向一个终端tty，执行成功返回0，失败返回-1并设置errno;
 * 限制：调用进程需持有fd指向的终端tty; 若果调用进程是session leader, 讲给前台进程组发送SIGHUP和
 *      SIGCONT信号, 当前session中所有进程失去该控制终端；
 */
int ret = ioctl(fd, TIOCNOTTY, 1);
```

## 3、linux相关命令：

```shell
# 查看进程相关ID
ps xao pid,pgid,pgrp,sid,ppid,comm
```

## 4、shell进程关系：

* 执行普通命令：

  shell中执行前台命令时，调用setpgid创建新的进程组，一个job中的所有进程在同一个新的进程组中，shell调用wait等待该进程组执行结束；命令执行结束后，shell再调用tcsetpgrp，将自己重新设置为前台进程组，继续读输入命令。

* shell执行前台命令，一行中的多个命令在一个job中，shell进程会将job中的进程设置到新的进程组中，job中第一个进程为该进程组的首进程：

```c
static void
forkparent(struct job *jp, union node *n, int mode, pid_t pid)
{
    ...
        if (jp->nprocs == 0)
                pgrp = pid;
        else
                pgrp = jp->ps[0].ps_pid;
        /* This can fail because we are doing it in the child also */
        setpgid(pid, pgrp);
    ...
}
```

* job中的进程会将自己设置为前台进程组：

```c
static NOINLINE void
forkchild(struct job *jp, union node *n, int mode)
{
    ...
        setpgid(0, pgrp);
        if (mode == FORK_FG)
            xtcsetpgrp(ttyfd, pgrp);
    ...
}
```

* job执行结束后，父进程shell会再将自己设置为前台进程组：

```c
static int
waitforjob(struct job *jp)
{
    ...
    if (jp->jobctl) {
        xtcsetpgrp(ttyfd, rootpid);
    }
    ...
}
```

## 5、telnetd创建新session的主要过程：

```c
//telnetd:
fd = open("/dev/ptmx");
name = ptsname(fd);
vfork();
  //child:
  getpid();
  setsid();
  open("/dev/pts/x");
  dup2();
  tcsetpgrg();
  tcgetattr();
  tcsetattr();
  exec("login");

//login:
exec("shell");
```

