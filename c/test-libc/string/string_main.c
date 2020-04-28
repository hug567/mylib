/*
 *
 *
 *
 * 时间：2020-04-28
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test_string.h"

int string_main(void)
{
    //int ret;

    //RUN_TEST(test_strlen);
	AddTestCase("string", "strlen", test_strlen);

    return 0;
}
