/*
 * elf共享目标文件(.so)(dynamic)
 * 编译：gcc -fPIC -shared elf_dyn.c -o elf_dyn.so
 * 2022-10-22
 */
/* 设置变量到自定义节中 */
static int __attribute__((__section__(".myvar_section"))) g_num = 0;

/* 设置函数到自定义节中 */
int get_num(void);
int __attribute__((__section__(".myfunc_section"))) get_num(void)
{
	return 0;
}
