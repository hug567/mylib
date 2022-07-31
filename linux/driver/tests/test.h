/*
 * linux test driver common func head file
 * 2022-07-19
 */
#ifndef __TEST_H__
#define __TEST_H__

#include <linux/printk.h>

#define log_info(fmt, ...) \
	printk("[INFO ][%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define log_error(fmt, ...) \
	printk("[ERROR][%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)

struct test_case {
	const char *name;
	int (*func)(void);
};

int __run_tests(const char *func, int line, struct test_case *tests, int size);

#define DEFINE_TEST_CASE(f) \
	{.name = #f, .func = (f)},

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#define RUN_TESTS(tests) \
	__run_tests(__func__, __LINE__, tests, ARRAY_SIZE(tests))

#endif
