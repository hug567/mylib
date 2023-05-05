#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>

#define LogInfo(fmt, ...) \
        printf("[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)

#endif