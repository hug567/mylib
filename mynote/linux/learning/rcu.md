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

* 静默状态：Quiescent State
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

# 2、主要接口：

```c
struct rcu_state
struct rcu_node
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