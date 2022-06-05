## 1、MMU：

* Memory Management Unit，内存管理单元，负责将虚拟地址转换成物理地址；
* 页：管理虚址的单元，支持的大小有：16M、1M、64K、4K；
* 页帧(页框)：管理物理地址的单元，支持的大小有：64K、4K；
* 页表：存放虚拟地址到物理地址的对应关系；
* 页表项：页表中的一条；
* TLB：Translation Lookaside Buffer，MMU中cache，缓存页表项；

## 2、MMU初始化：

* 建立一级页表；

  ```c
  //arch/arm64/kernel/head.S
  __create_page_tables
  ```

* 写入TTB（CP15-CR2）；

* 使能MMU；

