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

* EL0 -> EL1
    1)、svc (系统调用)
    2)、指令触发异常 (如：访存指令触发缺页异常)
    3)、中断

* 发生EL0->EL1特权级切换时：
    1)、触发异常的指令(PC指向)保存在ELR_EL1；
    2)、触发异常的原因保存在ESR_EL1；
    3)、栈指针从SP_EL0切换到SP_EL1；
    4)、CPU相关状态保存到SPSR_EL1，引发缺页异常的地址保存到FAR_EL1等；

* 切换后：
    CPU读取VBAR_EL1获取异常向量表；
    根据ESR_EL1中保存的异常原因，调用异常处理函数；
    异常处理函数先保存应用程序上下文，然后执行处理函数；
      保存上下文：将寄存器信息按pt_regs结构体值顺序压入栈中，并将栈顶指针作为pt_regs参数传入后续处理函数
    执行完后恢复应用程序上下文，然后调用eret指令；
      恢复向下文：将栈中存储的寄存器信息恢复到各寄存器中；

* 执行eret时：
    恢复CPU自动保存的EL0状态(PC、SP等)，并切回EL0，继续执行应用程序；

```c
/* arch/arm64/kernel/entry.S */
/* 定义中断向量表 */
ENTRY(vectors)
	kernel_ventry 0, sync
	......
END(vectors)
```