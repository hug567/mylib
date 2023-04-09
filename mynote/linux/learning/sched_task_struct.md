# 1、task_struct

```c
struct task_struct {
        struct thread_info thread_info;
        /* -1 unrunnable, 0 runnable, >0 stopped: */
        volatile long                   state;
    	/*
    	 * 0: task不在cpu上运行, finish_task()
         * 1: task正在cpu上运行, prepare_task()
         */
        int                             on_cpu;  //正在cpu上运行
        /* Current CPU: */
        unsigned int                    cpu;
        int recent_use_cpu;
        int wake_cpu;
    	/*
    	 * task_struct::on_rq states: 
    	 * #define TASK_ON_RQ_QUEUED       1
    	 * #define TASK_ON_RQ_MIGRATING    2
    	 */
        int                             on_rq;
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

        #ifdef CONFIG_PREEMPT_RCU
                int                             rcu_read_lock_nesting;        //rcu读者是否嵌套
                union rcu_special               rcu_read_unlock_special;
                struct list_head                rcu_node_entry;
                struct rcu_node                 *rcu_blocked_node;
        #endif
};
```

## 1）、state：

```c
struct task_struct {
        /* -1 unrunnable, 0 runnable, >0 stopped: */
        volatile long                   state;
};

/*
 * Task state bitmask. NOTE! These bits are also
 * encoded in fs/proc/array.c: get_task_state().
 *
 * We have two separate sets of flags: task->state
 * is about runnability, while task->exit_state are
 * about the task exiting. Confusing, but this way
 * modifying one set can't modify the other one by
 * mistake.
 */

/* Used in tsk->state: */
#define TASK_RUNNING                    0x0000
#define TASK_INTERRUPTIBLE              0x0001
#define TASK_UNINTERRUPTIBLE            0x0002
#define __TASK_STOPPED                  0x0004
#define __TASK_TRACED                   0x0008
/* Used in tsk->exit_state: */
#define EXIT_DEAD                       0x0010
#define EXIT_ZOMBIE                     0x0020
#define EXIT_TRACE                      (EXIT_ZOMBIE | EXIT_DEAD)
/* Used in tsk->state again: */
#define TASK_PARKED                     0x0040
#define TASK_DEAD                       0x0080
#define TASK_WAKEKILL                   0x0100
#define TASK_WAKING                     0x0200
#define TASK_NOLOAD                     0x0400
#define TASK_NEW                        0x0800
#define TASK_STATE_MAX                  0x1000

/* Convenience macros for the sake of set_current_state: */
#define TASK_KILLABLE                   (TASK_WAKEKILL | TASK_UNINTERRUPTIBLE)
#define TASK_STOPPED                    (TASK_WAKEKILL | __TASK_STOPPED)
#define TASK_TRACED                     (TASK_WAKEKILL | __TASK_TRACED)

#define TASK_IDLE                       (TASK_UNINTERRUPTIBLE | TASK_NOLOAD)

/* Convenience macros for the sake of wake_up(): */
#define TASK_NORMAL                     (TASK_INTERRUPTIBLE | TASK_UNINTERRUPTIBLE)

/* get_task_state(): */
#define TASK_REPORT                     (TASK_RUNNING | TASK_INTERRUPTIBLE | \
                                         TASK_UNINTERRUPTIBLE | __TASK_STOPPED | \
                                         __TASK_TRACED | EXIT_DEAD | EXIT_ZOMBIE | \
                                         TASK_PARKED)
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
