# 1、基本概念：

* Read-Copy Update，先创建一个旧数据的copy，然后写者更新这个copy，最后再用新的数据替换掉旧的数据。
* 代码：

```c
kernel/rcu/*
```

* 文档：

```c
Documentation/RCU/*
```

* 静止状态：Quiescent State

  * 当一个线程正在访问RCU保护的临界区时，认为是活动的状态，而当它离开了临界区后，则认为它是静止的状态；
  * 当所有的CPU都至少经历过一次QS后，宽限期将结束并触发回收工作；
  * 在时钟tick中检测CPU处于用户模式或者idle模式，则表明CPU离开了临界区；
  * 在不支持抢占的RCU实现中，检测到CPU有上下文切换，就能表明CPU离开了临界区；
* 强制静止状态：
  * 主动上报当前cpu已经历过禁止状态；
* 宽限期：Grace Period

  * 指所有线程都至少一次进入静默态的时间；
  * 宽限期前所有在读者临界区的读者在宽限区后都会结束；
  * 不同的宽限期可能有部分或全部重叠；
  * 宽限期后， 宽限期开始前的所有读者都完成读操作；
  * 同一时刻最多只有一个GP；
* 加速宽限期：
  * xx
* RCU类型：

  * 经典RCU
  * 可睡眠RCU
  * 微型RCU：用于单核系统，CONFIG_
* 常见缩写：

```bash
gp: grace perid, 宽限期
gps: grace perid start, 宽限期开始
gp_seq: grace period sequence, 宽限期序列
gpk: gp_kthread, 宽限期内核线程, rcu_preempt/13
qs: quiescent state, 静止状态
rnp: rcu_node pointer, rcu_node指针
rdp: rcu_data pointer, rcu_data指针
rtp: rcu_task pointer, rcu_task指针
iw: irq work
exp: expedited, 加速
```

- gp_kthread：宽限期内核线程，主要用于：

  - 1）创建新的宽限期；

  - 2）等待强制静止状态，设置超时，提前唤醒说明所有处理器经过了静止状态；

  - 3）宽限期结束处理。

    其中，前边两个操作都是通过睡眠等待在某个条件上。

    ```c
    t = kthread_create(rcu_gp_kthread, NULL, "%s", rcu_state.name);  //comm: rcu_preempt, pid: 13
    smp_store_release(&rcu_state.gp_kthread, t);
    ```
- 


# 2、主要接口：

```c
/*
 * 描述RCU全局状态，组织树状层次结构
 * 支持不同类型的RCU状态：rcu_sched_state，rcu_bh_state，rcu_preempt_state
 * 全局变量，只有一个实例
 */
struct rcu_state;

/*
 * Tree RCU中的节点，不与cpu一一对应
 * 一个rcu_node对应16个rcu_data
 */
struct rcu_node;

/*
 * 每个cpu对应一个
 * 描述cpu的rcu状态，每个CPU都维护一个rcu_data，归属于某一个rcu_node
 * 用于检测静止状态并进行处理，对应得CPU进行RCU回调
 */
struct rcu_data;

struct rcu_tasks;  //rcu任务状态机，kname: "rcu_tasks"

/*
 * 回调列表，嵌在其他数据结构中，synchronize_rcu时使用
 * #define rcu_head callback_head
 */
struct rcu_head;

// 读者
rcu_read_lock()
rcu_read_unlock()
// 写者
synchronize_rcu()/call_rcu()
rcu_assign_pointer()
rcu_dereference()
```

# 3、主要数据结构：

