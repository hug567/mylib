/*
 * Description: xxx
 * Author: huangxing567@163.com
 * Create: 2020-05-17 11:13:22
 */
#include <unistd.h>
#include <sys/ioctl.h>
#include "../test.h"

#define PL011_IOCTL_DEBUG 0xF00FU

int test_ttyname(void)
{
	int ret;
	int fd = 0;

	mt_info("ttyname(%d) = %s\n", fd, ttyname(fd));
	ret = ioctl(fd, PL011_IOCTL_DEBUG, 0);
	if (ret < 0) {
		mt_error("ioctl failed\n");
	}

	return 0;
}
