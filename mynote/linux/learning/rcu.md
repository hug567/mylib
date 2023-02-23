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
* 宽限期：Grace Period
* 指所有线程都至少一次进入静默态的时间。
  * 宽限期前所有在读者临界区的读者在宽限区后都会结束；
  * 不同的宽限期可能有部分或全部重叠‘
  * 宽限期后， 宽限期开始前的所有读者都完成读操作；
* RCU类型：
  * 经典RCU
  * 可睡眠RCU
  * 微型RCU：用于单核系统，CONFIG_

* 常见缩写：

```c
gp: grace perid, 宽限期
gps: grace perid start, 宽限期开始
gp_seq: grace period sequence, 宽限期序列
qs: quiescent state, 静止状态
rdp: rcu_data pointer, rcu_data指针
iw: irq work
```

# 2、主要接口：

```c
/*
 * 描述RCU全局状态，组织树状层次结构
 * 支持不同类型的RCU状态：rcu_sched_state，rcu_bh_state，rcu_preempt_state
 * 全局变量，只有一个
 */
struct rcu_state

/*
 * Tree TCU中的节点
 */
struct rcu_node


/*
 * 每个cpu对应一个
 * 描述cpu的rcu状态，每个CPU都维护一个rcu_data，归属于某一个rcu_node
 * 用于检测静止状态并进行处理，对应得CPU进行RCU回调
 */
struct rcu_data

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
struct rcu_data {
	unsigned long grpmask; /* Mask to apply to leaf qsmask. */
}

```

# 4、典型日志：

```bash
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
#   0/1: 是否嵌套
#   b: rcu读临界区被抢占
#   .: 
#   .: 
#   l: 
[ 2077.394277] rcu:         Tasks blocked on leve-0 rcu_node (CPUs 0-10): P3744/1:b..l
```
