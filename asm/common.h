/*
 * 描述：公共头文件
 * 时间：2020-12-09
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define log_info(fmt, ...)  printf("[INFO ][%s@%d]: " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define log_error(fmt, ...) printf("[ERROR][%s@%d]: " fmt, __func__, __LINE__, ##__VA_ARGS__)
