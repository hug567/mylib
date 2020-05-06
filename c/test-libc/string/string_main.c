/*
 *
 *
 *
 * 时间：2020-04-28
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../test.h"

extern int test_strlen(void);

int string_main(struct test_struct *test)
{
	add_test_module("string");

	add_test_case("string", "test_strlen", test_strlen);

	return 0;
}
