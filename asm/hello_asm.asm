extern	hello_print_c	;声明C函数
;extern _exit


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
	mov	eax,4     ;system call number (sys_write)
	mov     ebx,1     ;first argument: file handle (stdout)
	mov     ecx,msg   ;second argument: pointer to message to write
	mov     edx,len   ;third argument: message length
	int     0x80      ;call kernel
	; 调用C语言函数
	;bl	hello_print_c	;调用C语言函数
	call	hello_print_c	;调用C语言函数
	; 程序退出
	mov     eax,1     ;system call number (sys_exit)
	xor     ebx,ebx   ;first syscall argument: exit code
	int     0x80      ;call kernel
