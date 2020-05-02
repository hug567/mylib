/*
 * 简介：strlen测试
 * 时间：2020-04-28
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_header.h"

int test_strlen(void)
{
	char *str = "1234567890";
	printf("strlen(\"%s\") = %d\n", str, (int)strlen(str));
	return 0;
}
