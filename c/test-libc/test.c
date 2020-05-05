/*
 * Description:
 * Author: huangxing567@163.com
 * Create: 2020.05.03 17:06
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "test.h"

#define LOG_FILE "/tmp/debug.log"
#define LOG_BUF_SIZE 1024

static char log_buf[LOG_BUF_SIZE];
static struct TestModule *g_modules = NULL;

static struct TestModule *find_module(const char *name)
{
	struct TestModule *module = g_modules;

	while (module != NULL) {
		if (strcmp(module->name, name) == 0) {
			return module;
		}
		module = module->next;
	}

	return NULL;
}

static struct TestCase *find_case(struct TestModule *module, const char *name)
{
	struct TestCase *tcase = NULL;

	if (module == NULL) {
		mt_error("module is NULL\n");
		return NULL;
	}

	tcase = module->head;
	while (tcase != NULL) {
		if (strcmp(tcase->name, name) == 0) {
			return tcase;
		}
		tcase = tcase->next;
	}

	return NULL;
}

void add_test_module(const char *moduleName)
{
	struct TestModule *tmp = g_modules;
	struct TestModule *new = (struct TestModule *)malloc(sizeof(struct TestModule));

	new->name = moduleName;
	new->head = NULL;
	new->next = NULL;
	if (g_modules == NULL) {
		g_modules = new;
	} else {
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = new;
	}
}

void add_test_case(const char *moduleName, const char *caseName, TestFunc *func)
{
	struct TestModule *module = g_modules;
	struct TestCase *tmp = NULL;
	struct TestCase *new = (struct TestCase *)malloc(sizeof(struct TestCase));

	new->name = caseName;
	new->func = func;
	new->next = NULL;
	if (g_modules == NULL) {
		mt_error("g_modules is NULL\n");
		return;
	}
	while (module != NULL) {
		if (strcmp(module->name, moduleName) == 0) {
			break;
		}
		module = module->next;
	}
	if (module == NULL) {
		mt_error("there is no %s module\n", moduleName);
		return;
	}

	tmp = module->head;
	if (tmp == NULL) {
		module->head = new;
	} else {
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = new;
	}
}

int list_test_modules(void)
{
	struct TestModule *module = g_modules;

	while (module != NULL) {
		printf("module: %s\n", module->name);
		module = module->next;
	}

	return 0;
}

int list_test_cases(const char *name)
{
	struct TestModule *module = NULL;
	struct TestCase *tcase = NULL;

	module = find_module(name);
	if (module == NULL) {
		mt_error("there is no %s module\n", name);
		return -1;
	}

	tcase = module->head;
	printf("module: %s\n", name);
	while (tcase != NULL) {
		printf("    %s\n", tcase->name);
		tcase = tcase->next;
	}
	return 0;
}

int run_one_case(const char *module_name, const char *case_name)
{
	struct TestModule *module = NULL;
	struct TestCase *tcase = NULL;

	module = find_module(module_name);
	if (module == NULL) {
		mt_error("there is no %s module\n", module_name);
		return -1;
	}

	tcase = find_case(module, case_name);
	if (tcase == NULL) {
		mt_error("there is no %s test case\n", case_name);
		return -1;
	}

	if (tcase->func != NULL) {
		printf("\n---------- %s ----------\n", tcase->name);
		return tcase->func();
	}

	return -1;
}

int run_one_module(const char *name)
{
	struct TestModule *module = NULL;
	struct TestCase *tcase = NULL;

	module = find_module(name);
	if (module == NULL) {
		mt_error("there is no %s module\n", name);
		return -1;
	}

	tcase = module->head;
	while (tcase != NULL) {
		if (tcase->func != NULL) {
			printf("\n---------- %s ----------\n", tcase->name);
			tcase->func();
		}
		tcase = tcase->next;
	}

	return 0;
}

int run_all_module(void)
{
	return 0;
}

static int init_log_file(struct test_struct *test)
{
	int ret;
	int fd = -1;

	ret = access(LOG_FILE, 0);
	if (ret < 0) {
		mt_info("%s does not exist, will create it\n", LOG_FILE);
		fd = creat(LOG_FILE, S_IRUSR | S_IWUSR);
		if (fd < 0) {
			mt_error("create %s failed\n", LOG_FILE);
			return -1;
		}
	}

	fd = open(LOG_FILE, O_RDWR);
	if (fd < 0) {
		mt_error("open %s failed\n", LOG_FILE);
		return -1;
	}
	/* clear log file */
	ftruncate(fd, 0);
	lseek(fd, 0, SEEK_SET);

	test->fd = fd;

	return 0;
}

extern int file_main(struct test_struct *test);

static int init_test_module(struct test_struct *test)
{
	stdio_main();
	string_main();
	file_main(test);

	return 0;
}

int init_test(const char **modules, const int count)
{
	int i;
	struct test_struct *test = NULL;

	test = (struct test_struct *)malloc(sizeof(struct test_struct));
	if (test == NULL) {
		mt_error("malloc for test_struct faied\n");
		return -1;
	}

	if (modules == NULL || count <= 0) {
		mt_error("There are no modules to initialize\n");
		free(test);
		return -1;
	}
	for (i = 0; i < count; i++) {
		add_test_module(modules[i]);
	}

	init_log_file(test);
	init_test_module(test);

	return 0;
}

int register_module(const char *name)
{
	return 0;
}
