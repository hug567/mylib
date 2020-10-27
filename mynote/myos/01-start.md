## 第1天 从计算机结构到汇编程序入门

### 1、编辑二进制文件

```C
sudo apt install hexedit                                 //安装hexedit
man hexedit                                              //查看手册

touch <filename>                                         //创建文件
hexedit <filename>                                       //打开文件
hexedit --linelength 16 <filename>                       //打开文件时指定列宽
F1                                                       //帮助
F2                                                       //保存
Ctrl + X                                                 //保存并退出
F7                                                       //复制
F8                                                       //粘贴
```

### 2、操作系统启动过程：
1）、BIOS将引导扇区Boot程序加载至0x7C00处并执行；
2)、Boot程序读取活动分区的引导扇区代码；
3）、活动分区的加载程序读取文件系统里的系统加载程序；

### 3、制作启动Image命令：
```c
dd if=/dev/zero of=bin/ucore.img count=10000
dd if=bin/bootblock of=ucore.img conv=notrunc
dd if=bin/kernel of=ucore.img seek=1 conv=notrunc
```