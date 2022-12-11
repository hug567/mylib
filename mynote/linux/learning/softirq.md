# 1、linux软中断：

* 内核提供的一种延迟执行机制，完全由软件触发，与普通进程相比，能得到更快的响应时间；
* 软中断资源是有限的，内核中是静态实现的各类软中断，目前有：

  ```c
  enum
  {
          HI_SOFTIRQ=0,
          TIMER_SOFTIRQ,
          NET_TX_SOFTIRQ,
          NET_RX_SOFTIRQ,
          BLOCK_SOFTIRQ,
          IRQ_POLL_SOFTIRQ,
          TASKLET_SOFTIRQ,
          SCHED_SOFTIRQ,
          HRTIMER_SOFTIRQ,
          RCU_SOFTIRQ,    /* Preferable RCU should always be the last softirq */

          NR_SOFTIRQS
  };
  ```
* 软中断的守护进程是ksoftirqd，大多数情况下，软中断都会在irq_exit阶段执行，在irq_exit阶段没有处理完的软中断，才有可能会在守护进程中执行；
* 触发软中断：

  ```c
  /* 
   * 设置当前cpu上的softirq的pending位
   * 1）、若处在中断上下文调用，设置pending位后就结束，退出中断时会处理softirq
   * 2）、若处在进程上下文调用，需唤醒ksoftirqd线程去处理softirq
   */
  void raise_softirq(unsigned int nr)
  ```
* 执行软中断：

  ```c
  /* 调用软中断的action钩子函数 */
  static inline void invoke_softirq(void)
  ```

# 2、屏蔽软中断：

```c
/* 通过修改preemt_count */
local_bh_disable：将preempt_count的bit[15:9]表示的禁用软中断次数+1，bit[15:9]大于0表示禁用软中断
local_bh_enable：将preempt_count的bit[15:9]表示的禁用软中断次数-1
```
