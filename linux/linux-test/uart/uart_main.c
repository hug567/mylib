/*
 * Description: xxx
 * Author: huangxing567@163.com
 * Create: 2020-05-17 11:13:22
 */
#include "../test.h"

extern int test_uart_ioctl_1(void);
extern int test_uart_ioctl_2(void);

int uart_main(struct test_struct *test)
{
	add_test_module("uart");

	add_test_case("uart", "test_uart_ioctl_1", test_uart_ioctl_1);
	add_test_case("uart", "test_uart_ioctl_2", test_uart_ioctl_2);

	return 0;
}
