/*
 * 测试：tcp server
 * 2023-09-09
 */
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_BACKLOG 5
#define MAX_MESSAGE_LEN 1024

#define log_info(fmt, ...) \
	printf("[INFO ][%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define log_err(fmt, ...) \
	printf("[ERROR][%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)

static int read_message(int client_fd)
{
	int ret;
	int rd_len;
	char *buf = NULL;

	buf = malloc(MAX_MESSAGE_LEN + 1);
	if (buf == NULL) {
		log_err("malloc for recv msg failed\n");
		return -ENOMEM;
	}
	do {
		(void)memset(buf, 0, MAX_MESSAGE_LEN + 1);
		rd_len = read(client_fd, buf, MAX_MESSAGE_LEN);
		if (rd_len < 0) {
			log_err("read from client failed\n");
			free(buf);
			return -1;
		} else if (rd_len == 0) {
			break;
		}
		log_info("------------------------------------------------1\n");
		log_info("receive message: [%s]\n", buf);
		log_info("------------------------------------------------2\n");
	} while (rd_len > 0);

	free(buf);
	return 0;
}

static int start_server(int port)
{
	int ret;
	int sock_fd, client_fd;
	struct sockaddr_in serv_addr = {0}, client_addr;

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0) {
		log_err("create socket failed\n");
		return -1;
	}
	log_info("finish create socket\n");

	(void)memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port);

	ret = bind(sock_fd, (struct sockaddr *)(&serv_addr), sizeof(serv_addr));
	if (ret < 0) {
		log_err("bind port %d failed\n", port);
		close(sock_fd);
		return -1;
	}
	log_info("finish bind\n");

	ret = listen(sock_fd, MAX_BACKLOG);
	if (ret < 0) {
		log_err("listen failed\n");
		close(sock_fd);
		return -1;
	}
	log_info("finish listen\n");
	log_info("start tcp server with port: %d\n", port);

	while (true) {
		socklen_t clnt_len = sizeof(client_addr);
		client_fd = accept(sock_fd, (struct sockaddr *)(&client_addr),
				   &clnt_len);
		if (client_fd < 0) {
			log_err("accept failed\n");
			continue;
		}
		log_info("finish accept\n");
		ret = read_message(client_fd);
		if (ret < 0) {
			log_err("read message failed\n");
			continue;
		}
	}

	log_info("finish tcp server\n");
	close(sock_fd);
	return 0;
}

int main(void)
{
	start_server(1234);
	return 0;
}
