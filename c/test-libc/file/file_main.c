/*
 * Description:
 * Author: huangxing567@163.com
 * Create: 2020.05.03 17:06
 */
#include "../test.h"

extern int test_write(void);
extern int test_write_char(void);

int file_main(struct test_struct *test)
{
	add_test_module("file");

	add_test_case("file", "test_write", test_write);
	add_test_case("file", "test_write_char", test_write_char);

	return 0;
}
