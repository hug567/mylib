/*
 * 简介：strlen测试
 * 时间：2020-04-28
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../test.h"

int test_strlen(void)
{
	char *str = "1234567890";
	mt_info("strlen(\"%s\") = %d\n", str, (int)strlen(str));
	return 0;
}
