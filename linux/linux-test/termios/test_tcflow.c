#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>

int test_tcgetattr(void)
{
	int ret;
	int fd = 0;
	struct termios tio;

	ret = tcgetattr(fd, &tio);
	if (ret < 0) {
		printf("tcgetattr failed, ret = %d, errno = %d\n", ret, errno);
		return -1;
	}

	printf("tio.c_iflag = 0x%x\n", tio.c_iflag);
	printf("tio.c_oflag = 0x%x\n", tio.c_oflag);
	printf("tio.c_cflag = 0x%x\n", tio.c_cflag);
	printf("tio.c_lflag = 0x%x\n", tio.c_lflag);
	printf("tio.c_cc = %s\n", tio.c_cc);

	return 0;
}

int test_tcflow_ooff(void)
{
	int ret;
	int fd = 0;

	ret = tcflow(fd, TCOOFF);
	if (ret < 0) {
		printf("tcflow TCOOFF failed, ret = %d, errno = %d\n", ret, errno);
		return -1;
	}

	return 0;
}

int test_tcflow_oon(void)
{
	int ret;
	int fd = 0;

	ret = tcflow(fd, TCOON);
	if (ret < 0) {
		printf("tcflow TCOON failed, ret = %d, errno = %d\n", ret, errno);
		return -1;
	}

	return 0;
}

int test_tcflow_ioff(void)
{
	int ret;
	int fd = 0;

	ret = tcflow(fd, TCIOFF);
	if (ret < 0) {
		printf("tcflow TCIOFF failed, ret = %d, errno = %d\n", ret, errno);
		return -1;
	}

	return 0;
}

int test_tcflow_ion(void)
{
	int ret;
	int fd = 0;

	ret = tcflow(fd, TCION);
	if (ret < 0) {
		printf("tcflow TCION failed, ret = %d, errno = %d\n", ret, errno);
		return -1;
	}

	return 0;
}
