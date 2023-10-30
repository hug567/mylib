/*
 * 练习：本地socket通信
 * 时间：2023-10-30
 */
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/un.h>
#include <sys/socket.h>

#define UNIX_DOMAIN "/tmp/local_socket"
#define MSG_BUF_LEN 1024

int main(void)
{
	int ret;
	char *msg_buf = NULL;
	int sock_fd;
	struct sockaddr_un srv_addr;

	msg_buf = malloc(MSG_BUF_LEN);
	if (msg_buf == NULL) {
		printf("malloc message buf failed\n");
		return -1;
	}

	sock_fd = socket(PF_UNIX, SOCK_STREAM, 0);
	if (sock_fd < 0) {
		printf("create socket failed\n");
		free(msg_buf);
		return -1;
	}

	srv_addr.sun_family = AF_LOCAL;
	strncpy(srv_addr.sun_path, UNIX_DOMAIN, sizeof(srv_addr.sun_path) - 1);

	ret = connect(sock_fd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
	if (ret < 0) {
		printf("connect to server failed\n");
		return -1;
	}

	while (true) {
		memset(msg_buf, 0, MSG_BUF_LEN);
		ret = read(sock_fd, msg_buf, MSG_BUF_LEN - 1);
		if (ret < 0) {
			printf("read from server failed, errno: %d(%s)\n", errno, strerror(errno));
			break;
		} else if (ret == 0) {
			printf("read 0 bytes from server\n");
			break;
		}
		printf("read form server: [%s]\n", msg_buf);
	}

	close(sock_fd);
	free(msg_buf);
	return 0;
}
