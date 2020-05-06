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

extern int test_qsort(void);

int stdlib_main(struct test_struct *test)
{
	add_test_module("stdlib");

	add_test_case("stdlib", "test_qsort", test_qsort);

	return 0;
}
