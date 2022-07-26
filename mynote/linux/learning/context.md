## 1、CPU上下文：



## 2、上下文切换类型：

### 1）、 用户空间和内核空间切换；

* 用户进程：

  不同进程用户态地址空间不同(mm=active_mm)，但共享同一个内核地址空间()；

  每个用户进程拥有自己的用户栈和内核栈；

* 内核线程：

  只有内核态地址空间(active_mm)，没有用户态地址空间(mm=NULL)，共享同一个内核地址空间()；

### 2）、进程上下文和中断上下文切换；
### 3）、不同进程间切换 (context_switch)；

* 切换地址空间(页表) (switch_mm)；
* 切换寄存器和栈空间 (switch_to)；

## 3、用户空间和内核空间切换：



## 4、ARM64系统调用：

将系统调用号写入x8寄存器，然后执行svc发起同步异常，中断向量表中同步异常处理入口为：

```c
SYM_CODE_START(vectors)
    ......
    kernel_ventry	0, sync				// Synchronous 64-bit EL0


SYM_CODE_START_LOCAL_NOALIGN(el0_sync)
    ......
	bl	el0_sync_handler                // el0_sync 处理函数

asmlinkage void noinstr el0_sync_handler(struct pt_regs *regs)
{
    ......
    el0_svc(regs);
}



```

