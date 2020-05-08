/*
 * Brief  : Test framework unified header file
 * Author : Huang Xing <huangxing567@163.com>
 * Time   : 2020-03-22
 */
#ifndef __TEST_H__
#define __TEST_H__

#include <stdio.h>

struct test_struct {
	int fd; /* log file's fd */
};

struct test_case {
	const char *name;
	struct test_case *next;
	int (*func)(void);
};

struct test_module {
	const char *name;
	struct test_case *head;
	struct test_module *next;
};

#define mt_debug(fmt, ...) printf("[DEBUG][%s@%d]: " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define mt_info(fmt, ...)  printf("[INFO][%s@%d]: "  fmt, __func__, __LINE__, ##__VA_ARGS__)
#define mt_error(fmt, ...) printf("[ERROR][%s@%d]: " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define mt_succ(fmt, ...)  printf("[SUCC][%s@%d]: "  fmt, __func__, __LINE__, ##__VA_ARGS__)
#define mt_fail(fmt, ...)  printf("[FAIL][%s@%d]: "  fmt, __func__, __LINE__, ##__VA_ARGS__)

FILE *__fp;
#define write_to_file(path, fmt, ...) \
do { \
	__fp = fopen(path, "a"); \
	fprintf(__fp, fmt, __VA_ARGS__); \
	fclose(__fp); \
} while(0)

#define RUN_TEST(__test__) \
	do { \
		printf("--------------- %s ---------------\n", #__test__); \
		ret = __test__(); \
		if (ret < 0) { \
			mt_fail("%s failed\n", #__test__); \
		}\
	} while (0)

void add_test_module(const char *moduleName);
void add_test_case(const char *moduleName, const char *caseName, int (*func)(void));
int list_test_modules(void);
int list_test_cases(const char *name);
struct test_module *find_module(const char *module_name);
struct test_case *find_case(const char *module_name, const char *case_name);
int run_one_case(struct test_case *tcase);
int run_one_module(struct test_module *module);
int run_all_module(void);
struct test_struct *get_test_struct(void);
int init_test(void);

#endif /* __TEST_H__ */
