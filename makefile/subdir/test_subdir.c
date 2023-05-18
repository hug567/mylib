/*
 * 练习：Makefile编译子目录
 * 简介：子目录中的源文件
 * 时间：2020-04-04
 */
#include <stdio.h>
#include "test_subdir.h"

void subdir_print(void)
{
	printf("%s is a function in sub dir\n", __func__);
}
