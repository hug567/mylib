/*
 * Introduction: the main function of the test suite
 * Author: huangxing567@163.com
 * Create: 2020-04-30
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "test.h"

#define OPT_STR "hl:r:t:"

static const char *g_modules_name[] = {
	"stdio",
	"stdlib",
	"string",
};

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

int main(int argc, char *argv[])
{
	int ret;
	int count = sizeof(g_modules_name) / sizeof(char *);
	char *module_name = NULL;
	char *case_name = NULL;

	init_test_modules(g_modules_name, count);

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

	if (module_name != NULL && strcmp(module_name, "all") == 0) {
		run_all_module();
	} else if (module_name != NULL && case_name == NULL) {
		run_one_module(module_name);
	} else if (module_name != NULL && case_name != NULL) {
		run_one_case(module_name, case_name);
	}

	return 0;
}
