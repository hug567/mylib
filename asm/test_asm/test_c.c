/*
 * 测试：C语言调用汇编
 * 平台：X86-64
 * 时间：2020-12-09
 */
#include "../common.h"

/*
 * x86-64:
 * %rax    返回值
 * %rbx    被调用者保存
 * %rcx    第4个参数
 * %rdx    第3个参数
 * %rsi    第2个参数
 * %rdi    第1个参数
 * %rbp    被调用者保存
 * %rsp    栈指针
 * %r8     第5个参数
 * %r9     第6个参数
 * %r10    调用者保存
 * %r11    调用者保存
 * %r12    被调用者保存
 * %r13    被调用者保存
 * %r14    被调用者保存
 * %r15    被调用者保存
 */
int asm_add(int a, int b)
{
	__asm__(
		"addq %rdi, %rsi;" /* %rsi = %rsi + %rdi */
		"movq %rsi, %rax" /* %rax = %rsi */
	);
}

int asm_sub(int a, int b)
{
	__asm__(
		"subq %rsi, %rdi;" /* %rdi = %rsi - %rdi */
		"movq %rdi, %rax" /* %rax = %rdi */
	);
}

int main(void)
{
	printf("1 + 2 = %d\n", asm_add(1, 2));
	printf("3 + 4 = %d\n", asm_add(3, 4));
	printf("4 - 3 = %d\n", asm_sub(4, 3));
	printf("9 - 3 = %d\n", asm_sub(9, 3));
	return 0;
}
