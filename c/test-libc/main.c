#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"

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

static void ListAllModules(const char **modules, int count)
{
	int i;

	for (i = 0; i < count; i++) {
		printf("%s\n", modules[i]);
	}
}

static void add_all_test_modules(const char **modules, int count)
{
	int i;

	for (i = 0; i < count; i++) {
		AddTestModule(modules[i]);
	}
}

int main(int argc, char *argv[])
{
	int count = sizeof(g_modules_name) / sizeof(char *);

	if (argc == 2 && (strcmp(argv[1], "-h") == 0)) {
		usage(argv[0]);
	}

	add_all_test_modules(g_modules_name, count);
	string_main();

	if (argc == 2 && (strcmp(argv[1], "-l") == 0)) {
		ListAllModules(g_modules_name, count);
	}
	return 0;
}
