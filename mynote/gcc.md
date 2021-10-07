## 1、gdb调试：
---
### 1）、基本操作
```c
gcc -g hello.c -o a.out      //编译可调式文件
gdb a.out  //启动调试
l / list    //查看源码，默认10行，按Enter继续查看
r / run  //运行至断点或结束
b / break <n>  //在第n行设置断点
s / step
n / next
c / continue
print <var>  //查看变量值
whatis <var>  //查看变量类型
q / quit  //推出gdb
```
### 2）、设置断点：
```c
info b(breakpoints)  //显示所有断点
b(break) m  //在第m行设置断点
clear m  //清除第m行的断点
b(break) func  //在函数func入口处设置断点
delete n  //删除第n个断点
delete breakpoints  //删除所有断点
disable n  //暂停第n个断点
enable n  //开启第n个断点
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

