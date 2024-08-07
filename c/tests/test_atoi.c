/*
 * 测试atoi函数
 * 2024-08-01
 */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char ret;
	char *str;

	str = "-1";
	ret = atoi(str);
	printf("atoi(%s) = %hhd\n", str, ret);
	return 0;
}
