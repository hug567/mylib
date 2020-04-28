/*
 * Brief  : Test framework unified header file
 * Author : Huang Xing <huangxing567@163.com>
 * Time   : 2020-03-22
 */
#ifndef __TEST_H__
#define __TEST_H__

typedef int TestFunc(void);

struct TestCase {
	const char *name;
	int (*func)(void);
	struct TestCase *next;
};

struct TestModule {
	const char *name;
	struct TestCase *head;
	struct TestModule *next;
};

#define mt_info(fmt, ...)  printf("[INFO][%s@%d]: " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define mt_error(fmt, ...) printf("[ERROR][%s@%d]: " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define mt_succ(fmt, ...)  printf("[SUCC][%s@%d]: " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define mt_fail(fmt, ...)  printf("[FAIL][%s@%d]: " fmt, __func__, __LINE__, ##__VA_ARGS__)

#define RUN_TEST(__test__) \
	do { \
		printf("--------------- %s ---------------\n", #__test__); \
		ret = __test__(); \
		if (ret < 0) { \
			mt_fail("%s failed\n", #__test__); \
		}\
	} while (0)

void AddTestModule(const char *moduleName);
void AddTestCase(const char *moduleName, const char *caseName, TestFunc *func);

int string_main(void);

#endif /* __TEST_H__ */
