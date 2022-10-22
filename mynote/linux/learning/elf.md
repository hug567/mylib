## 1、链接脚本：

 作用：主要用于规定如何把输入文件内的section放入输出文件内, 并控制输出文件内各部分在程序地址空间内的布局。

```c
//查看默认链接脚本
ld --verbose
-T    //指定自定义链接脚本
```

```c
ENTRY(SYMBOL)             //将符号SYMBOL设为程序入口地址
INCLUDE filename          //包含名为filename的链接脚本，搜索路径由-L指定，最大深度为10
INPUT(files)              //文件files作为输入文件，搜索路径由-L指定，或由命令行-lfile指定
OUTPUT_ARCH(BFDARCH)      //设置输出文件的架构
SECTIONS{}                //描述section链接方式
```

## 2、elf基本信息：

segment：段，段是程序执行的必要组成部分，每个段中会有代码或数据被划分成不同的节；

section：节

linux链接脚本文件：include/asm-generic/vmlinux.lds.h, arch/arm64/kernel/vmlinux.lds.S

链接脚本中定义了个level的initcall符号的存储位置：

```c
__initcall_start
__initcallx_start  //x: 0-7
__initcall_end
```

