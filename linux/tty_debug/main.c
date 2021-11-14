/*
 * 功能：tty调试工具
 * 2020-12-06
 */
#include "tty_debug.h"

#define SHORT_OPTION ":dth"
#define OPTION_DUMP_DETAIL (1 << 0)

static int g_fd = 0; /* current terminal */
static unsigned int g_options = 0;

static void usage(const char *name)
{
	printf("Usage:\n");
	printf("%s                  dump current terminal termios info\n", name);
	printf("%s -t               dump current terminal detail termios info\n", name);
	printf("%s -d /dev/xxx      dump /dev/xxx termios info\n", name);
	printf("%s -d /dev/xxx -t   dump /dev/xxx detail termios info\n", name);
	printf("%s -h               print help info\n", name);
	printf("%s -c IXON 1/0      enable/disable current terminal IXON\n", name);
}

static int update_fd(const char *name)
{
	int fd = -1;

	fd = open(name, O_RDWR);
	if (fd < 0) {
		log_error("open %s failed\n", name);
		return -1;
	}
	g_fd = fd;
	return 0;
}

int main(int argc, const char *argv[])
{
	int ret;
	int opt;

	while ((opt = getopt(argc, argv, SHORT_OPTION)) != -1) {
		switch (opt) {
		case 'd' :
			ret = update_fd(argv[optind]);
			if (ret < 0) {
				return ret;
			}
			break;
		case 't' :
			g_options |= OPTION_DUMP_DETAIL;
			break;
		case 'h' :
			usage(argv[0]);
			return 0;
		default:
			usage(argv[0]);
			return -1;
		}
	}

	ret = dump_termios(g_fd);
	if (ret < 0) {
		log_error("dump termios info failed\n");
		return ret;
	}
	return 0;
}
