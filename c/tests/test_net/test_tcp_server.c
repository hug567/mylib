/*
 * 测试：tcp server
 * 2023-09-09
 */
#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_BACKLOG 5
#define MAX_MESSAGE_LEN 1024

#define log_info(fmt, ...) \
	printf("[INFO ][%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define log_err(fmt, ...) \
	printf("[ERROR][%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)

static void usage(const char *name)
{
	printf("Usage: %s <port>    start tcp server with port\n", name);
}

static int read_message(int client_fd)
{
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
		} else if (rd_len == 0) { /* tcp client连接断开时read返回值为0 */
			break;
		}
		log_info("------------------------------------------------1\n");
		log_info("receive message: [%s]\n", buf);
		log_info("------------------------------------------------2\n");
	} while (rd_len > 0);

	free(buf);
	return 0;
}

static int write_message(int client_fd)
{
	time_t t;
	size_t len;
	int wr_len;
	char buf[128] = {0};

	do {
		time(&t);
		memset(buf, 0, 128);
		len = snprintf(buf, 128, "current time: %ld\n", t);
		if (len < 0) {
			log_err("snprintf current time failed\n");
			return -1;
		}
		wr_len = write(client_fd, buf, len);
		if (wr_len < 0) {
			log_err("write to client failed\n");
			return -1;
		} else if (wr_len == 0) {
			log_err("wr_len: %d\n", wr_len);
			break;
		}
		log_info("wr_len: %d\n", wr_len);
		sleep(1);
	} while (wr_len > 0);

	return 0;
}

static int start_tcp_server(int port)
{
	int ret;
	int sock_fd, client_fd;
	struct sockaddr_in serv_addr = {0}, client_addr;

	/* 忽略SIGPIPE信号，当tcp客户端连接断开时，不终止当前服务进程 */
	signal(SIGPIPE, SIG_IGN);

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

		/* 没有连接时阻塞在accept */
		log_info("will accept\n");
		client_fd = accept(sock_fd, (struct sockaddr *)(&client_addr),
				   &clnt_len);
		if (client_fd < 0) {
			log_err("accept failed\n");
			continue;
		}
		/* 有连接后accept结束，获取到正常client_fd */
		log_info("finish accept, client_fd: %d\n", client_fd);
#if 0
		ret = read_message(client_fd);
		if (ret < 0) {
			log_err("read message failed\n");
			close(client_fd);
			continue;
		}
#endif
		ret = write_message(client_fd);
		if (ret < 0) {
			log_err("write message failed\n");
			close(client_fd);
			continue;
		}
		close(client_fd);
	}

	log_info("finish tcp server\n");
	close(sock_fd);
	return 0;
}

int main(int argc, const char *argv[])
{
	int ret;
	int port;

	if (argc != 2) {
		usage(argv[0]);
		return -1;
	}
	port = atoi(argv[1]);
	printf("tcp server listen port: %d\n", port);

	ret = start_tcp_server(port);
	if (ret < 0) {
		printf("start tcp server failed\n");
		return ret;
	}
	return 0;
}
