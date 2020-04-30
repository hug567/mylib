/*
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"

struct TestModule *g_modules = NULL;

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

int init_test_modules(const char **modules, const int count)
{
	int i;

	if (modules == NULL || count <= 0) {
		mt_error("There are no modules to initialize\n");
		return -1;
	}
	for (i = 0; i < count; i++) {
		add_test_module(modules[i]);
	}
	return 0;
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

int run_one_module(const char *name)
{
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
		return tcase->func();
	}

	return -1;
}
