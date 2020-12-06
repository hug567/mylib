/*
 * 获取termios信息
 * 2020-12-06
 */
#include "common.h"

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
	log_info("==================== c_iflag ====================\n");
}

static void parse_c_oflag(tcflag_t c_oflag)
{
	log_info("==================== c_oflag ====================\n");
}

static void parse_c_cflag(tcflag_t c_cflag)
{
	log_info("==================== c_cflag ====================\n");
	log_info("CBAUD = %d\n", get_baud_value(c_cflag & CBAUD));
	log_info("CSIZE = %d\n", mask_value(c_cflag, CSIZE) + 5);
	log_info("CSTOPB = %d\n", mask_value(c_cflag, CSTOPB));
	log_info("CREAD = %d\n", mask_value(c_cflag, CREAD));
	log_info("PARENB = %d\n", mask_value(c_cflag, PARENB));
	if (c_cflag & PARENB) {
		log_info("PARODD = %d (0: even, 1: odd)\n", mask_value(c_cflag, PARODD));
	}
	log_info("HUPCL = %d\n", mask_value(c_cflag, HUPCL));
	log_info("CLOCAL = %d\n", mask_value(c_cflag, CLOCAL));
}

static void parse_c_lflag(tcflag_t c_lflag)
{
	log_info("==================== c_lflag ====================\n");
	log_info("ISIG = %d\n", mask_value(c_lflag, ISIG));
	log_info("ICANON = %d\n", mask_value(c_lflag, ICANON));
	log_info("ECHO = %d\n", mask_value(c_lflag, ECHO));
	log_info("ECHOE = %d\n", mask_value(c_lflag, ECHOE));
	log_info("ECHOK = %d\n", mask_value(c_lflag, ECHOK));
	log_info("ECHONL = %d\n", mask_value(c_lflag, ECHONL));
	log_info("NOFLSH = %d\n", mask_value(c_lflag, NOFLSH));
	log_info("TOSTOP = %d\n", mask_value(c_lflag, TOSTOP));
}

static void parse_c_cc(const cc_t *c_cc)
{
	log_info("===================== c_cc ======================\n");
	log_info("c_cc[VINTR   ] = %d\n", c_cc[VINTR   ]);
	log_info("c_cc[VQUIT   ] = %d\n", c_cc[VQUIT   ]);
	log_info("c_cc[VERASE  ] = %d\n", c_cc[VERASE  ]);
	log_info("c_cc[VKILL   ] = %d\n", c_cc[VKILL   ]);
	log_info("c_cc[VEOF    ] = %d\n", c_cc[VEOF    ]);
	log_info("c_cc[VTIME   ] = %d\n", c_cc[VTIME   ]);
	log_info("c_cc[VMIN    ] = %d\n", c_cc[VMIN    ]);
	log_info("c_cc[VSWTC   ] = %d\n", c_cc[VSWTC   ]);
	log_info("c_cc[VSTART  ] = %d\n", c_cc[VSTART  ]);
	log_info("c_cc[VSTOP   ] = %d\n", c_cc[VSTOP   ]);
	log_info("c_cc[VSUSP   ] = %d\n", c_cc[VSUSP   ]);
	log_info("c_cc[VEOL    ] = %d\n", c_cc[VEOL    ]);
	log_info("c_cc[VREPRINT] = %d\n", c_cc[VREPRINT]);
	log_info("c_cc[VDISCARD] = %d\n", c_cc[VDISCARD]);
	log_info("c_cc[VWERASE ] = %d\n", c_cc[VWERASE ]);
	log_info("c_cc[VLNEXT  ] = %d\n", c_cc[VLNEXT  ]);
	log_info("c_cc[VEOL2   ] = %d\n", c_cc[VEOL2   ]);
}

int print_termios(const struct termios *tio)
{
	int i;

	if (tio == NULL) {
		return -EINVAL;
	}
	log_info("==================== termios ====================\n");
	log_info("c_iflag = 0x%x\n", tio->c_iflag);
	log_info("c_oflag = 0x%x\n", tio->c_oflag);
	log_info("c_cflag = 0x%x\n", tio->c_cflag);
	log_info("c_lflag = 0x%x\n", tio->c_lflag);
	log_info("c_cc: ");
	for (i = 0; i < NCCS; i++) {
		printf("%d ", tio->c_cc[i]);
	}
	printf("\n");

	parse_c_iflag(tio->c_iflag);
	parse_c_oflag(tio->c_oflag);
	parse_c_cflag(tio->c_cflag);
	parse_c_lflag(tio->c_lflag);
	parse_c_cc(tio->c_cc);

	return 0;
}

int get_termios(int fd, struct termios *tio)
{
	int ret;

	if (fd < 0 || tio == NULL) {
		return -EINVAL;
	}
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

	if (fd < 0) {
		return -EINVAL;
	}

	ret = get_termios(fd, &tio);
	if (ret < 0) {
		log_error("get termios failed\n");
		return ret;
	}

	ret = print_termios(&tio);
	if (ret < 0) {
		log_error("print termios failed\n");
		return ret;
	}

	return 0;
}
