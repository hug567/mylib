# 1、常见用法

```bash
ps                                 # 打印当前会话中的进程信息
  -e/-A                              # 选择所有进程
  -T                                 # 打印所有线程信息
ps aux                             # 打印所有进程信息
ps -elT                            # 打印所有线程信息
ps -elTF
# 按指定格式打印所有线程信息 (显示完整线程名称)
ps -eT -o f,s,uid,pid,spid,ppid,c,pri,ni,addr,sz,wchan,rss,psr,stime,tty,time,cmd

# 查看进程所属调度类 (class)
#   TS  SCHED_OTHER
#   FF  SCHED_FIFO
#   RR  SCHED_RR
#   B   SCHED_BATCH
#   ISO SCHED_ISO
#   IDL SCHED_IDEL
#   -   未上报
#   ?   未知的值
ps -eTo pid,spid,pri,ni,class,cmd
```

# 2、打印的信息含义：

```bash
C                                  #
PRI                                #
NI                                 #
ADDR                               #
SZ                                 # 核心映像的物理页大小
WCHAN                              # 进程处于休眠状态的内核函数的名称
RSS                                # 常驻集大小，即任务所使用的非交换物理内存
PSR                                # 进程当前被分配给的处理器
STIME                              # start time，任务启动的时间
TTY                                #
TIME                               # 累积cpu运行时间
```
