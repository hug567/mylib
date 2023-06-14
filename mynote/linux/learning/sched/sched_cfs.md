# 1、CFS：

- 每个cpu对应一个rq，每个rq对应一个cfs_rq，cfs_rq处理的单元是sched_entity，sched_entiy位于每个task_struct中；

```c
struct task_struct {
	struct sched_entity	se;
};

struct task_struct *p = container_of(se, struct taks_struct, se);
```

- 调度发生时，调度器从cfs_rq中选择vruntime最小的task运行；
- 若调度器选择了一个任务组，则继续从改调度组中选择vruntime最新的task；

```c
struct cfs_rq {
        struct load_weight      load;
        unsigned int            nr_running;  //当前cfs_rq中就绪任务数量（只有就绪的任务才会放到rq中）
        unsigned int            h_nr_running;  //组调度中所有子cfs_rq的nr_running之和
        unsigned int            idle_h_nr_running;  //idle进程数量（等于系统中处于空闲的cpu数量）

        u64                     exec_clock;  //cfs_rq当前task已经运行的vruntime
        u64                     min_vruntime;  //可分配给任务的最小vruntime
#ifndef CONFIG_64BIT
        u64                     min_vruntime_copy;
#endif

        struct rb_root_cached   tasks_timeline;

        /*
         * 'curr' points to currently running entity on this cfs_rq.
         * It is set to NULL otherwise (i.e when none are currently running).
         */
        struct sched_entity     *curr;
        struct sched_entity     *next;
        struct sched_entity     *last;
        struct sched_entity     *skip;

#ifdef  CONFIG_SCHED_DEBUG
        unsigned int            nr_spread_over;
#endif

#ifdef CONFIG_SMP
        /*
         * CFS load tracking
         */
        struct sched_avg        avg;
#ifndef CONFIG_64BIT
        u64                     load_last_update_time_copy;
#endif
        struct {
                raw_spinlock_t  lock ____cacheline_aligned;
                int             nr;
                unsigned long   load_avg;
                unsigned long   util_avg;
                unsigned long   runnable_avg;
        } removed;

#ifdef CONFIG_FAIR_GROUP_SCHED
        unsigned long           tg_load_avg_contrib;
        long                    propagate;
        long                    prop_runnable_sum;

        /*
         *   h_load = weight * f(tg)
         *
         * Where f(tg) is the recursive weight fraction assigned to
         * this group.
         */
        unsigned long           h_load;
        u64                     last_h_load_update;
        struct sched_entity     *h_load_next;
#endif /* CONFIG_FAIR_GROUP_SCHED */
#endif /* CONFIG_SMP */

#ifdef CONFIG_FAIR_GROUP_SCHED
        struct rq               *rq;    /* CPU runqueue to which this cfs_rq is attached */

        /*
         * leaf cfs_rqs are those that hold tasks (lowest schedulable entity in
         * a hierarchy). Non-leaf lrqs hold other higher schedulable entities
         * (like users, containers etc.)
         *
         * leaf_cfs_rq_list ties together list of leaf cfs_rq's in a CPU.
         * This list is used during load balance.
         */
        int                     on_list;
        struct list_head        leaf_cfs_rq_list;
        struct task_group       *tg;    /* group that "owns" this runqueue */

#ifdef CONFIG_CFS_BANDWIDTH
        int                     runtime_enabled;
        s64                     runtime_remaining;

        u64                     throttled_clock;
        u64                     throttled_clock_pelt;
        u64                     throttled_clock_pelt_time;
        int                     throttled;
        int                     throttle_count;
        struct list_head        throttled_list;
#endif /* CONFIG_CFS_BANDWIDTH */
#endif /* CONFIG_FAIR_GROUP_SCHED */
};

struct load_weight {
        unsigned long                   weight;
        u32                             inv_weight;
};
```

# 2、vruntime：

- 每个进程都有一个vruntime值，表示进程已运行的虚拟时间；
- cfs根据进程vruntime值进行调度，进程vruntime越小，表示其优先级越高；
- cfs红黑树以进程vruntime为键值排序，调度时从红黑树选择vruntime最小的进程进度调度；