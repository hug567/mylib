/*
 * 公共头文件
 * 2020-12-06
 */
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <termios.h>
#include <sys/stat.h>
#include <sys/types.h>

#define log_info(fmt, ...)  printf("[INFO ][%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define log_error(fmt, ...) printf("[ERROR][%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)

//int print_termios(const struct termios *tio);
//int get_termios(int fd, struct termios *tio);
//int dump_termios(int fd);
