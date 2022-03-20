/*
 * 测试：自定义程序抢占shell的控制终端，程序结束后返还
 * 2022-03-19
 */
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <termios.h>
#include <sys/wait.h>
#include <sys/ioctl.h>

#define log(fmt, ...) \
	printf("[%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)

int listening_input(void)
{
	char ch;
	int ret;
	int fd = 0;
	struct termios tio, old_tio;

	/* 将当前进程所在进程组设置为前台进程组 */
	ret = tcsetpgrp(fd, getpid());
	if (ret < 0) {
		log("tcsetpgrp failed, errno: %s\n", strerror(errno));
		return ret;
	}

	ret = tcgetattr(fd, &tio);
	if (ret < 0) {
		log("tcgetattr failed, errno: %s\n", strerror(errno));
		return ret;
	}
	memcpy(&old_tio, &tio, sizeof(struct termios));

	tio.c_cc[VMIN] = 1;
	tio.c_cc[VTIME] = 0;
	tio.c_lflag &= ~(ECHO | ICANON);

	ret = tcsetattr(fd, TCSANOW, &tio);
	if (ret < 0) {
		log("tcsetattr failed, errno: %s\n", strerror(errno));
		return ret;
	}

	printf("[hi] # ");
	fflush(stdout);
	while (true) {
		ret = read(fd, &ch, sizeof(ch));
		if (ret < 0) {
			log("read failed, errno: %s\n", strerror(errno));
			break;
		} else if (ret == 0) {
			log("read no char\n");
			continue;
		}
		if (ch == 0x18) { /* Ctrl-X */
			log("receive Ctrl-X, will exit\n");
			break;
		}
		printf("%c", ch);
		printf("\n[hi] # ");
		fflush(stdout);
	}

	ret = tcsetattr(fd, TCSANOW, &old_tio);
	if (ret < 0) {
		log("tcsetattr failed, errno: %s\n", strerror(errno));
		return ret;
	}
	return 0;
}

int main(void)
{
	return listening_input();
}
