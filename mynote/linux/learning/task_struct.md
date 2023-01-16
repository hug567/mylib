# 1、task_struct

```c
struct thread_info thread_info;
int on_cpu;    //正在cpu上运行
int cpu;
int recent_use_cpu;
int wake_cpu;
int on_rq;
int nr_cpus_allowed;
cpumask_t cpus_mask;
unsigned int migration_disabled;  //禁止迁移，0：不禁止；>0：禁止
unsigned short migration_flags;
struct sched_info sched_info;
union {
        refcount_t              rcu_users;
        struct rcu_head         rcu;
};

#ifdef CONFIG_LOCKDEP
# define MAX_LOCK_DEPTH                 48UL
        u64                             curr_chain_key;
        int                             lockdep_depth;                //锁的深度
        unsigned int                    lockdep_recursion;            //递归深度
        struct held_lock                held_locks[MAX_LOCK_DEPTH];   //持有的锁
#endif
```

# 2、thread_info

```c
preempt_count：记录当前任务所处的上下文状态
    bit[7:0]：抢占次数，PREEMPT_MASK=0xff
        preempt_disable时值加1，preempt_enable时减一，大于0时表示关闭调度
    bit[15:8]：软中断嵌套次数，SOFTIRQ_MASK=0xff00
      bit[8]：由于单个cpu不会嵌套软中断，用bit[8]表示当前是否处于软中断上下文
      bit[15:9]：表示禁用软中断的次数，调用一次local_bh_disable，值加1
    bit[19:16]：硬中断嵌套次数，HARDIRQ_MASK=0xf0000，大于0表示当前处于中断上下文
    bit[23:20]：NMI，不可屏蔽中断
    bit[31:24]：保留

在硬/软中断上下文，调度是关闭的，bit[7:0]大于0，不会发生进程切换；
```
