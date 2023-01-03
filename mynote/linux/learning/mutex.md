# 1、mutex特性：

* 需要由持锁者释放锁；
* 临界区允许睡眠；
* 若mutex已被其他线程持有，当前线程想持锁时，会根据持锁线程是否在运行，决定自身是乐观自旋还是睡眠；
* mutex可选择支持是否乐观自旋：
  * A线程持锁，B线程请求锁，若此时发行A正在运行，则B可能自旋等待，不睡眠；
* PI：Priority Inheritance，优先级继承

# 2、定义：

```c
struct mutex {
    atomic_long_t    owner;       //记录锁的持有者的task_struct地址，低3bit记录锁的状态，为空表示锁未被持有
    struct list_head wait_list;   //等待链表，等锁进程会被记录在此list上
    spinlock_t       wait_lock;   //保护wait_list链表
    .....
};

owner:
  bit[63:3]：记录持锁线程task_struct地址
  bit[2:1]：用于实现handoff基址
  bit[0]：表示wait_list是否为空
```
