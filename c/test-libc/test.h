/*
 * Brief  : Test framework unified header file
 * Author : Huang Xing <huangxing567@163.com>
 * Time   : 2020-03-22
 */
#ifndef __TEST_H__
#define __TEST_H__

typedef int (*TestFunc(void));

struct TestCase {
	char *name;
	TestFunc *func;
	struct TestCase *next;
};

struct TestModule {
	struct TestCase *head;
	struct TestMode *next;
};

#define mt_log(fmt, ...) printf("[mytest][%s@%d]: " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define mt_succ(fmt, ...) printf("[mytest][success][%s@%d]: " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define mt_fail(fmt, ...) printf("[mytest][fail][%s@%d]: " fmt, __func__, __LINE__, ##__VA_ARGS__)

#define RUN_TEST(__test__) \
	do { \
		printf("--------------- %s ---------------\n", #__test__); \
		ret = __test__(); \
		if (ret < 0) { \
			mt_fail("%s failed\n", #__test__); \
		}\
	} while (0)

#endif /* __TEST_H__ */
