/*
 * 简介：strlen测试
 * 时间：2020-04-28
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test_string.h"

int test_strlen()
{
	char *str = "1234567890";
	printf("strlen(\"%s\") = %d\n", str, (int)strlen(str));
	return 0;
}
