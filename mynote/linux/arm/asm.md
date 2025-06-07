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
.global symbol    //声明符号为全局符号，试其对其他c文件或链接脚本可见
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

//定义一个段，a:可分配
.section .init.ramfs,"a"

//在汇编文件中包含一个指定文件，不对该文件做任何操作
.incbin "usr/initramfs_inc_data"
```

## 3、常用指令：

### 3.1、跳转指令：

```c
b             //跳转指令
bl            //带返回的跳转指令，将PC寄存器的值保存到LR寄存器中
blx           //带返回和状态切换的跳转指令
bx            //带状态切换的跳转指令
br Rx         //跳转到Rx寄存器指定的地址处，不是子程序返回
b.hi <addr>   //CPSR寄存器结果是无符号数大于，则跳转到addr
beq <addr>    //上一条cmp指令比较的两个值相等时跳转
bge <addr>    //上一条cmp指令比较的两个值，a>=b时跳转

cbz  //值为0就跳转
cbz w4, ffff8000101f1d40 <find_get_entries+0x260>  //w4值为0则跳转

cbnz  //值不为0就跳转

tbnz  //测试指定bit位不为0则跳转
tbnz w19, #0, ffff8000101f1c2c <find_get_entries+0x14c>  //w19第0位不为0则跳转
```

### 3.2、数据处理指令：

#### 3.2.1、数据传送指令：

```c
mov ra, rb          //将rb中存放的数据传送给ra，mov只能在寄存器间传递数据，或将立即数传递给寄存器,不能直接操作内存中的数据
mov ra, #0x12       //将立即数0x12存入ra寄存器中，立即数不能太大，mov最多只能操作16位的立即数，太大用ldr
mov ra, #'A'        //将字符A存入ra寄存器中
//按位取反后传送
mvn r1, #0xFF      //r1=0xFFFFFF00
//加载到低16位，高半部清零：0x0000-0xFFFF
movw r1, 0xDF0D     //r1=0x0000DF0D
//加载到寄存器高半部，低半部不受影响：0x0000-0xFFFF
movt r1, #0xFFFF    //r1=0xFFFF0000
//复合指令，将 r8 的值右移 12 位后，存储到 r0 中
mov r0, r8, LSR #12

stp                 //入栈指令 (aarch64栈由高地址向底地址增长)
/*
 * aarch64：栈自顶部向下
 * !：向将sp的值减去64，再从新的sp开始，向上入栈x29和x30
 */
