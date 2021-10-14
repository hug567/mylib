/*
 * arm汇编练习：
 * 汇编打印日志
 * 编译: arm-linux-gnueabi-gcc test_put_char.asm
 * 运行: qemu-arm ./a.out
 * 2021-10-10
 */

; 数据段
section .data                               ;section declaration
	msg	db	"Hello, world!",0xA     ;our dear string
	len	equ     $ - msg                 ;length of our dear string
section .text                               ;section declaration
                       ;we must export the entry point to the ELF linker or
global _start          ;loader. They conventionally recognize _start as their
                       ;entry point. Use ld -e foo to override the default.

_start:
	; 打印字符串
	mov	eax, 4		; 系统调用write()
	mov	ebx, 1		; 第一个参数：fd = 1, stdout
	mov	ecx, msg	; 第二个参数：buf
	mov	edx, len	; 第三个参数: length
	int	0x80		; 开始系统调用
	; 调用C语言函数
	;bl	hello_print_c	;调用C语言函数
	;call	hello_print_c	;调用C语言函数
	;STR	lr,[sp,#-4]!
	;ldr	r0,=0x01
	;ldr	r1,=0x02
	;call	add
	;addl	$0x10, %esp
	; 程序退出
	mov     eax, 1		; 系统调用exit()
	xor     ebx, ebx	; 第一个参数：退出码
	int     0x80		; 开始系统调用
