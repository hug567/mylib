/*
 *
 *
 *
 * 时间：2020-05-07
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../test.h"

extern int test_array(void);
extern int test_func_param(void);

int array_main(struct test_struct *test)
{
	add_test_module("array");

	add_test_case("array", "test_array", test_array);
	add_test_case("array", "test_func_param", test_func_param);

	return 0;
}
