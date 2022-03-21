/*
 * 公共头文件
 * 2022-03-20
 */
#ifndef __TESTS_COMMON_H__
#define __TESTS_COMMON_H__

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <termios.h>
#include <sys/wait.h>
#include <sys/ioctl.h>

#define log_info(fmt, ...) \
	printf("[%s:%d][INFO ] " fmt, __func__, __LINE__, ##__VA_ARGS__)

#define log_error(fmt, ...) \
	printf("[%s:%d][ERROR] " fmt, __func__, __LINE__, ##__VA_ARGS__)

#endif
