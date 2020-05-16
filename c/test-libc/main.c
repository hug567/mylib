/*
 * Introduction: the main function of the test suite
 * Author: huangxing567@163.com
 * Create: 2020-04-30
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "test.h"

#define OPT_STR "hl:r:t:"

extern int array_main(struct test_struct *test);
extern int file_main(struct test_struct *test);
extern int stdio_main(struct test_struct *test);
extern int stdlib_main(struct test_struct *test);
extern int string_main(struct test_struct *test);

static void usage(const char *name)
{
    printf("Usage:\n");
    printf("%s -h                     get help information\n", name);
    printf("%s -l all                 list all modules\n", name);
    printf("%s -l <module>            list all test case in the specified module\n", name);
    printf("%s -r all                 run all test case\n", name);
    printf("%s -r <module>            run all test case in the specified module\n", name);
    printf("%s -r <module> -t <test>  run the specified test case in the specified module\n", name);
}

static int init_all_modules(struct test_struct *test)
{
	array_main(test);
	file_main(test);
	stdio_main(test);
	stdlib_main(test);
	string_main(test);
	return 0;
}

static int run_test(const char *module_name, const char *case_name)
{
	int ret;
	struct test_module *module = NULL;
	struct test_case *tcase = NULL;

	if (module_name != NULL && strcmp(module_name, "all") == 0) {
		ret = run_all_module();
		if (ret < 0) {
			mt_error("run all module failed\n");
			return -1;
		}
	} else if (module_name != NULL && case_name == NULL) {
		module = find_module(module_name);
		ret = run_one_module(module);
		if (ret < 0) {
			mt_error("run module %s failed\n", module_name);
			return -1;
		}
	} else if (module_name != NULL && case_name != NULL) {
		module = find_module(module_name);
		tcase = find_case(module_name, case_name);
		ret = run_one_case(tcase);
		if (ret < 0) {
			mt_error("run case %s failed\n", case_name);
			return -1;
		}
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int ret;
	char *module_name = NULL;
	char *case_name = NULL;
	struct test_struct *test = NULL;

	if (argc < 2 || argc > 5) {
		usage(argv[0]);
		return -1;
	}

	init_test();
	test = get_test_struct();
	if (test == NULL) {
		mt_error("get test struct failed\n");
		return -1;
	}
	init_all_modules(test);

	while ((ret = getopt(argc, argv, OPT_STR)) != -1) {
		switch (ret) {
		case 'h':
			usage(argv[0]);
			break;
		case 'l':
			if (strcmp(optarg, "all") == 0) {
				list_test_modules();
			} else {
				list_test_cases(optarg);
			}
			break;
		case 'r':
			module_name = optarg;
			break;
		case 't':
			case_name = optarg;
			break;
		default:
			usage(argv[0]);
			break;
		}
	}

	run_test(module_name, case_name);

	return 0;
}
