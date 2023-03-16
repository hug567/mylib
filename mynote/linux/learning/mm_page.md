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