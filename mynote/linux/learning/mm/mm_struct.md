# 内存描述符

## 1、task_struct中的内存描述符：

```c
struct task_struct {
    /*
     * 用户线程：mm == active_mm == 0xffff000012345678
     * 内核线程：
     *     mm == NULL
     *     正在运行：
     *         active_mm == 上个进程的mm，内核线程没有独立的地址空间，通过active_mm保存上一个进程的mm_struct，是为了进程做user1 -> kernel -> user1的切换时，可以避免切换用户地址空间，避免清TLB
     *     未在运行：
     *        active_mm == NULL
     */
    struct mm_struct *mm;
    struct mm_struct *active_mm;
};

struct mm_struct{
    struct {
        pgd_t *pgd;  //存储页全局目录的内存的虚址，virt_to_phys(pgd)可获取pgd物理地址
    } __randomize_layout;
};

struct vm_area_struct
```

## 1）、ttbr1_el1：

- 访问内核空间虚拟地址时，mmu自动从ttbr1_el1中存储的页表中翻译物理地址；

```c
//arch/arm64/kernel/head.S
__primary_switch
    adrp x1, init_pg_dir
    __enable_mmu
    	msr ttbr1_el1, x1                   // load TTBR1

secondary_startup
    adrp x1, swapper_pg_dir
    __enable_mmu
	    msr ttbr1_el1, x1                   // load TTBR1
```

## 2）、地址空间切换：

```c
switch_mm()  //arch/arm64/include/asm/mmu_context.h
    if (prev != next)
        __switch_mm(next);
			check_and_switch_context(next);

copy_mm()
    dup_mm()
    	mm = allocate_mm();
		memcpy(mm, oldmm, sizeof(*mm));
```

# 2、常见缩写：

```bash
pfn：page frame number，页帧号（物理内存区域编号）；物理地址x，页对齐，其页帧号为(x>>PAGE_SHIFT)
pte：page table entry，页表项
lm：linear map，线性映射
kasan：Kernel Address Sanitizer，内核地址消毒器
```

# 3、内存布局举例：

```bash
# 查看物理内存布局
cat /proc/iomem
# 查看进程用户空间内存布局
cat /proc/<pid>/maps
# 4级页表
pgd -> pud -> pmd -> pte -> va[11:0]
```

- aarch64，48位虚址，4k页，4级页表：

```bash
       Start            End         Size   Use
 ------------------------------------------------
 0000000000000000 0000ffffffffffff  256TB  user
 ffff000000000000 ffffffffffffffff  256TB  kernel
```

- 常见变量：

```c
#define VA_BITS           (CONFIG_ARM64_VA_BITS)  //48
#define VA_BITS_MIN       (VA_BITS)  //48
#define PAGE_SHIFT        CONFIG_ARM64_PAGE_SHIFT  //12
#define _PAGE_OFFSET(va)  (-(UL(1) << (va)))
/* 系统启动时，会将启动物理地址 PHYS_OFFSET 映射到内核起始虚拟地址 PAGE_OFFSET */
#define PAGE_OFFSET       (_PAGE_OFFSET(VA_BITS))  //(-(1UL << 48))=0xffff,0000,0000,0000，内核起始虚址
#define _PAGE_END(va)     (-(UL(1) << ((va) - 1)))  //-(1UL << (48 - 1)) = 0xffff,8000,0000,0000
#define PAGE_END          (_PAGE_END(vabits_actual))  //0xffff,8000,0000,0000
#define PHYS_OFFSET       ({ VM_BUG_ON(memstart_addr & 1); memstart_addr; })  //0x4000,0000, 起始物理地址
#define PHYS_PFN_OFFSET   (PHYS_OFFSET >> PAGE_SHIFT)  //0x4,0000
#define PAGE_SIZE         (_AC(1, UL) << PAGE_SHIFT)  //0x1000
#define PAGE_MASK         (~(PAGE_SIZE-1))  //0xffff,ffff,ffff,f000
#define PGDIR_SHIFT       ARM64_HW_PGTABLE_LEVEL_SHIFT(4 - CONFIG_PGTABLE_LEVELS)  //39，虚址中pgd索引的偏移位数，bit[39,47]
#define PTRS_PER_PGD      (1 << (VA_BITS - PGDIR_SHIFT))  //0x200=512，一个pgd页能存储的pud项数
#define TASK_SIZE_64      (UL(1) << vabits_actual)
#define TASK_SIZE         TASK_SIZE_64  //0x0001,0000,0000,0000，用户地址空间大小

// vabits_actual = 48
// memstart_addr = 0x4000,0000
// kimage_vaddr = 0xffff,8000,1000,0000
// kimage_voffset = 0xffff,7fff,cfe0,0000
// vmemmap = 0xffff,fdff,fee0,0000
swapper_pg_dir = 0xffffffc008e82000  //kernel image mapping初始阶段使用的页表
init_pg_dir = 0xffffffc009490000
init_pg_end = 0xffffffc009492000
idmap_pg_dir
idmap_pg_end
```

