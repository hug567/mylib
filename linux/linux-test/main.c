#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>

static int test_tcgetattr(void)
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

static int test_tcflow(int action)
{
	int ret;
	int fd = 0;

	printf("TCOOFF = %d, TCOON = %d, TCIOFF = %d, TCION = %d, action = %d\n",
	       TCOOFF, TCOON, TCIOFF, TCION, action);
	ret = tcflow(fd, action);
	if (ret < 0) {
		printf("tcflow failed, ret = %d, errno = %d\n", ret, errno);
		return -1;
	}

	return 0;
}

int main(int argc, char *argv[])
{
	int action = TCOON;
	printf("hello world in linux\n");

	if (argc == 2) {
		if (strcmp(argv[1], "OOFF") == 0) {
			action = TCOOFF;
		} else if (strcmp(argv[1], "OON") == 0) {
			action = TCOON;
		} else if (strcmp(argv[1], "IOFF") == 0) {
			action = TCIOFF;
		} else if (strcmp(argv[1], "ION") == 0) {
			action = TCION;
		} else {
			action = TCOON;
		}
	}

	printf("\n-------------------- test_tcgetattr -------------------\n");
	test_tcgetattr();
	printf("\n-------------------- test_tcflow -------------------\n");
	test_tcflow(action);

	return 0;
}
