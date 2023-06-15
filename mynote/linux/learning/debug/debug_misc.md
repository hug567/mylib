# linux调试技术：

## 1、kgdb



## 2、gdb

kdb / kdebug (补丁)

kdump

syslogd / rsyslogd

klogd

oops

ksymoops

kallsyms

内核调试配置选项

​	CONFIG_DEBUG_KERNEL

BUG_ON()

sysrq

ftrace (/sys/kernel/debug)

strace：跟踪进程的系统调用及收到的符号

ltrace：跟踪进程的动态库调用及收到的信号

内存调试工具：MEMWATCH、YAMD、Electric Fence、valgrind、Asan(AddressSanitizer)

codedump

## 3、展开宏：

- 先成功编一遍内核，再在想展开的文件中添加：

```c
#error xxx
```

- 再用-j1编译内核，并开启V=1

```bash
make -C ../ O=`pwd` ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- V=1 -j1
```

- 复制编译命令，修改编译-c为预编译-E，删除文件中的#error，并重新执行修改后的命令：

```bash
# 编译命令：
gcc -c -o main.o main.c
# 修改为预编译：
gcc -E -o main.i main.c
```

