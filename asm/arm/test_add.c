/*
 * arm汇编练习：
 * C语言中执行汇编代码, 实现整数加法
 * 编译: arm-linux-gnueabi-gcc test_add.c
 * 运行: qemu-arm ./a.out
 * 2021-09-02
 */

#include <stdio.h>

unsigned int add(unsigned int a, unsigned int b)
{
	__asm__(
		"add r0, r0, r1"
	);
}

int main(int argc, const char *argv[])
{
	return 0;
}
