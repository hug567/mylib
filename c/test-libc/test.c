/*
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"

//struct TestModule *gTestModules = NULL;

char *g_modulesName[] = {
    "stdio",
    "stdlib",
    "string",
};

struct TestModule *g_modules = NULL;

int RegisterTestModules(const char *name)
{
    return 0;
}

void InitTestModules(void)
{
    int i;
    struct TestModule *new = NULL;
    struct TestModule *tail = NULL;
    int modulesNum = sizeof(g_modulesName) / sizeof(char *);
mt_log("modulesNum = %d\n", modulesNum);

    for (i = 0; i < modulesNum; i++) {
        new = (struct TestModule *)malloc(sizeof(struct TestModule));
        new->head = NULL;
        new->next = NULL;
        if (g_modules == NULL) {
            g_modules = new;
            tail = new;
        } else {
            tail->next = new;
            tail = tail->next;
        }
    }

}
