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

#define OPT_STR "hlr:t:"

static const char *g_modules_name[] = {
	"stdio",
	"stdlib",
	"string",
};

static void usage(const char *name)
{
    printf("Usage:\n");
    printf("%s -h                     get help information\n", name);
    printf("%s -l                     list all modules\n", name);
    printf("%s -l <module>            list all test case in the specified module\n", name);
    printf("%s                        run all test case\n", name);
    printf("%s -r <module>            run all test case in the specified module\n", name);
    printf("%s -r <module> -t <test>  run the specified test case in the specified module\n", name);
}

int main(int argc, char *argv[])
{
	int ret;
	int count = sizeof(g_modules_name) / sizeof(char *);

	init_test_modules(g_modules_name, count);
	string_main();

	while ((ret = getopt(argc, argv, OPT_STR)) != -1) {
		switch (ret) {
		case 'h':
			usage(argv[0]);
			break;
		case 'l':
			if (argc == 2) {
				list_test_modules();
			} else if (argc == 3) {
mt_debug("optarg = %s\n", optarg);
				list_test_cases(argv[2]);
			}
			break;
		default:
			usage(argv[0]);
			break;
		}
	}
	return 0;
}
