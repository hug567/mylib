/*
 * Description:
 * Author: huangxing567@163.com
 * Create: 2020.05.03 17:06
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"

static struct test_struct *g_test = NULL;
static struct test_module *g_modules = NULL;

struct test_module *find_module(const char *module_name)
{
	struct test_module *module = g_modules;

	if (module_name == NULL) {
		mt_error("module name is NULL\n");
		return NULL;
	}
	while (module != NULL) {
		if (strcmp(module->name, module_name) == 0) {
			return module;
		}
		module = module->next;
	}

	return NULL;
}

struct test_case *find_case(const char *module_name, const char *case_name)
{
	struct test_module *module = NULL;
	struct test_case *tcase = NULL;

	if (module_name == NULL || case_name == NULL) {
		mt_error("module_name or case_name is NULL\n");
		return NULL;
	}

	module = find_module(module_name);
	if (module == NULL) {
		mt_error("module is NULL\n");
		return NULL;
	}

	tcase = module->head;
	while (tcase != NULL) {
		if (strcmp(tcase->name, case_name) == 0) {
			return tcase;
		}
		tcase = tcase->next;
	}

	return NULL;
}

void add_test_module(const char *moduleName)
{
	struct test_module *tmp = g_modules;
	struct test_module *new = (struct test_module *)malloc(sizeof(struct test_module));

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

void add_test_case(const char *moduleName, const char *caseName, int (*func)(void))
{
	struct test_module *module = g_modules;
	struct test_case *tmp = NULL;
	struct test_case *new = (struct test_case *)malloc(sizeof(struct test_case));

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
	struct test_module *module = g_modules;

	while (module != NULL) {
		printf("module: %s\n", module->name);
		module = module->next;
	}

	return 0;
}

int list_test_cases(const char *module_name)
{
	struct test_module *module = NULL;
	struct test_case *tcase = NULL;

	module = find_module(module_name);
	if (module == NULL) {
		mt_error("there is no %s module\n", module_name);
		return -1;
	}

	tcase = module->head;
	printf("module: %s\n", module_name);
	while (tcase != NULL) {
		printf("    %s\n", tcase->name);
		tcase = tcase->next;
	}

	return 0;
}

int run_one_case(struct test_case *tcase)
{
	if (tcase == NULL) {
		mt_error("tcase is NULL\n");
		return -1;
	}

	if (tcase->func != NULL) {
		printf("\n---------- Start test case: %s ----------\n",
		       tcase->name);
		return tcase->func();
	}

	return 0;
}

int run_one_module(struct test_module *module)
{
	struct test_case *tcase = NULL;

	if (module == NULL) {
		mt_error("module is NULL\n");
		return -1;
	}

	tcase = module->head;
	while (tcase != NULL) {
		if (tcase->func != NULL) {
			printf("\n---------- Start test case: %s ----------\n",
			       tcase->name);
			tcase->func();
		}
		tcase = tcase->next;
	}

	return 0;
}

int run_all_module(void)
{
	struct test_module *module = g_modules;

	while (module != NULL) {
		run_one_module(module);
		module = module->next;
	}

	return 0;
}

struct test_struct *get_test_struct(void)
{
	return g_test;
}

int init_test(void)
{
	struct test_struct *test = NULL;

	test = (struct test_struct *)malloc(sizeof(struct test_struct));
	if (test == NULL) {
		mt_error("malloc for test_struct faied\n");
		return -1;
	}

	g_test = test;

	return 0;
}
