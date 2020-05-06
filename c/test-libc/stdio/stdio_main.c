/*
 *
 *
 *
 * 时间：2020-05-02
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../test.h"

extern int test_sizeof(void);

int stdio_main(struct test_struct *test)
{
	add_test_module("stdio");

	add_test_case("stdio", "test_sizeof", test_sizeof);

	return 0;
}
