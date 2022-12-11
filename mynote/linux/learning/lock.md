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

### 6、读写信号量：rwsem

* 读写锁的睡眠不会被信号打断；

* 能清晰区别读写操作时再使用读写信号量；
  
  ```c
  struct rw_semaphore
  down_read / up_read
  down_write / up_write
  downgrade_write    //可动态地将获取的写锁转换为读锁
  ```

### 7、互斥锁：mutex

* 互斥锁同一时刻只能被一个线程持有；

* 必须在同一上下文中持锁和放锁；

* 不能递归地持有同一个锁，也不能释放一个已释放的锁；

* 进程持有互斥锁时，不能退出；

* 互斥锁不能在中断上半部和下半部使用；
  
  ```c
  mutex_lock / mutex_unlock
  mutex_trylock
  mutex_is_locked
  ```

* 相对于信号量，应优先使用互斥锁；
  
  ### 8、完成变量：completion

* 两个任务间的简单同步，一个任务发出信号通知另一个任务某个特定事件；

```c
init_completion
wait_for_completion
completion
```

### 9、大内核锁：BLK

* BLK是一个全局自旋锁，目前linux中已不再推荐使用；

### 10、顺序锁：seqlock

* 顺序锁优先保证写者可用，适用于多个读者和少数写者的场景，写优先于读，不希望读者让写者饥饿；

* 读锁被获取的情况下，写锁仍然能被获取；

* 顺序锁读前后可检查序列值，若前后值不一致，表示读期间有写操作，则需要继续读，直到读前后序列值一致；

* 典型的场景是jiffies的读取与更新；
  
  ```c
  write_seqlock / write_sequnlock
  read_seqbegin / read_seqretry 
  ```

### 11、禁止抢占：

* 一个自旋锁被持有，内核便不能进行抢占，但其他锁可被抢占；

* 一个进程持有非自旋锁进入临界区，但被抢占调度另一个任务，若新任务也进入临界区修改数据，则产生并发问题；

* 为避免抢占带来的问题，可关闭内核抢占；
  
  ```c
  preempt_disable / preempt_enable
  ```

* 关抢占可嵌套调用，可调用多次，但每个disable需对应一个enable，且最后一次enable后，内核抢占才重新启用；

### 12、顺序和屏障：barrier

* 编译器和处理器为提高效率，可能对代码执行顺序重新排序，有可能产业与预期不一样的结果；

* 可使用编译器属性或指令通知编译器或处理器，不对代码做重新排序，跑着代码的执行顺序；
  
  ```c
  rmb / wmb / mb / read_barrier_depends
  smp_rmb / smp_wmb / smp_mb / smp_read_barrier_depends
  barrier    //组织编译器重排代码执行顺序
  ```

### 13、读-复制-更新：RCU

* 可看做是读写自旋锁的扩展，RCU中读者和写者可并发执行，同一时刻允许多个线程同时读，和一个线程写；

* 主要针对的数据结构是链表，提高遍历读的效率；
  
  ```c
  rcu_read_lock / rcu_read_unlock
  synchronize_rcu
  rcu_assign_pointer / rcu_dereference
  ```

### 14、每CPU变量：

* 定义的时变量数组，每个cpu均有一个此变量的拷贝；

* 每CPU变量不需要加锁保护，但应在禁止抢占的情况下访问每CPU变量；
  
  ```c
  DEFINE_PER_CPU(type, name)
  alloc_percpu(type) / free_percpu(p)
  per_cpu(name, cpu)
  get_cpu_var(name)
  put_cpu_var(name)
  per_cpu_ptr(p, cpu)
  ```