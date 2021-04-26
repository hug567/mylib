/*
 * 串口驱动测试程序
 * 2020-01-31
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include "myuart.h"

#define test_info(fmt, ...)  printf("[TESF][INFO ][%s@%d]: " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define test_error(fmt, ...) printf("[TEST][ERROR][%s@%d]: " fmt, __func__, __LINE__, ##__VA_ARGS__)

#define DEV_NAME "/dev/myuart"

int write_char(int fd, char ch)
{
	int ret;
	ret = ioctl(fd, CMD_WRITE_CHAR, ch);
	if (ret < 0) {
		test_error("ioctl CMD_WRITE_CHAR failed\n");
		return -1;
	}
	return 0;
}

int main(void)
{
	int i;
	int ret;
	int fd = -1;

	fd = open(DEV_NAME, O_RDWR);
	if (fd < 0) {
		test_error("open %s failed\n", DEV_NAME);
		return -1;
	}
	test_info("open %s success\n", DEV_NAME);

	test_info("will write char to %s by ioctl\n", DEV_NAME);
	for (i = 0; i < 10; i++) {
		ret = write_char(fd, 'A');
		if (ret < 0) {
			close(fd);
			return ret;
		}
	}
	write_char(fd, '\r');
	write_char(fd, '\n');

	test_info("will close %s\n", DEV_NAME);
	close(fd);
	return 0;
}
