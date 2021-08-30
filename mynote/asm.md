## 1、编译汇编：

```C
sudo apt install nasm                                    //安装nasm
nasm -v                                                  //查看nasm版本
nasm -f elf64 hello.asm                                  //编译
ld -s -o hello hello.o                                   //链接
./hello                                                  //运行可执行文件
```

## 2、ARM汇编：

```c
.global symbol    //声明符号对链接器可见
.extern symbol    //声明符号为外部符号，链接时从外部文件搜索符号
.section    //节
.text    //代码段
.data    //数据段，C语言中的全局变量
.incbin    //包含文件，不做任何变动
.align    //字节对齐，取值为2的幂
.type    //




```

## 3、常用指令：

### 3.1、跳转指令：

```c
b    //跳转指令
bl   //带返回的跳转指令，将PC寄存器的值保存到LR寄存器中
blx  //带返回和状态切换的跳转指令
bx   //带状态切换的跳转指令
```

### 3.2、数据处理指令：

```c
mov ra rb  ：将rb中存放的数据传送给ra，mov不能直接操作内存中的数据；
```

### 3.3、程序状态寄存器传输指令：

```c

```

### 3.4、内存访问指令：

```c
ldr / str命令：
ldr ra, [rb]  ：将rb寄存器指示的内存中的数据加载到ra；
ldr ra, [rb, #12]  ：将rb+12指示的内存中的数据加载到ra；
ldr ra, [rb], #12  ：将rb指示的内存中的数据加载到ra，然后执行rb=rb + 12；
ldr ra, [rb, rc]  ：将rb+rc指示的内存中的数据加载到ra；
str ra, [rb]  ：将ra中的数据存储rb寄存器指示的内存中；

ldr / str命令后缀：
b：从指定地址取1字节数据
h：从指定地址取2字节数据
w：从指定地址取4字节数据
x：从指定地址取8字节数据
s：进行指定字节的位扩展，配合上述4个扩展位使用

ldm / stm批量传输指令：
命令后缀：
i：increase，地址变化方向为增加
d：decrease，地址变化方向为减小
a：after，传送后增加地址值(i++)
b：before，传送前增加地址值(++i)
```

### 3.5、协处理器指令：

```c
cdp  协处理器数据操作指令
......
```

### 3.6、异常中断产生指令：

```c
swi  软中断指令
bkpt  断点中断指令
```

