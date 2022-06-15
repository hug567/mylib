## 1、MMU：

* Memory Management Unit，内存管理单元，负责将虚拟地址转换成物理地址；
* 页：管理虚址的单元，支持的大小有：16M、1M、64K、4K；
* 页帧(页框)：管理物理地址的单元，支持的大小有：64K、4K；
* 页表：存放虚拟地址到物理地址的对应关系；
* 页表项：页表中的一条；
* TLB：Translation Lookaside Buffer，MMU中cache，缓存页表项；

## 2、MMU初始化：

* 建立内核一级页表；

  ```c
  //arch/arm64/kernel/head.S
  __create_page_tables
  ```

* 写入TTB（CP15-CR2）；

* 使能MMU；

## 3、页表：

* 页表是软件实现的，但是页表的查找是MMU完成的，所以硬件定义了页表的实现规则，软件只可以选择页表的级数，是否使用huge page以及填充对应的权限标志位；

* 每个进程有独立的页表pgd，切换进程时，将该进程的页表基址写入TTBR寄存器；

  ```c
  struct task_struct {
      struct mm_struct *active_mm;
  };
  
  struct mm_struct {
      pgd_t *pgd;
  };
  ```

* 内核0号线程页表：

  ```c
  struct task_struct init_task {
      .active_mm = { /* struct mm_struct */
          .pgd = swapper_pg_dir,
      },
  };
  
  struct mm_struct 
  ```

  

## 4、Linux页表：

* PGD：Page Global Directory，页全局目录；

* P4D：Page 4th Directory，页4级目录；

* PUD：Page Upper Directory，页上层目录；

* PMD：Page Middle Directory，页中间目录；

* PT：Page Table ，直接页表（PTE：Page Table Entry：页表项）；

### 1）、页表配置：CONFIG_PGTABLE_LEVELS

* 5级页表：PGD、P4D、PUD、PMD、PT；
* 4级页表：PGD、PUD、PMD、PT；
* 3级页表：PGD、PMD、PT；
* 2级页表：PGD、PT；

### 2）、ARMv8页表：

* ARMv8支持2~4级页表，常用4级；

* ARMv8支持的虚拟地址位数：36(64G)、39(512G)、42(4T)、47(128T)，高位用于区分内核空间和用户空间，高位全1为内核地址空间，高位全0为用户地址空间；

* PAGE_SIZE：页表大小，默认4K，ARMv8支持的页面大小有：4K、16K、64K;

* PAGE_SHIFT：页表偏移；

## 5、进程页表：

* 内核加载进程后，通过pgd_alloc()、pud_alloc()、pmd_alloc()、pte_alloc()创建页表；