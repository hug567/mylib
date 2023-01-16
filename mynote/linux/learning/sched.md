# 1、调度的时机

tick中断中；

中断返回时；

阻塞操作：semaphore、mutex、等待队列等；

# 2、进程状态

```bash
R：TASK_RUNNING，可执行
S：TASK_INTERRUPTIBLE，可中断睡眠状态，进程在等待事件，事件发生时会被唤醒，如socket、锁、信号量等
D：TASK_UNINTERRUPTIBLE，不可中断睡眠状态，进程不响应异步信号，如kill -9
I：IDLE，空闲状态，不可中断睡眠状态的内核线程
T：TASK_STOPPED or TASK_TRACED，暂停或跟踪
    SIGSTOP可是进程进入TASK_STOPPED状态，SIGCONT恢复；进程被跟踪时处于TASK_TRACED状态
Z：TASK_DEAD - EXIT_ZOMBIE，退出状态，成为僵尸进程
X：TASK_DEAD - EXIT_DEAD，退出状态，进程即将被销毁
```

# 3、调度信息：

```bash
cpu#0
  .nr_running                    : 18                           # 可运行任务数量
  .nr_switches                   : 143056637                    # 累积切换次数
  .nr_uninterruptible            : 58476                        #
  .next_balance                  : 4299.147278                  # 
  .curr->pid                     : 388473                       # 正在运行的任务pid
  .clock                         : 17021141.835360              #
  .clock_task                    : 12681871.696416              #
  .avg_idle                      : 21556                        #
  .max_idle_balance_cost         : 500000                       #

cfs_rq[0]:/user.slice
  .exec_clock                    : 0.000000                      # 累积运行时间
  .MIN_vruntime                  : 0.000001                      # 虚拟时间最小的进程的vtime
  .min_vruntime                  : 25202.055937                  # 当前rq vtime下限
  .max_vruntime                  : 0.000001
  .spread                        : 0.000000
  .spread0                       : -1276551.769151
  .nr_spread_over                : 0
  .nr_running                    : 0                             # 处于就绪队列数量
  .load                          : 0
  .load_avg                      : 1
  .runnable_avg                  : 1
  .util_avg                      : 1
  .util_est_enqueued             : 0
  .removed.load_avg              : 0
  .removed.util_avg              : 0
  .removed.runnable_avg          : 0
  .tg_load_avg_contrib           : 1
  .tg_load_avg                   : 1436
  .throttled                     : 0
  .throttle_count                : 0
  .se->exec_start                : 12681871.375232
  .se->vruntime                  : 1301741.993482
  .se->sum_exec_runtime          : 8884.429856
  .se->load.weight               : 730
  .se->avg.load_avg              : 0
  .se->avg.util_avg              : 1
  .se->avg.runnable_avg          : 1
```

# 4、优先级：


- 线程优先级范围：0~139，值越小，优先级越高；
- 用户态线程优先级范围：100~139，默认优先级是120，对应nice值为0；

- nice值范围：-20~19，对应优先级100~139；
- 只有内核线程支持低于100的优先级，优先级低于100的线程称为RT级线程；
- SCHED_NORMAL调度策略为CFS，为默认调度策略，完全公平调度，没有优先级的概念；
- SCHED_FIFO、SCHED_RR为实时调度策略，优先级范围为1~99；