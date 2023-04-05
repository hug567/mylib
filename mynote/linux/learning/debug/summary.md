# 1、常见问题：

- rcu stall：21s未释放rcu read lock，rcu_preempt进程主动调用panic()；

- task hung：进程处于D状态超过120s，khungtaskd进程主动调用panic()；

- Unable to handle kernel paging request at virtual address；



# 2、rcu stall：

- stall的进程处于R状态：当前进程可运行，可能是没有正常进入rq，尝试在stall前调用wake_up_process()主动唤醒；



# 3、task hung：

- 调用wait_xxx()相关接口后，未调用对应的wakeup_xxx()，或wakeup未生效，可能是并发调了2次wakeup，但只生效了一次；



# 4、va fault：

- 未加锁，并发方位导致的UAF；
- 在结构体的成员全赋值好后，再加入全局资源，否则已加入全局资源，成员没准备好，又没有锁保护，有可能在此过程中被其他进程抢占，从而方位到未初始化完全的资源，导致方位地址异常；