## 1、编译汇编：

```C
sudo apt install nasm                                    //安装nasm
nasm -v                                                  //查看nasm版本
nasm -f elf64 hello.asm                                  //编译
ld -s -o hello hello.o                                   //链接
./hello                                                  //运行可执行文件
```

## 2、ARM汇编：

### 1）、关键字：

```c
.global symbol    //声明符号对链接器可见
.extern symbol    //声明符号为外部符号，链接时从外部文件搜索符号
.section          //段
.text             //代码段
.data             //数据段，C语言中的全局变量
.incbin           //包含文件，不做任何变动
.align            //字节对齐，取值为2的幂
.type             //声明符号类型，function或object
```

* 自定义段： 以段名为开始，以下一个段名或者文件结尾为结束 

```c
.section section_name[,"flags"[,%type[,flag_specific_arguments]]] 

flag：a：可分配
      w：可写
      x：可执行

/*
 * 定义一个.start段，后面两个为参数
 * #alloc: 表示本段包含可分配数据
 * #execinstr: 表示本段是可执行段
 */
.section .start,#alloc,#execinstr
    
/* 指定符号_start类型为函数 */
.type _start, #function
```

### 2）、伪指令：

```c
adr r0, symbol    //获取标号symbol的地址，存储到r0中
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

#### 3.2.1、数据传送指令：

```c
mov ra rb  ：将rb中存放的数据传送给ra，mov不能直接操作内存中的数据；
```

#### 3.2.2、运算指令：

```c
add r0, r1, #num  //r0 = r1 + num
```

#### 3.2.3、比较指令：

```c

```

### 3.3、程序状态寄存器传输指令：

```c

```

### 3.4、内存访问指令：

```c
ldr/str 命令：
ldr ra, [rb]  ：将rb寄存器指示的内存中的数据加载到ra；
ldr ra, [rb, #12]  ：将rb+12指示的内存中的数据加载到ra；
ldr ra, [rb], #12  ：将rb指示的内存中的数据加载到ra，然后执行rb=rb + 12；
ldr ra, [rb, rc]  ：将rb+rc指示的内存中的数据加载到ra；
str ra, [rb]  ：将ra中的数据存储rb寄存器指示的内存中；

ldr/str 命令后缀：
b：从指定地址取1字节数据
h：从指定地址取2字节数据
w：从指定地址取4字节数据
x：从指定地址取8字节数据
s：进行指定字节的位扩展，配合上述4个扩展位使用

ldm/stm 批量传输指令：
命令后缀：
i：increase，地址变化方向为增加
d：decrease，地址变化方向为减小
a：after，传送后增加地址值(i++)
b：before，传送前增加地址值(++i)
Rn!    //!: 数据传输完成后，最后的地址写入Rn
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

## 4、ARM寄存器

```c
通用寄存器：
    未备份寄存器：R0 ~ R7
    备份寄存器：R8 ~ R14
    堆栈指针：SP (R13)
    连接寄存器：LR (R14)，保存子程序或异常返回地址
    程序计数器：PC (R15)
程序状态寄存器：CPSR
```

