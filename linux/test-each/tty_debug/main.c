/*
 * 功能：tty调试工具
 * 2020-12-06
 */
#include "common.h"

void usage(const char *name)
{
	printf("Usage:\n");
	printf("%s -d                  dump termios info\n", name);
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

	dump_termios(fd);

	close(fd);
	return 0;
}
