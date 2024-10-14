/*
 * 测试：udp server
 * 2024-10-12
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

#define MAX_MESSAGE_LEN 1024

#define log_info(fmt, ...) \
	printf("[INFO ][%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define log_warn(fmt, ...) \
	printf("[WARN ][%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define log_err(fmt, ...) \
	printf("[ERROR][%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)

static void usage(const char *name)
{
	printf("Usage: %s <port>    start udp server with port\n", name);
}

static int start_udp_server(int port)
{
	int ret;
	int sock_fd;
	char *buf = NULL;
	int recv_len, send_len;
	struct sockaddr_in serv_addr = {0}, client_addr = {0};
	socklen_t addr_len = sizeof(client_addr);

	sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
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

	buf = malloc(MAX_MESSAGE_LEN + 1);
	if (buf == NULL) {
		log_err("malloc buf for receiving message failed\n");
		close(sock_fd);
		return -1;
	}

	while(true) {
		(void)memset(buf, 0, MAX_MESSAGE_LEN + 1);
		recv_len = recvfrom(sock_fd, buf, MAX_MESSAGE_LEN, 0,
				    (struct sockaddr *)&client_addr, &addr_len);
		if (recv_len < 0) {
			log_warn("receive message from client failed, errno: "
				 "%s\n", strerror(errno));
			break;
		}
		log_info("receive message(%d): %s\n", recv_len, buf);

		send_len = sendto(sock_fd, buf, recv_len, 0,
				  (struct sockaddr *)&client_addr, addr_len);
		if (send_len < 0) {
			log_warn("send message to client failed, errno: %s\n",
				 strerror(errno));
			break;
		}
	}

	log_info("finish udp server\n");
	free(buf);
	close(sock_fd);
	return 0;
}

static int start_server_loop(int port)
{
	int ret;

	while (true) {
		ret = start_udp_server(port);
		if (ret < 0) {
			log_err("start udp server failed\n");
		}
	}

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
	printf("udp server listen port: %d\n", port);

	ret = start_server_loop(port);
	if (ret < 0) {
		printf("start udp server failed\n");
		return ret;
	}

	return 0;
}
