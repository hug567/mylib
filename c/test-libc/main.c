#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"

int test_printf(void)
{
	int ret;
	ret = printf("printf test\n");
	if (ret < 0) {
		mt_fail("%s failed, ret = %d\n", __func__, ret);
	} else {
		mt_succ("%s success, ret = %d\n", __func__, ret);
	}
	return 0;
}

char *tests[] = {
	"test_printf",
};

int test_case_exist(char **tests, int count, char **test)
{
	int i;

	for (i = 0; i < count; i++) {
		if (strcmp(tests[i], test) == 0) {
			return 1;
		}
	}
	return 0;
}

void run_all_test(char **tests, int count)
{

}

int main(int argc, char *argv[])
{
	int ret;

	if (argc == 1) {
		run_all_test();
	}
	mt_log("hello mt_log\n");

	RUN_TEST(test_printf);

	return 0;
}
