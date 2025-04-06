# Linux arm启动过程：

### 1、启动时建立临时页表：

PHYS_OFFSET：物理内存起始地址

PAGE_OFFSET：内核虚拟地址空间起始地址，默认0xC0000000

```c
#ifdef CONFIG_ARM_PATCH_PHYS_VIRT    // 内核根据实际所在地址调整PHYS_OFFSET的值
        bl      __fixup_pv_table     // 会将计算出的PHYS_OFFSET存在r8中
#endif
```



```c
	...
    /*
     * PLAT_PHYS_OFFSET：内存起始物理地址
     *     #define PLAT_PHYS_OFFSET     UL(CONFIG_PHYS_OFFSET)
     */
	ldr     r8, =PLAT_PHYS_OFFSET	//@ always constant in this case
    ...
__create_page_tables:
	/*
	 * r8 = PHYS_OFFSET, 内存起始物理地址
	 * TEXT_OFFSET：内核镜像起始地址相对内存起始地址的偏移
	 * PG_DIR_SIZE：L1页表大小（16K）
	 * r4 = r8 + TEXT_OFFSET - PG_DIR_SIZE, 临时页表起始物理地址，内核镜像前16K空间
	 */
    pgtbl   r4, r8	//@ page table address
	/*
	 * 后续代码为将临时页表项清零
	 */
```

启动时页表放在内核镜像前16K的物理地址空间：

起始：PHYS_OFFSET + TEXT_OFFSET - PG_DIR_SIZE

终止：PHYS_OFFSET + TEXT_OFFSET

PHYS_OFFSET：内存起始地址





开启MMU后，将内核虚拟地址0xC0000000映射到phys_offset

```c
#define PAGE_SHIFT  12
// 物理内存起始地址：
#define PHYS_OFFSET((phys_addr_t)__pv_phys_pfn_offset << PAGE_SHIFT)

//内核虚拟地址起始空间：0xC0000000
#define PAGE_OFFSET UL(CONFIG_PAGE_OFFSET)
```



CONFIG_ARM_PATCH_PHYS_VIRT



## 2、Arm寄存器：

ELR：
	Exception Link Registers，当产生一个下陷到ELx的异常时，保存异常返回时的地址（eret指令跳转的地址）
	ELR_EL1、ELR_EL2、ELR_EL3
FAR：
	FAR_ELx，产生异常的虚拟地址，Faulting virtual Address Register (P2484)
	当产生以下异常时：
		指令终止异常
		数据终止异常
		CP对齐错误异常
		观察点异常
ESR=1fe00000 (EC=0x7, IL=0x1, ISS=0xe00000)
	ESR_ELx，Exception Syndrome Register (1,2,3)，异常综合寄存器
	EC：bit[31:26]，异常类型
		0x0
		0x1
		0x3
		0x4
		0x5
		0x6
		0x7：SVE访问、高级SIMD、浮点功能
		0xa
	IL：bit[25]，指令长度(0:16, 1:32)
	ISS：bit[24:0]，异常综合域

SVE：Scalable Vector Extension，可扩展矢量指令（单指令多数据）
SPSR；SPSR_ELx(1,2,3)，Saved Program Status Register，保存的程序状态寄存器

Arm运行模式：9种
User用户模式、FIQ快速中断、IRQ普通中断、SVC超级管理模式、Data Abort数据终止、Instructure Abort指令终止、Sys系统模式、Mon监视模式、Hyp超级监视模式

TPIDR：软件线程ID寄存器

​	TPIDR_EL0：EL0读写软件线程ID寄存器

​	TPIDR_EL1：EL1软件线程ID寄存器

​	TPIDR_EL2：EL2软件线程ID寄存器

​	TPIDR_EL3：EL3软件线程ID寄存器

### 1）、通用寄存器：
```c
//32个
x0-x7                  //参数寄存器，多余参数通过栈传递；x0：存储返回值
FP(x29)                //栈顶指针
LR(x30)                //链接寄存器，保存函数返回位置
SP(x31)                //栈底指针
    //SP对应的物理寄存器有4个，默认对应EL级别使用对应寄存器，4个异常级别也都可以访问SP_EL0
    SP_EL0
    SP_EL1
    SP_EL2
    SP_EL3
PC                     //程序计数器
```

### 2）、xx寄存器：

```c

```



