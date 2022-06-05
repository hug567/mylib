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













