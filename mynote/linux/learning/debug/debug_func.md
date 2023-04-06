# 1、常用kernel调试函数：
## 1.1、task：

```c
// include/linux/sched/signal.h
//系统中所有的进程都挂在init_task的tasks链表下，每个进程的线程挂在task_sturct->signal的链表下
for_each_process(p)
for_each_thread(p, t)
//遍历所有task
for_each_process_thread(p, t)
//遍历所有cpu
for_each_online_cpu(cpu)

//打印所有task调用栈
void show_state(void);
//打印所有处于指定状态的task的调用栈
void show_state_filter(unsigned int state_filter);
//打印指定cpu当前运行的task的调用栈
void dump_cpu_task(int cpu);
//打印当前task的调用栈
void show_stack(NULL, NULL, NULL);
//打印指定task的调用栈
void show_stack(task, NULL, NULL);
//打印指定task的调用栈
void sched_show_task(task)
//指定cpu正在运行的task
#define cpu_curr(cpu) (cpu_rq(cpu)->curr)
//task所在cpu
unsigned int task_cpu(const struct task_struct *p)
```

## 1.2、锁：

```c
//include/linux/debug_locks.h
//打印所有锁信息
void debug_show_all_locks(void)
//打印task持有的锁
void debug_show_held_locks(task)
//检查指定内存区域是否有锁
void debug_check_no_locks_freed(const void *mem_from, unsigned long mem_len)
//检查当前进程是否持有锁
void debug_check_no_locks_held(void)
// mutex是否被持有
bool mutex_is_locked(struct mutex *lock)
```

## 1.3、辅助函数：

```c
//判断addr是否是一个有效的内核虚拟地址
virt_addr_valid(addr)
```

# 2、调试文件：

```bash
# 调度信息
cat /proc/sched_debug > sched_debug.log
# 追踪日志
cat /sys/kernel/debug/tracing/trace > trace.log
```
