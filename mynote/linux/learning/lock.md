## 内核同步：

### 1、内核同步方法：

* 原子操作；
* 自旋锁；
* 读写自旋锁；
* 信号量；
* 读写信号量；
* 互斥体；
* 完成变量；
* 大内核锁；
* 顺序锁；
* 禁止抢占；
* 顺序和屏障；
* 读-复制-更新（RCU）；
* 每CPU变量；

### 2、原子操作：atomic_t

* 单指令读写数据，执行过程不可被打断；

* 内核提供针对整数或位操作的原子操作接口；

  ```c
  atomic_t
  atomic64_t
  ```

* 能通过原子操作实现代码逻辑的地方，尽量不要使用复杂的锁机制；

### 3、自旋锁：spin_lock

* 一个线程视图获取已被其他线程持有的锁，当前线程循环等待；

  ```c
  spin_lock / spin_unlock
  ```

* 自旋锁不应被长时间持有，适合短期内进行轻量级加锁；

* 自旋锁可以用在中断处理程序中，获取锁前，需禁止本地中断；

  ```c
  spin_lock_irqsave / spin_lock_irqrestore
  ```
  
* 由于中断上半部可抢占下半部(tasklet)，若上半部可下半部共享数据，下半部尝试持锁前，需禁止本地中断；
  
  ```c
  local_irq_save / local_irq_restore                //推荐使用,屏蔽时间不宜过长
  local_irq_disable / local_irq_enable
  disable_irq / enable_irq                          //禁止/使能指定中断线
  ```
  
* 由于中断下半部可抢占进程上下文，若下半部与进程上下文共享数据，进程上下文尝试持锁前，需禁止中断下半部；

  ```c
  local_bh_disable / local_bh_enable
  ```

* 由于同类tasklet不能同时运行，所以同类tasklet中的共享数据不需要保护；

* 若不同类型的tasklet共享数据，则需要添加自旋锁保护，但不需要禁止下半部，因为同一处理器上不会出现tasklet相互抢占；

* 若是多个软中断(soft irq)中共享数据，无论是否是同种类型，都需要锁保护，但不需要禁止下半部；

### 4、读写自旋锁：read_lock/write_lock

* 一个线程持有读锁，另一个线程也可以持有读锁；
* 一个线程持有了写锁，另一个线程不能持有读锁或写锁；
* 一个线程持有了读写，另一个线程不能持有写锁；
* 同一个线程，获取读锁后再获取写锁，将产生死锁；
* 若读和写不能清新得分开，不能使用读写锁；

```c
read_lock / read_unlock
read_lock_irq / read_unlock_irq
read_lock_irqsave / read_unlock_irqrestroe
write_lock / write_unlock
write_lock_irq / write_unlock_irq
write_lock_irqsave / write_unlock_irqrestroe
```

### 5、信号量：semaphore

* 信号量是一种睡眠锁，线程获取不到锁时，会进入睡眠，直到有信号量释放被唤醒；
* 信号量比自旋锁有更大的开销，适用于等待时间较长的临界区保护；
* 信号量只能用在进程上下文中，因为中断上下文不能进行调度；
* 进行持有信号量后，仍然可以进入睡眠，也可以被抢占；
* 占用信号量的同时，不能占用自旋锁，因为持有自旋锁时不允许睡眠；

```c
sema_init / init_MUTEX / DECLARE_MUTEX
down / down_interruptible / down_trylock
up
```




