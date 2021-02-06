/*
 * 练习：printf
 * 时间：2021-02-03
 */
#include "test.h"

void print_char(char ch)
{
	printf("%c", ch);
}

void print_chars(const char *buf, int size)
{
	int i;
	for (i = 0; i < size; i++) {
		print_char(buf[i]);
	}
}

#define BUF_SIZE 256
#define print_log(fmt, ...) \
({ \
	int __i; \
	char __buf[BUF_SIZE] = {0}; \
	int __len = sprintf(__buf, fmt, ##__VA_ARGS__); \
	for (__i = 0; __i < __len; __i++) { \
		print_char(__buf[__i]); \
	} \
})

int test_printf(void)
{
	int ret;
	mt_info("Enter %s\n", __func__);
	print_log("[hx-debug][%s:%d] Enter %s\n", __func__, __LINE__, __func__);

	mt_debug("debug log\n");
	mt_info("info log\n");
	mt_error("error log\n");
	mt_succ("success log\n");
	mt_fail("fail log\n");

	return 0;
}
