/*
 * Description: xxx
 * Author: huangxing567@163.com
 * Create: 2020-05-17 11:13:22
 */
#include "../test.h"

extern int test_ttyname(void);
extern int test_tcflow_ooff(void);
extern int test_tcflow_oon(void);
extern int test_tcflow_ioff(void);
extern int test_tcflow_ion(void);

int termios_main(struct test_struct *test)
{
	add_test_module("termios");

	add_test_case("termios", "test_ttyname", test_ttyname);
	add_test_case("termios", "test_tcflow_ooff", test_tcflow_ooff);
	add_test_case("termios", "test_tcflow_oon", test_tcflow_oon);
	add_test_case("termios", "test_tcflow_ioff", test_tcflow_ioff);
	add_test_case("termios", "test_tcflow_ion", test_tcflow_ion);

	return 0;
}