```c
struct rcu_state{
    /*
     * #define RCU_GP_FLAG_INIT 0x1     需要宽限期初始化
	 * #define RCU_GP_FLAG_FQS  0x2     需要宽限期强制静止状态
	 * #define RCU_GP_FLAG_OVLD 0x4     当前回调过载
     */
	short gp_flags;                 //宽限期任务标志

    /*
     * #define RCU_GP_IDLE      0      出事状态，不在宽限期中
     * #define RCU_GP_WAIT_GPS  1      等待宽限期初始化
     * #define RCU_GP_DONE_GPS  2      宽限期初始化完成
     * #define RCU_GP_ONOFF     3      宽限期初始化热插拔
     * #define RCU_GP_INIT      4      宽限期初始化
     * #define RCU_GP_CLEANED   8      宽限期清理完成
     * #define RCU_GP_WAIT_FQS  5      等待强制静止状态时刻
     * #define RCU_GP_DOING_FQS 6      强制静止状态完成
     * #define RCU_GP_CLEANUP   7      宽限期清理开始
     */
    short gp_state;                 //宽限期内核线程状态

    /*
	 * 低两位是当前宽限期状态：
     *   0：宽限期未开始，RCU处于idle
     *   1：处于宽限期中，低2为非0表示当前宽限期未结束
     *   2/3：有错误发生
     * rcu_node和rcu_data中也有名为gp_seq成员
     */
	unsigned long gp_seq;           //当前宽限期序列号
	unsigned long jiffies_stall;    //检查cpu将产生stall的未来时间点
	unsigned long gp_start;         //宽限期开始的节拍数
	unsigned long gp_end;           //上一个宽限期结束的节拍数
	unsigned long gp_activity;      //上一次宽限期线程活动的节拍数
	struct swait_queue_head gp_wq;  //宽限期任务等待队列
};

struct rcu_node {
	/*
	 * 阻塞在rcu读关键区的task，此head链接的是task->rcu_node_entry
	 * 如：list_add(&t->rcu_node_entry, &rnp->blkd_tasks);
	 */
	struct list_head blkd_tasks;
};

struct rcu_data {
	unsigned long grpmask; /* Mask to apply to leaf qsmask. */
};

```

# 4、典型日志：

