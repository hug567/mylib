/*
 * 简介：验证fork创建子进程
 * 系统：Linux (ubuntu 18.04)
 * 时间：2020-03-29
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t pid, pid1;

	pid = fork();

	if (pid < 0) {
		printf("fork failed\n");
		return -1;
	/* child process */
	} else if (pid == 0) {
		pid1 = getpid();
		printf("child: pid = %d\n", pid); /* 0 */
		printf("child: pid1 = %d\n", pid1); /* child pid */
	/* parent process */
	} else {
		wait(NULL); /* wait child process end */
		pid1 = getpid();
		printf("parent: pid = %d\n", pid); /* child pid */
		printf("parent: pid1 = %d\n", pid1); /* parent pid */
	}
	return 0;
}
