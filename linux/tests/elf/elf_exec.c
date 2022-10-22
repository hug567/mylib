/*
 * elf可执行文件(executable)
 * 编译：gcc elf_exec.c -o elf_exec.elf
 * 2022-10-22
 */
/*
 * readelf -h elf_exec.elf        查看elf文件头
 * readelf -l elf_exec.elf        查看elf程序头
 * readelf -S elf_exec.elf        查看elf所有节头
 * readelf -t elf_exec.elf        查看elf所有节详细信息
 * readelf -s elf_exec.elf        查看elf符号表
 * readelf -e elf_exec.elf        查看elf节头信息，等价于：-h -I -S
 * readelf -n elf_exec.elf        查看elf note段
 * readelf -r elf_exec.elf        查看elf可重定位段信息
 * readelf -d elf_exec.elf        查看elf动态段信息
 * readelf -a elf_exec.elf        查看elf所有信息，等价于： -h -l -S -s -r -d -V -A -I
 * readelf -x .text elf_exec.elf  查看elf .text节内容
 */
/*
 * objdump -t elf_exec.elf           导出所有符号表
 * objdump -T elf_exec.elf           导出动态链接符号表
 * objdump -h elf_exec.elf           导出段信息
 * objdump -f elf_exec.elf           导出文件头
 * objdump -s elf_exec.elf           以十六进制打印所有段内容
 * objdump -d elf_exec.elf           反汇编程序
 * objdump -S elf_exec.elf           反汇编打印源代码
 * objdump -D elf_exec.elf           反汇编所有段
 * objdump -j .text -d elf_exec.elf  反汇编.text节
 * objdump -x elf_exec.elf           显示所有可用信息，等价于：-a -f -h -r -t
 */
#include <stdio.h>

int main(void)
{
	printf("hello world!\n");
	return 0;
}