## 1）、用户空间：

```bash
       Start            End         Size           Use
 -------------------------------------------------------------------
随机预留
.text
.data
.bss
heap
mm->mmap_base
stack 
```

- 顶端：TASK_SIZE - 1，即0x0000,ffff,ffff,ffff；

## 2）、内核空间：

- 划分举例：

```bash
       Start            End         Size           Use
 -------------------------------------------------------------------
ffff000000000000 ffff7fffffffffff   128TB  kernel logical memory map
ffff800000000000 ffff800000000000    32TB  kasan shadow region
ffff800000000000 ffff800008000000   128MB  bpf jit region
ffff800008000000 ffff800010000000   128MB  modules
ffff800010000000 fffffdffbfff0000   ~93TB  vmalloc
fffffdffbfff0000 fffffdfffe5f8fff  ~998MB  [guard region]
fffffdfffe5f9000 fffffdfffe9fffff  4124KB  fixed mappings
fffffdfffea00000 fffffdfffebfffff     2MB  [guard region]
fffffdfffec00000 fffffdffffc00000    16MB  PCI I/O space
fffffdffffc00000 fffffdffffdfffff     2MB  [guard region]
fffffdffffe00000 ffffffffffe00000     2TB  vmemmap
ffffffffffe00000 ffffffffffffffff     2MB  [guard region]
```

- kernel logical memory map：线性映射区(linear map, lm)，VA和PA可以通过线性关系转换，此段的物理地址连续，kmalloc()分配的是此段地址；

```c
__is_lm_address(addr)
```

- kasan shadow region：kasan使用的内存，总内存的1/8，主要用于检测内存访问越界和UAF；

```c
#ifdef CONFIG_KASAN
#define KASAN_SHADOW_OFFSET     _AC(CONFIG_KASAN_SHADOW_OFFSET, UL)
#define KASAN_SHADOW_END        ((UL(1) << (64 - KASAN_SHADOW_SCALE_SHIFT)) \
                                        + KASAN_SHADOW_OFFSET)  //
#define KASAN_THREAD_SHIFT      1
#else
#define KASAN_THREAD_SHIFT      0
#define KASAN_SHADOW_END        (_PAGE_END(VA_BITS_MIN))  //0xffff,8000,0000,0000
#endif /* CONFIG_KASAN */
```

- bpf jit region：bpf just-in-time编译器使用；

```c
#define BPF_JIT_REGION_START    (KASAN_SHADOW_END)  //0xffff,8000,0000,0000
#define BPF_JIT_REGION_SIZE     (SZ_128M)  //0x800,0000
#define BPF_JIT_REGION_END      (BPF_JIT_REGION_START + BPF_JIT_REGION_SIZE)  //0xffff,8000,0800,0000
```

