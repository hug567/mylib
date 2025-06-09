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
do_page_fault()  //arch/arm64/mm/fault.c
	__do_page_fault()
		handle_mm_fault()  //mm/memory.c
			__handle_mm_fault()
    			pgd = pgd_offset(mm, address);
				p4d = p4d_alloc(mm, pgd, address);  //linux默认使用4级页表，此时没有p4d
				vmf.pud = pud_alloc(mm, p4d, address);
					__pud_alloc()
                        pud_alloc_one()
                        p4d_populate()
                        	__p4d_populate()
                        		set_p4d()
				vmf.pmd = pmd_alloc(mm, vmf.pud, address);
					__pmd_alloc(mm, pud, address);
                        pmd_alloc_one(mm, address);
                        	pud_populate(mm, pud, new);
								__pud_populate();
									set_pud();
				handle_pte_fault(&vmf);
					do_fault(vmf);
						do_read_fault()
                            __do_fault()
                            finish_fault()
                            	pte_alloc()
                            		__pte_alloc()
                            			pte_alloc_one(mm);
											pmd_populate(mm, pmd, new);
												__pmd_populate()
                                                    set_pmd()
```

# 5、内核页表：

- swapper_pg_dir：内核pgd虚址，

```c
swapper_pg_dir   = KERNEL_RAM_VADDR-PG_DIR_SIZE
PAGE_OFFSET      = CONFIG_PAGE_OFFSET
init_pg_dir  //初始阶段页表，被放在内核镜像.bss段之后, 0xffff80000a08c000
#define INIT_DIR_SIZE (PAGE_SIZE * EARLY_PAGES(KIMAGE_VADDR, _end))  //初始阶段页表大小
init_pg_end  //0xffff80000a091000
    
idmap_pg_dir  //identity mapping，恒等映射，在mmu使能前，建立的物理地址和虚拟地址相等的映射
#define IDMAP_DIR_SIZE (IDMAP_PGTABLE_LEVELS * PAGE_SIZE)  //恒等映射页大小，0x3000=3*4k
```

- PAGE_OFFSET：内核空间和用户空间虚拟地址的空间的划分界限，如：0xffff,0000,0000,0000

- TEXT_OFFSET：编译内核时指定，表示内核代码起始的偏移

## 1）、起始阶段页表创建：

- 第一段：identity mapping，把物理地址mapping到物理地址上去，为打开mmu做准备；
- 第二段：kernel image mapping，将kernel running需要的地址（kernel txt、dernel rodata、data、bss等等）进行映射；
- 第三段：blob memory对应的mapping；

```c
//u-boot启动linux arm时，将dtb物理地址写入r2，传递给linux

// arm中，KERNEL_OFFSET：内核在虚拟地址空间中的起始位置，链接器使用这个地址作为起始地址链接代码，常用值如：0xC0000000 (3GB处)
// linux启动时，打开MMU前，直接操作物理地址；打开MMU后，临时创建恒等映射，通常将物理内存起始地址映射到虚拟地址KERNEL_OFFSET
// 注：物理内存起始可能时0，也可能不是0，如：0x800000000
//     映射后：物理地址 = 虚拟地址 - KERNEL_OFFSET
// 内核初始页表（swapper_pg_dir）将物理内存区域映射到 [KERNEL_OFFSET, KERNEL_OFFSET + RAM_SIZE] 的虚拟地址范围
#define KERNEL_OFFSET          (PAGE_OFFSET)

// PAGE_OFFSET：内核起始虚拟地址，通常与KERNEL_OFFSET等价
#define PAGE_OFFSET            UL(CONFIG_PAGE_OFFSET)

// PHYS_OFFSET：实际物理内存起始地址
#define PHYS_OFFSET     ((phys_addr_t)__pv_phys_pfn_offset << PAGE_SHIFT)

// TEXT_OFFSET：内核镜像在物理内存中的起始地址相当于PHYS_OFFSET的偏移
// arm中的定义：arch/arm/Makefile
textofs-y	:= 0x00008000
TEXT_OFFSET := $(textofs-y)

//已知虚拟地址，可计算出其物理地址：pa = va - PAGE_OFFSET + PHYS_OFFSET
```

- linux arm32启动阶段获取起始物理地址过程：

```c
//编译后查看_text符号地址：0xC0008000
arm-none-eabi-nm vmlinux | grep " _text"
readelf -s vmlinux | grep " _text"

//arch/arm/boot/compressed/Makefile
ZTEXTADDR       := $(CONFIG_ZBOOT_ROM_TEXT)                     //CONFIG_ZBOOT_ROM_TEXT=0x0
CPPFLAGS_vmlinux.lds := -DTEXT_START="$(ZTEXTADDR)" -DBSS_START="$(ZBSSADDR)"

//arch/arm/boot/compressed/vmlinux.lds.S
  . = TEXT_START;                                               //当前地址 = TEXT_START
  _text = .;                                                    //_text = 当前地址

  .text : {
    _start = .;
    *(.start)
    *(.text)
    *(.text.*)
    ARM_STUBS_TEXT
  }

// arch/arm/kernel/head.S
ENTRY(stext)
    adr_l   r8, _text  //adr_l：汇编命令宏封装，将符号_text运行时地址加载到r8中
    sub     r8, r8, #TEXT_OFFSET
    bl      __fixup_pv_table
ENDPROC(stext)

// arch/arm/kernel/phys2virt.S
ENTRY(__fixup_pv_table)
    mov     r0, r8, lsr #PAGE_SHIFT
    str_l   r0, __pv_phys_pfn_offset, r3  //str_l：汇编命令的宏封装，将r0寄存器的值写入变量__pv_phys_pfn_offset的地址中，r3是临时寄存器
ENDPROC(__fixup_pv_table)
```

# 6、调试文件：

```bash
/proc/iomem                           # 部分物理地址信息
/proc/buddyinfo                       # buddy各阶页帧信息
/proc/pagetypeinfo                    # 页帧分配状态
/proc/slabinfo                        # slab所有活动缓存的列表
/proc/sys/kernel/randomize_va_space   # 用户态进程地址空间随机化
```

