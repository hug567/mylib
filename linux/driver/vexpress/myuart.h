/*
 * 串口驱动和用户态测试程序公共头文件
 * 2020-01-31
 */

enum myuart_ioctl_cmd {
	CMD_START = 0xF000,
	CMD_WRITE_CHAR,
};
