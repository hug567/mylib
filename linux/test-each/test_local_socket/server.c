/*
 * 练习：本地socket通信
 * 时间：2023-10-30
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

#define UNIX_DOMAIN "/tmp/local_socket"
#define MAX_LISTEN_CONNECT 32
#define MSG_BUF_LEN 1024

#define hx_info(fmt, ...) \
	printf("[I][%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)

int main(void)
{
	int ret;
	int count = 0;
	char *msg_buf = NULL;
	int sock_fd, clt_fd = -1;
	struct sockaddr_un srv_addr, clt_addr;

	struct sigaction sa;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGPIPE, &sa, 0);

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
	unlink(UNIX_DOMAIN);
	ret = bind(sock_fd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
	if (ret < 0) {
		printf("bind listen fd failed\n");
		close(sock_fd);
		unlink(UNIX_DOMAIN);
		free(msg_buf);
		return -1;
	}

	ret = listen(sock_fd, MAX_LISTEN_CONNECT);
	if (ret < 0) {
		printf("listen client failed\n");
		close(sock_fd);
		unlink(UNIX_DOMAIN);
		free(msg_buf);
		return -1;
	}

	while (true) {
		int msg_len;
		socklen_t clt_len = sizeof(clt_addr);
		clt_fd = accept(sock_fd, (struct sockaddr *)(&clt_addr),
				   &clt_len);
		if (clt_fd < 0) {
			printf("accept failed\n");
			continue;
		}
		while (true) {
			count++;
			memset(msg_buf, 0, MSG_BUF_LEN);
			msg_len = snprintf(msg_buf, MSG_BUF_LEN, "accept count: %d", count);
			if (msg_len < 0) {
				printf("snprintf failed\n");
				break;
			}

			ret = write(clt_fd, msg_buf, msg_len);
			if (ret < 0) {
				printf("write to client failed\n");
				break;
			} else if (ret == 0) {
				printf("write to client 0 bytes\n");
				break;
			}
			sleep(1);
		}
		close(clt_fd);
	}

	close(clt_fd);
	close(sock_fd);
	unlink(UNIX_DOMAIN);
	free(msg_buf);
	return 0;
}
