#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"

const char *gTestModules[] = {
	"stdio",
	"stdlib",
	"string",
};

static void usage(const char *name)
{
	printf("Usage:\n");
	printf("%s                        run all test case\n", name);
	printf("%s -h                     get help information\n", name);
	printf("%s -l                     list all modules\n", name);
	printf("%s -l <module>            list all test case in the specified module\n", name);
	printf("%s -r <module>            run all test case in the specified module\n", name);
	printf("%s -r <module> -t <test>  run the specified test case in the specified module\n", name);
}

int main(int argc, char *argv[])
{
	int ret;
	int modulesNum = sizeof(gTestModules) / sizeof(char *);

	usage(argv[0]);
	struct TestModule *module = CreateTestModule(gTestModules, modulesNum);

	return 0;
}
