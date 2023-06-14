# 1、spin_lock

- spin_lock / spin_unlock，持锁时关中断、关抢占；
- PREEMPT_RT内核中的spin lock可能被抢占

# 2、spin_lock_bh

## 2.1、普通实现：

* spin_lock_bh / spin_unlock_bh，禁止软中断和抢占，不禁止硬件中断；

```c
static __always_inline void spin_lock_bh(spinlock_t *lock)
{
        raw_spin_lock_bh(&lock->rlock);
}

#define raw_spin_lock_bh(lock)  _raw_spin_lock_bh(lock)

void __lockfunc _raw_spin_lock_bh(raw_spinlock_t *lock)
{
        __raw_spin_lock_bh(lock);
}

static inline void __raw_spin_lock_bh(raw_spinlock_t *lock)
{
        __local_bh_disable_ip(_RET_IP_, SOFTIRQ_LOCK_OFFSET);  //禁用软中断
        spin_acquire(&lock->dep_map, 0, 0, _RET_IP_);
        LOCK_CONTENDED(lock, do_raw_spin_trylock, do_raw_spin_lock);
}
```

## 2.2、RT内核实现：

* 只关软中断，可被抢占及硬件中断打断，但关闭了迁移；

```c
static __always_inline void spin_lock_bh(spinlock_t *lock)
{
        /* Investigate: Drop bh when blocking ? */
        local_bh_disable();  //禁用软中断
        rt_spin_lock(lock);
}

void __sched rt_spin_lock(spinlock_t *lock)
{
        spin_acquire(&lock->dep_map, 0, 0, _RET_IP_);
        __rt_spin_lock(lock);
}

static __always_inline void __rt_spin_lock(spinlock_t *lock)
{
        ___might_sleep(__FILE__, __LINE__, 0);
        rtlock_lock(&lock->lock);  //rt将spinlock映射到了rt_mutex_base
        rcu_read_lock();
        migrate_disable();
}
```

# 3、spin_lock_irq

* 禁止中断

# 4、spin_lock_irqsave

* 禁止中断
