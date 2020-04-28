/*
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"

struct TestModule *g_modules = NULL;

void AddTestModule(const char *moduleName)
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
		tmp->next = NULL;
	}
}

void AddTestCase(const char *moduleName, const char *caseName, TestFunc *func)
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

int RunTestCase(struct TestMode *module, struct TestCase *Case)
{
	return 0;
}

int RunTestModule(struct TestMode *module)
{
	return 0;
}
