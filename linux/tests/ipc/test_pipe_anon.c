/*
 * linux IPC: 匿名管道，半双工，只能在父子或兄弟进程间通讯
 * 2022-06-24
 */
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUF_SIZE 32

#define log_info(fmt, ...) \
	printf("[INFO ][%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define log_error(fmt, ...) \
	printf("[ERROR][%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)

void child_process(int pipe_rd_fd)
{
	int ret;
	char buf[BUF_SIZE] = {0};

	ret = read(pipe_rd_fd, buf, BUF_SIZE);
	if (ret < 0) {
		log_error("child read from pipe failed, errno: %d\n", errno);
	} else {
		log_info("child read from pipe success, msg: [%s]\n", buf);
	}
}

void parent_process(int pipe_wr_fd)
{
	int ret;
	char buf[BUF_SIZE] = {"test anon pipe message"};

	ret = write(pipe_wr_fd, buf, strlen(buf));
	if (ret < 0) {
		log_error("parent write to pipe failed, errno: %d\n", errno);
	} else {
		log_info("parent write to pipe success\n");
	}
}

int main(void)
{
	int ret;
	int fds[2];
	pid_t pid;

	ret = pipe(fds);
	if (ret < 0) {
		log_error("pipe failed, errno: %d\n", errno);
		return ret;
	}

	pid = fork();
	if (pid < 0) {
		log_error("fork failed, errno: %d\n", errno);
	} else if (pid > 0) {
		close(fds[1]); /* 子进程关闭写，只读 */
		child_process(fds[0]);
	} else {
		close(fds[0]); /* 子进程关闭读，只写 */
		parent_process(fds[1]);
	}
	wait(NULL);

	return 0;
}
