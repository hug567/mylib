# 1、页表：

```c
pgp_alloc
pud_alloc
pmd_alloc
pte_alloc

mk_pte(page, prot)
pfn_to_pte(pfn, prot)
page_to_pfn(page)
```

- 页表的使用者是mmu，cpu访问的是虚拟地址，访问时通过mmu查询物理地址；
- 基地址寄存器和各级页表中存储的都是物理地址；
- 如果需要修改页表，也需要页表所在的物理地址映射到虚拟地址，才能访问；
- 内核初始化后，会将物理内存线性映射，物理地址与虚拟地址见偏移为固定值；
- mm->pgd：pgd_t类型变量的地址，pgd_val(*mm->pgd);获取pgd_t的val，为pgd的物理地址(如：0x41889003)；
- 内核线程没有独立的进程地址空间，对应的task->mm = NULL；

# 2、struct page存储方式：

## 1）、CONFIG_FLATMEM：

- 物理地址空间是连续的；
- 所有的struct page存储在一个连续的数组mem_map中，每一项对应某个具体的物理页面；

## 2）、CONFIG_DISCONTIGMEM：

- 物理地址空间有空洞，不连续；
- 单个的连续物理地址空间作为一个node，按flat mem node管理；

## 3）、CONFIG_SPARSEMEM：

- 稀疏内存，支持内存热插拔；
- 物理地址空间按照SECTION被分成一段一段的，每个section都是可热插拔的，section内部地址连续；

## 4）、CONFIG_SPARSEMEM_VMEMMAP：

- struct page存储在vmemmap开始的连续虚址空间，通过页表关联实际的物理地址；

# 3、物理页：

```c
//页帧号偏移
#define ARCH_PFN_OFFSET     ((unsigned long)PHYS_PFN_OFFSET)
#define PHYS_PFN_OFFSET     (PHYS_OFFSET >> PAGE_SHIFT)  //0x4,0000
```

# 4、缺页异常：

```c
do_page_fault()
	__do_page_fault()
		handle_mm_fault()
			__handle_mm_fault()
				handle_pte_fault()
```

# 5、内核页表：

- swapper_pg_dir：内核pgd虚址，

```c
swapper_pg_dir   = KERNEL_RAM_VADDR-PG_DIR_SIZE
PAGE_OFFSET      = CONFIG_PAGE_OFFSET
```

- PAGE_OFFSET：内核空间和用户空间虚拟地址的空间的划分界限，如：0xffff,0000,0000,0000

- TEXT_OFFSET：编译内核时指定，表示内核代码起始的偏移