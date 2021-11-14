/*
 * 获取termios信息
 * 2020-12-06
 */
#include "tty_debug.h"

struct ascii_str {
	char val;
	const char *str;
};

static tcflag_t g_baud[][2] = {
	{ B0      , 0       },
	{ B50     , 50      },
	{ B75     , 75      },
	{ B110    , 110     },
	{ B134    , 134     },
	{ B150    , 150     },
	{ B200    , 200     },
	{ B300    , 300     },
	{ B600    , 600     },
	{ B1200   , 1200    },
	{ B1800   , 1800    },
	{ B2400   , 2400    },
	{ B4800   , 4800    },
	{ B9600   , 9600    },
	{ B19200  , 19200   },
	{ B38400  , 38400   },
	{ B57600  , 57600   },
	{ B115200 , 115200  },
	{ B230400 , 230400  },
	{ B460800 , 460800  },
	{ B500000 , 500000  },
	{ B576000 , 576000  },
	{ B921600 , 921600  },
	{ B1000000, 1000000 },
	{ B1152000, 1152000 },
	{ B1500000, 1500000 },
	{ B2000000, 2000000 },
	{ B2500000, 2500000 },
	{ B3000000, 3000000 },
	{ B3500000, 3500000 },
	{ B4000000, 4000000 },
};

static struct ascii_str g_ascii_str[] = {
	{0x03, "Ctrl-C"},
};

/* 无符号整形的最低有效位, 从0开始 */
static int least_valid_bit(unsigned int val)
{
	int i;

	for (i = 0; i < 8 * sizeof(val); i++) {
		if ((val & 0x1) == 0x1) {
			return i;
		}
		val >>= 1;
	}

	return -1;
}

/* 计算指定掩码的值 */
static inline tcflag_t mask_value(tcflag_t val, tcflag_t mask)
{
	return (val & mask) >> least_valid_bit(mask);
}

/* 获取波特率数值 */
static int get_baud_value(tcflag_t baud)
{
	int i;
	int size = sizeof(g_baud) / sizeof(g_baud[0]);

	for (i = 0; i < size; i++) {
		if (g_baud[i][0] == baud) {
			return g_baud[i][1];
		}
	}
	return -1;
}

static void parse_c_iflag(tcflag_t c_iflag)
{
#define PRINT_C_IFLAG(flag) log_info(#flag " = %d\n", mask_value(c_iflag, flag))
	log_info("==================== c_iflag ====================\n");
	PRINT_C_IFLAG(IGNBRK);
	PRINT_C_IFLAG(BRKINT);
	PRINT_C_IFLAG(IGNPAR);
	PRINT_C_IFLAG(PARMRK);
	PRINT_C_IFLAG(INPCK);
	PRINT_C_IFLAG(ISTRIP);
	PRINT_C_IFLAG(INLCR);
	PRINT_C_IFLAG(IGNCR);
	PRINT_C_IFLAG(ICRNL);
	PRINT_C_IFLAG(IUCLC);
	PRINT_C_IFLAG(IXON);
	PRINT_C_IFLAG(IXANY);
	PRINT_C_IFLAG(IXOFF);
	PRINT_C_IFLAG(IMAXBEL);
	PRINT_C_IFLAG(IUTF8);
}

static void parse_c_oflag(tcflag_t c_oflag)
{
#define PRINT_C_OFLAG(flag) log_info(#flag " = %d\n", mask_value(c_oflag, flag))
	log_info("==================== c_oflag ====================\n");
	PRINT_C_OFLAG(OPOST);
	PRINT_C_OFLAG(OLCUC);
	PRINT_C_OFLAG(ONLCR);
	PRINT_C_OFLAG(OCRNL);
	PRINT_C_OFLAG(ONOCR);
	PRINT_C_OFLAG(ONLRET);
	PRINT_C_OFLAG(OFILL);
	PRINT_C_OFLAG(OFDEL);
}

static void parse_c_cflag(tcflag_t c_cflag)
{
#define PRINT_C_CFLAG(flag) log_info(#flag " = %d\n", mask_value(c_cflag, flag))
	log_info("==================== c_cflag ====================\n");
	log_info("CBAUD = %d\n", get_baud_value(c_cflag & CBAUD));
	log_info("CSIZE = %d\n", mask_value(c_cflag, CSIZE) + 5);
	PRINT_C_CFLAG(CSTOPB);
	PRINT_C_CFLAG(CREAD);
	PRINT_C_CFLAG(PARENB);
	if (c_cflag & PARENB) {
		PRINT_C_CFLAG(PARODD);
	}
	PRINT_C_CFLAG(HUPCL);
	PRINT_C_CFLAG(CLOCAL);
}

