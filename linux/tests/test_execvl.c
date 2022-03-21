/*
 * 测试：学习execvl函数
 * 2022-03-20
 */
#include "common.h"

int main(void)
{
	pid_t pid;

	pid = fork();
	if (pid < 0) {
		log_error("fork failed with errno: %s\n", strerror(errno));
		return pid;
	}
	return 0;
}
