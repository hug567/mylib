# 1、linux软中断：

* 内核提供的一种延迟执行机制，完全由软件触发，与普通进程相比，能得到更快的响应时间；

* 软中断资源是有限的，内核中是静态实现的各类软中断，目前有：
  
  ```bash
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
  
  ```bash
  
  ```

# 2、屏蔽软中断：

```bash
local_bh_disable
local_bh_enable
```