static void parse_c_lflag(tcflag_t c_lflag)
{
#define PRINT_C_LFLAG(flag) log_info(#flag " = %d\n", mask_value(c_lflag, flag))
	log_info("==================== c_lflag ====================\n");
	PRINT_C_LFLAG(ISIG);
	PRINT_C_LFLAG(ICANON);
	PRINT_C_LFLAG(ECHO);
	PRINT_C_LFLAG(ECHOE);
	PRINT_C_LFLAG(ECHOK);
	PRINT_C_LFLAG(ECHONL);
	PRINT_C_LFLAG(NOFLSH);
	PRINT_C_LFLAG(TOSTOP);
	PRINT_C_LFLAG(IEXTEN);
}

static void parse_c_cc(const cc_t *c_cc)
{
#define PRINT_C_CC(flag) log_info("c_cc[" #flag "]\t = 0x%02x\n", c_cc[flag])
	log_info("===================== c_cc ======================\n");
	PRINT_C_CC(VINTR);
	PRINT_C_CC(VQUIT);
	PRINT_C_CC(VERASE);
	PRINT_C_CC(VKILL);
	PRINT_C_CC(VEOF);
	PRINT_C_CC(VTIME);
	PRINT_C_CC(VMIN);
	PRINT_C_CC(VSWTC);
	PRINT_C_CC(VSTART);
	PRINT_C_CC(VSTOP);
	PRINT_C_CC(VSUSP);
	PRINT_C_CC(VEOL);
	PRINT_C_CC(VREPRINT);
	PRINT_C_CC(VDISCARD);
	PRINT_C_CC(VWERASE);
	PRINT_C_CC(VLNEXT);
	PRINT_C_CC(VEOL2);
}

static void dump_termios_detail(const struct termios *tio)
{
	parse_c_iflag(tio->c_iflag);
	parse_c_oflag(tio->c_oflag);
	parse_c_cflag(tio->c_cflag);
	parse_c_lflag(tio->c_lflag);
	parse_c_cc(tio->c_cc);
}

static void __dump_termios(const struct termios *tio)
{
	int i;

	log_info("c_iflag = 0x%x\n", tio->c_iflag);
	log_info("c_oflag = 0x%x\n", tio->c_oflag);
	log_info("c_cflag = 0x%x\n", tio->c_cflag);
	log_info("c_lflag = 0x%x\n", tio->c_lflag);
	log_info("c_cc: ");
	for (i = 0; i < NCCS; i++) {
		printf("%02x ", tio->c_cc[i]);
	}
	printf("\n");
}

static int get_termios(int fd, struct termios *tio)
{
	int ret;

	if (fd < 0 || tio == NULL) {
		return -EINVAL;
	}

	if (!isatty(fd)) {
		log_error("%d is not a tty device\n", fd);
		return -1;
	}
	log_info("termios: %s\n", ttyname(fd));

	ret = tcgetattr(fd, tio);
	if (ret < 0) {
		log_error("tcgetattr failed\n");
		return ret;
	}

	return 0;
}

int dump_termios(int fd)
{
	int ret;
	struct termios tio;

	ret = get_termios(fd, &tio);
	if (ret < 0) {
		log_error("tcgetattr failed\n");
		return ret;
	}

	__dump_termios(&tio);

	return 0;
}

#if 0
static int update_fd(const char *tty_name)
{
	g_fd = open(tty_name, O_RDWR);
	if (g_fd < 0) {
		log_error("open %s failed\n", tty_name);
		return -1;
	}

	if (!isatty(g_fd)) {
		log_error("%s is not a tty device\n", tty_name);
		return -1;
	}

	return 0;
}

int main(int argc, char *argv[])
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
			g_dump_detail_flag = true;
			break;
		default:
			usage(argv[0]);
			return -1;
		}
	}

	log_info("tty name: %s\n", ttyname(g_fd));

	ret = get_termios(g_fd, &g_tio);
	if (ret < 0) {
		return ret;
	}

	dump_termios(&g_tio);
	if (g_dump_detail_flag) {
		dump_termios_detail(&g_tio);
	}

	return 0;
}
#endif