```bash
pr_err("INFO: %s detected stalls on CPUs/tasks:\n", rcu_state.name);
# 检测到宽限期超时
[ 2077.394266] rcu: INFO: rcu_preempt detected stalls on CPUs/tasks:

pr_err("\tTasks blocked on level-%d rcu_node (CPUs %d-%d):",
	   rnp->level, rnp->grplo, rnp->grphi);
pr_cont(" P%d/%d:%c%c%c%c",
		t->pid, rscr.nesting,
		".b"[rscr.rs.b.blocked],
		".q"[rscr.rs.b.need_qs],
		".e"[rscr.rs.b.exp_hint],
		".l"[rscr.on_blkd_list]);
# level-0: 在树形rcu_node第0级阻塞
# CPUs 0-10: cpu编号0-10
# P3744/1:b..l:
#   P3744: 阻塞进程pid为3744
#   0/1: rcu是否嵌套
#   ./b: rcu读临界区是否被抢占(阻塞)
#   ./q: 是否需要静止状态
#   ./e: 是否有加速提示
#   ./l: 任务是否处于某一个rcu阻塞列表中
[ 2077.394277] rcu:         Tasks blocked on leve-0 rcu_node (CPUs 0-10): P3744/1:b..l

pr_cont("\t(detected by %d, t=%ld jiffies, g=%ld, q=%lu)\n",
        smp_processor_id(), (long)(jiffies - gps),
        (long)rcu_seq_current(&rcu_state.gp_seq), totqlen);
# 检查到rcu stall的cpu(当前所处的cpu)：5
# 现在距宽限期开始的节拍数：5252
# 当前宽限期序号：432473
# 当前所有cpu上rcu回调总数：22778
[ 2077.394288]         (detect by 5, t=5252 jiffies, g=432473, q=22778)
# 遍历树形rcu_node叶子节点，打印阻塞任务的调用栈
[ 2077.394293] task:dds_Par_1       state:R  running task     stack:    0 pid: 3744 ppid:  3105 flags:0x00000000

pr_err("%s kthread starved for %ld jiffies! g%ld f%#x %s(%d) ->state=%#lx ->cpu=%d\n",
       rcu_state.name, j,
       (long)rcu_seq_current(&rcu_state.gp_seq),
       data_race(rcu_state.gp_flags),
       gp_state_getname(rcu_state.gp_state), rcu_state.gp_state,
       gpk ? gpk->state : ~0, gpk ? task_cpu(gpk) : -1);
# rcu内核线程：rcu_preempt
# 饥饿节拍数：5250
# 当前宽限期序号：432473
# 宽限期任务标志：0x0
# 宽限期状态名称：RCU_GP_WAIT_FQS
# 宽限期状态：5
# 宽限期线程状态：0x402 (task->state)
# 宽限期线程所有cpu：8
[ 2077.394357] rcu: rcu_preempt kthread starved for 5250 jiffies! g432473 f0x0 RCU_GP_WAIT_FQS(5) ->state=0x402 ->cpu=8

pr_err("\tUnless %s kthread gets sufficient CPU time, OOM is now expected behavior.\n", rcu_state.name);
# rcu_preempt若未能获取充足的执行实现，OOM是预期的行为
[ 2077.394360] rcu:         Unless rcu_preempt kthread gets sufficient CPU time, OOM is now expected behavior.

pr_err("RCU grace-period kthread stack dump:\n");
# 将打印rcu宽限期线程调用栈
[ 2077.394362] task:rcu_preempt     state:I stac:   0 pid:   13 ppid:     2 flags:0x00000028

pr_err("\t%d-%c%c%c%c: (%lu %s) idle=%03x/%ld/%#lx softirq=%u/%u fqs=%ld %s%s\n",
       cpu,
       "O."[!!cpu_online(cpu)],
       "o."[!!(rdp->grpmask & rdp->mynode->qsmaskinit)],
       "N."[!!(rdp->grpmask & rdp->mynode->qsmaskinitnext)],
       !IS_ENABLED(CONFIG_IRQ_WORK) ? '?' :
                rdp->rcu_iw_pending ? (int)min(delta, 9UL) + '0' :
                        "!."[!delta],
       ticks_value, ticks_title,
       rcu_dynticks_snap(rdp) & 0xfff,
       rdp->dynticks_nesting, rdp->dynticks_nmi_nesting,
       rdp->softirq_snap, kstat_softirqs_cpu(RCU_SOFTIRQ, cpu),
       data_race(rcu_state.n_force_qs) - rcu_state.n_force_qs_gpstart,
       fast_no_hz,
       falsepositive ? " (false positive?)" : "");
# 1：当前所在cpu
# O/.：cpu是否在线
# o/.：
# N/.：
# !/.：
# fqs=0：当前宽限期强制静止状态数量
[ 3080.094350] rcu:		1-...!: (5250 ticks this GP) idle=69a/1/0x4000000000000002 softirq=0/0 fqs=0
```

# 5、宽限期经历过程：

```c
//宽限期线程
static int __init rcu_spawn_gp_kthread(void)
	t = kthread_create(rcu_gp_kthread, NULL, "%s", rcu_state.name);  //name: rcu_preempt

// 开始
static int __noreturn rcu_gp_kthread(void *unused)
    for (;;) {
        for (;;) {
            rcu_gp_init()
                record_gp_stall_check_time();
            		WRITE_ONCE(rcu_state.gp_start, j);

// 结束
static int __noreturn rcu_gp_kthread(void *unused)
	for (;;) {
		rcu_gp_cleanup();
			rcu_state.gp_end = jiffies;

//宽限期开始
trace_rcu_grace_period(rcu_state.name, rcu_state.gp_seq, TPS("start"));
//宽限期正在等待当前cpu，当前cpu需要静止状态
trace_rcu_grace_period(rcu_state.name, rnp->gp_seq, TPS("cpustart"));
//当前cpu宽限期结束
trace_rcu_grace_period(rcu_state.name, rdp->gp_seq, TPS("cpuend"));
//宽限期结束
trace_rcu_grace_period(rcu_state.name, rcu_state.gp_seq, TPS("end"));

```

# 6、rcu线程：

- rcu_preempt：
  - xx
- rcuc/%u：
  - per cpu线程，用于执行rcu回调

- rcu_gp：
  - 工作队列，
- rcu_par_gp：
  - 工作队列，
- rcu_tasks_kthred：
- rcu_tasks_rude_kthred：
- rcu_tasks_trace_kthred ：