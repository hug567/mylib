/*
 * gcc预定义宏
 * 2024-08-21
 */
#include <stdio.h>

static int test_counter(void)
{
	printf("[%s] --------------------------------------------\n", __func__);

	/*
	 * __COUNTER__提供不重复的整形值，从0开始
	 * 在宏中与连接符##一起使用，可自动创建独一无二的符合
	 */
	printf("__COUNTER__: %d\n", __COUNTER__);
	printf("__COUNTER__: %d\n", __COUNTER__);
	printf("__COUNTER__: %d\n", __COUNTER__);

	return 0;
}

static int test_file(void)
{
	printf("[%s] --------------------------------------------\n", __func__);

#define PRINT_MACRO_STR(macro) \
	printf(#macro ": %s\n", macro)
#define PRINT_MACRO_INT(macro) \
	printf(#macro ": %d\n", macro)

	/* 绝对路径文件名 */
	PRINT_MACRO_STR(__FILE__);
	PRINT_MACRO_STR(__BASE_FILE__);
	/* 当前文件名，没有路径 */
	PRINT_MACRO_STR(__FILE_NAME__);
	/* 函数名 */
	PRINT_MACRO_STR(__FUNCTION__);
	PRINT_MACRO_STR(__func__);
	/* 当前行 */
	PRINT_MACRO_INT(__LINE__);
	/* 日期 */
	PRINT_MACRO_STR(__DATE__);
	/* 时间 */
	PRINT_MACRO_STR(__TIME__);

	PRINT_MACRO_INT(__INCLUDE_LEVEL__);
	PRINT_MACRO_INT(__ELF__);
	/* 编译器版本字符串 */
	PRINT_MACRO_STR(__VERSION__);

	return 0;
}

int main()
{
	test_counter();
	test_file();
	return 0;
}
