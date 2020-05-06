/*
 * Description:
 * Author: huangxing567@163.com
 * Create: 2020.05.03 17:06
 */
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "../test.h"

#define LOG_FILE "/tmp/debug.log"

int test_write(void)
{
	mt_info("Enter %s success\n", __func__);

	int ret;
	int fd = -1;
	char *log = "start write log to file\n";

	ret = access(LOG_FILE, 0);
	if (ret < 0) {
		mt_info("%s does not exist, will create it\n", LOG_FILE);
		fd = creat(LOG_FILE, S_IRUSR | S_IWUSR);
		if (fd < 0) {
			mt_error("create %s failed\n", LOG_FILE);
			return -1;
		}
	}

	fd = open(LOG_FILE, O_RDWR | O_APPEND);
	if (fd < 0) {
		mt_error("open %s failed\n", LOG_FILE);
		return -1;
	}

	ret = write(fd, log, strlen(log));
	if (ret < 0) {
		mt_error("write to %s failed\n", LOG_FILE);
	}

	close(fd);
	return 0;
}
