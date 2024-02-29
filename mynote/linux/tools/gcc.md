## 1、gdb调试：
---
### 1）、基本操作
```bash
gcc -g hello.c -o a.out      # 编译可调式文件
gdb a.out                    # 启动调试
l / list                     # 查看源码，默认10行，按Enter继续查看
l <n>                        # 查看指定行号前后10行源码
l <func>                     # 查看函数源码
r / run                      # 运行至断点或结束
b / break <n>                # 在第n行设置断点
s / step                     # 单步调试，进入调用函数
n / next                     # 单步调试，不进入调用函数
c / continue                 # 继续运行至下一个断点或结束
until                        # 运行至退出循环
until <n>                    # 运行至指定行
finish                       # 运行至当前函数结束
print <var>                  # 查看变量值
whatis <var>                 # 查看变量类型
q / quit                     # 退出gdb
```
### 2）、设置断点：
```bash
info b(breakpoints)          # 显示所有断点
b(break) <m>                 # 在第m行设置断点
clear <m>                    # 清除第m行的断点
b(break) func                # 在函数func入口处设置断点
delete <n>                   # 删除第n个断点
delete breakpoints           # 删除所有断点
disable n                    # 暂停第n个断点
enable n                     # 开启第n个断点
```

### 3）、TUI界面：

```c
/* 进入tui界面： */
gdb --tui a.out
```

## 2、GCC预定义宏：

https://gcc.gnu.org/onlinedocs/gcc-5.1.0/cpp/Common-Predefined-Macros.html#Common-Predefined-Macros

```c
__GNUC__                       // 主版本号，7.3.1中的7
__GNUC_MINOR__                 // 此版本号，7.3.1中的3
__GNUC_PATCHLEVEL__            // 不定版本号，7.3.1中的1
```

## 3、gdb调试用户态程序：

### 1）、gdb远程调试开发板中的程序：

```bash
# 编译选项中添加-g
add_definitions(-Wall -g)

# 编译目标架构的gdbserver
petalinux-build -c gdb

# 目标板子中启动gdbserver
gdbserver :2345 log1server
```