- modules：内核模块动态加载区域；

```c
#define MODULES_VADDR           (BPF_JIT_REGION_END)  //0xffff,8000,0800,0000
#define MODULES_VSIZE           (SZ_128M)  //0x800,0000
#define MODULES_END             (MODULES_VADDR + MODULES_VSIZE)  //0xffff,8000,1000,0000
```

- kimage：内核代码映射区
```c
#define KIMAGE_VADDR         (MODULES_END)  //xffff,8000,1000,0000
                             //kimage_vaddr = 0xffff,8000,1000,0000
#define KERNEL_START         _text  //内核镜像起始虚址, 0xffff,8000,1000,0000
#define KERNEL_END           _end  //内核镜像结束虚址, 0xffff,8000,120a,0000
```

- vmalloc：虚拟地址连续，但物理地址不一定连续；

```c
#define VMALLOC_START           (MODULES_END)  //0xffff,8000,1000,0000
#define VMALLOC_END             (- PUD_SIZE - VMEMMAP_SIZE - SZ_64K)  //0xffff,fdff,bfff,0000
                                //size: VMALLOC_END - VMALLOC_START = 0x7dff,afff,0000
```

- fixed mappings：固定映射区，系统启动时，内存管理还没使能，将此区域映射到物理内存上；

```c
#define FIXADDR_START   (FIXADDR_TOP - FIXADDR_SIZE)  //0xffff,fdff,fe5f,9000
#define FIXADDR_SIZE    (__end_of_permanent_fixed_addresses << PAGE_SHIFT)  //0x407000
#define FIXADDR_TOP     (PCI_IO_START - SZ_2M)  //0xffff,fdff,fea0,0000
```

- PCI I/O space：PCI总线使用；

```c
#define PCI_IO_START            (PCI_IO_END - PCI_IO_SIZE)  //0xffff,fdff,fec0,0000
#define PCI_IO_SIZE             SZ_16M  //0x100,0000
#define PCI_IO_END              (VMEMMAP_START - SZ_2M)  //0xfff,ffdf,fffc0,0000
```

- vmemmap：稀疏内存模型(NUMA)中用来存放所有struct page的虚拟地址空间；

```c
#define STRUCT_PAGE_MAX_SHIFT   (order_base_2(sizeof(struct page)))  //能够存储struct page空间大小的位移，如：6
                                                                     //sizeof(struct page) = 44
#define VMEMMAP_SIZE ((_PAGE_END(VA_BITS_MIN) - PAGE_OFFSET) \
                        >> (PAGE_SHIFT - STRUCT_PAGE_MAX_SHIFT))  //0x200,0000,0000
#define VMEMMAP_START           (-VMEMMAP_SIZE - SZ_2M)  //0xffff,fdff,ffe0,0000
#define VMEMMAP_END             (VMEMMAP_START + VMEMMAP_SIZE) //0xffff,ffff,ffe0,0000
```

#  4、内核内存空间：

```c
struct mm_struct init_mm = {
        .mm_rb          = RB_ROOT,
        .pgd            = swapper_pg_dir,
        .mm_users       = ATOMIC_INIT(2),
        .mm_count       = ATOMIC_INIT(1),
        .write_protect_seq = SEQCNT_ZERO(init_mm.write_protect_seq),
        MMAP_LOCK_INITIALIZER(init_mm)
        .page_table_lock =  __SPIN_LOCK_UNLOCKED(init_mm.page_table_lock),
        .arg_lock       =  __SPIN_LOCK_UNLOCKED(init_mm.arg_lock),
        .mmlist         = LIST_HEAD_INIT(init_mm.mmlist),
        .user_ns        = &init_user_ns,
        .cpu_bitmap     = CPU_BITS_NONE,
        INIT_MM_CONTEXT(init_mm)
};

#define INIT_MM_CONTEXT(name) .pgd = init_pg_dir,  //内核空间pgd虚址
```

