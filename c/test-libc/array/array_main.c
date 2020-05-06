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

int array_main(struct test_struct *test)
{
	add_test_module("array");

	add_test_case("array", "test_array", test_array);

	return 0;
}