stp x29, x30, [sp, #-64]!
/*
 * 将x29和x30从sp+0x10的位置开始向上入栈，sp的值不变
 */
stp x29, x30, [sp, #0x10]

ldp                 //出栈指令
ldp x29, x30, [sp, #0x10] 	//从将sp加16个字节开始，读值存入寄存器x29和x30
```

#### 3.2.2、运算指令：

##### 1）、算术指令：

```c
add r0, r1, #num           //加法：r0 = r1 + num

mul x0, x1, x2             //32位乘法：x0 = x1 * x2

bic：位清除指令
bic r0, r0, #0x0F          //r0 = r0 & (~0x0F)

adrp <Rd>, <label>         //获取label所在4k大小的页基址，存入Rd寄存器（armv8引入，address page）

orr x0, x0, #9             //按位或，x0 = x0 | 9
eor x0, x0, #0xf           //按位异或，x0 = x0 ^ 0xf

cbz x0, ffff80001027ec8c   //值为0就跳转
cbnz x0, ffff80001027ec8c  //值不为0就跳转

lsl x1, x1, #12            //将x1中的值左移12位
lsr x1, x1, #12            //将x1中的值右移12位

neg x1, x2                 //取负数运算，x2按位取反后+1，赋值给x1

//原子加法操作
stadd x1, [x2]             //将x1寄存器值和x2指向的内存的值相加，然后存储到x2指向的内存中
```

##### 2）、位域指令：

```c
//位域插入
bfi

//无符号位域提取
ubfx

//有符号位域提取
sbfx

//位域提取并向低位插入
bfxil

//无符号位域插入零
ubfiz x1, x0, #3, #6  //x0[0:5]位存储到x1[3:8]，其他位填充0

//有符号位域插入零
sbfiz
```

#### 3.2.3、比较指令：

```c
/*
 * 比较交换：
 * tmp = [x4];
 * if (x0 == [x4]) {
 *     [x4] = x1;
 * }
 * x0 = tmp;
 */
cas x0, x1, [x4]           //从内存[x4]读取值与x0比较，若相同则将x1存入内存[x4]，最后将内存[x4]的值写入x1

casp  //比较交换两对寄存器
casp x0, x1, x2, x3, [x4]  //同时操作两对寄存器

//按位与
tst x0, #0xfffffffd        //按位与
b.ne 22b0                  //结果不为0则跳转
b.eq 22b0                  //结果为0则跳转
```

### 3.3、程序状态寄存器传输指令：

```c
mrs    //将系统寄存器的值读取到通用寄存器
mrs x0, tpidr_el1    //将tpidr_el1读取到x0 (TPIDR_EL1, EL1 Software Thread ID Register)

msr    //将通用寄存器的值写入系统寄存器
msr tpidr_el1, x0    //将tpidr_el1的值读到x0
```

### 3.4、内存访问指令：

```c
ldr  //从内存读取指令到寄存器
ldr ra, =0x12345678  //将立即数0x12345678存入寄存器ra中
ldr ra, [rb]         //将rb寄存器指示的内存中的数据加载到ra；
ldr ra, [rb, #12]    //将rb+12指示的内存中的数据加载到ra；
ldr ra, [rb], #12    //将rb指示的内存中的数据加载到ra，然后执行rb=rb + 12；
ldr ra, [rb, rc]     //将rb+rc指示的内存中的数据加载到ra；
ldr x1, [x0, #8]     //x1 = *(x0 + 0x8)
ldrh w1, [x1, #12]   //从x1+12地址处读取半字数据到w1

str ra, [rb]         //将ra中的数据存储到rb寄存器指示的内存中

/*
ldr/str 命令后缀：
b：从指定地址取1字节数据
h：从指定地址取2字节数据
w：从指定地址取4字节数据
x：从指定地址取8字节数据
s：进行指定字节的位扩展，配合上述4个扩展位使用
*/
/*
ldm/stm 批量传输指令：
命令后缀：
i：increase，地址变化方向为增加
d：decrease，地址变化方向为减小
a：after，传送后增加地址值(i++)
b：before，传送前增加地址值(++i)
Rn!    //!: 数据传输完成后，最后的地址写入Rn
*/

/*
 * #define __smp_mb() dmb(ish)
 * #define __smp_rmb() dmb(ishld)
 * #define __smp_wmb() dmb(ishst)
 */
dmb [arg]        // 数据存储器隔离，指令前的所有存储器访问操作都完成，才提交指令后的存储器操作指令
dsb [arg]        // 数据同步隔离，指令前的所有存储器访问操作都完成，才执行后面的指令
isb              // 指令同步隔离，清流水线，保证前面的所有指令都执行完，才执行后面的指令
/*
 * dmb/dsb指令参数：
 *   DMA设备属于外部共享域
 */
    sy           //内存读写指令，全系统共享域
    ish          //内存读写指令，内部共享域
    ishld        //内存读指令，内部共享域
    ishst        //内存写指令，内部共享域
    nsh          //内存读写指令，不指定共享域
    osh          //内存读写指令，外部共享域
```

### 3.5、协处理器指令：

```c
cdp  协处理器数据操作指令

mcr    //将arm寄存器的值传送到协处理器寄存器中
mrc    //将协处理寄存器中的数值传送到arm寄存器中
```

### 3.6、异常中断产生指令：

```c
swi           //软中断指令
brk #0x800    //产生异常，通常用于程序调试
bkpt          //断点中断指令
```

### 3.7、其他：
```c
//地址中删除指针验证码
XPACD x1             //删除x1中存储的数据地址的指针验证码，可以指定任意通用寄存器
XPACI x1             //删除x1中存储的指令地址的指针验证码
XPACLRI              //删除LR中存储的指令地址的指针验证码

wfe                  //wait for event，等待事件
wfi                  //wait for interrupt，等待中断
sev                  //send event，发送事件，向系统中所有cpu核发送事件，如果有cpu处于等待事件(wfe)状态，该cpu将被唤醒
sevl                 //send event local，只向当前cpu发送事件，只在ARMv8之后支持
```

## 4、ARM寄存器

```c
通用寄存器：
    未备份寄存器：R0 ~ R7
    备份寄存器：R8 ~ R14
    堆栈指针：SP (R13)
    连接寄存器：LR (R14)，跳转返回将执行的指令
    程序计数器：PC (R15)，指向即将执行的下一条指令

LR：R14，连接寄存器，有两个用途：
    用途一：保存子程序返回地址，使用BL或BLX调用子程序时，硬件自动将返回地址保存到LR寄存器中，子程序返回时，将LP复制到PC，即可实现子程序返回；
    用途二：发生异常时LR被自动填充PC值减4；

//程序状态寄存器
CPSR

//特殊寄存器：
wzr              //32位零寄存器
xzr(x31)         //64零寄存器，写入代表丢弃结果，读取是0（zero register）

ttbr0_el1        //用户态地址转换，页表基地址寄存器
ttbr1_el1        //内核态地址转换，页表基地址寄存器

//Translation Control Register，转换控制寄存器
tcr_el1/tcr_el2/tcr_el3
    IPS,bits[34:32]    //地址宽度
        000            //32位，4G
        001            //36位，64G
        010            //40位，1T
        011            //42位，4T
        100            //44位，16T
        101            //48位，256T
        110            //52位，4P
```

## 5、C语言嵌套ARM汇编：

```c
__asm__ [__volatile__] (
    “mov r0, #0x12\n”                        //汇编代码
    : [output operand list]                  //输出操作数列表，可选  
    : [input operand list]                   //输入操作数列表，可选
    : [clobbered register list]              //修改寄存器列表，可选
);  
```

## 6、ARM协处理器：

协处理器CP15：ARM的存储系统是通过协处理器CP15管理的，CP15有16个32位寄存器，编号为0 - 15；

#### 1）、写协处理器寄存器：mcr

* **mcr**{cond}     coproc,  opcode1,  Rd,  CRn,  CRm,  {opcode2}

  cond：执行条件，可选，缺省为无条件执行

  coproc：协处理器名，p0~15，CP15名为p15

  opcode1：操作码，CP15协处理器操作码为0

  Rd：ARM寄存器

  CRn：目标协处理寄存器1，c0~15

  CRm：目标协处理寄存器2，c0~15

  opcode2：操作码，可选

* 功能：将ARM寄存器Rd中的值传送到协处理器的寄存器CRn和CRm中；

#### 2）、读协处理器寄存器：mrc

* **mrc**{cond}     coproc,  opcode1,  Rd,  CRn,  CRm,  {opcode2}

  cond：执行条件，可选，缺省为无条件执行

  coproc：协处理器名，p0~15，CP15名为p15

  opcode1：操作码，CP15协处理器操作码为0

  Rd：ARM寄存器

  CRn：目标协处理寄存器1，c0~15

  CRm：目标协处理寄存器2，c0~15

  opcode2：操作码，可选，用于区分同一编号的不同物理寄存器

* 功能：将协处理器的寄存器CRn和CRm中的值传送到ARM寄存器Rd中；

## 7、CP15寄存器：

| 寄存器 | 功能                         | 权限 |
| ------ | ---------------------------- | ---- |
| c0     | ID编码                       | 只读 |
| c1     | 控制位                       | 读写 |
| c2     | 地址转换表基址(一级页表基址) |      |
| c3     | 域访问控制                   |      |

## 8、向串口输出字符：

### 1）、arm(v7)：

```bash
	mov r5, #'A'
	ldr r6, =-0xE0001030
	str r5, [r6]
```

### 2）、aarch64(v8)：

```bash

```

