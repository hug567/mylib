## 第1天 从计算机结构到汇编程序入门

### 1、操作系统启动过程：
1）、BIOS将引导扇区Boot程序加载至0x7C00处并执行；
2)、Boot程序读取活动分区的引导扇区代码；
3）、活动分区的加载程序读取文件系统里的系统加载程序；

### 2、制作启动Image命令：
```c
dd if=/dev/zero of=bin/ucore.img count=10000
dd if=bin/bootblock of=ucore.img conv=notrunc
dd if=bin/kernel of=ucore.img seek=1 conv=notrunc
```