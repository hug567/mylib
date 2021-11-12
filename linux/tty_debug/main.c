/*
 * 功能：tty调试工具
 * 2020-12-06
 */
#include "common.h"

static int g_fd;

static void usage(const char *name)
{
	printf("Usage:\n");
	printf("%s                  dump current terminal termios info\n", name);
	printf("%s -t               dump current terminal detail termios info\n", name);
	printf("%s -d /dev/xxx      dump /dev/xxx termios info\n", name);
	printf("%s -d /dev/xxx -t   dump /dev/xxx detail termios info\n", name);
	printf("%s -h               print help info\n", name);
}

int main(void)
{
	int fd;
	char *name = NULL;

	name = ttyname(0);
	log_info("ttyname(0) = %s\n", name);

	fd = open(name, O_RDWR);
	if (fd < 0) {
		log_error("open %s failed\n", name);
		return -1;
	}
	log_info("open %s success\n", name);

	//dump_termios(fd);

	close(fd);
	return 0;
}
