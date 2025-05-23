/*
 * 进程间通信：FIFO
 * Create: 2025-05-23 09:32:46
 */
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

#define TEST_FIFO_FILE "/tmp/cfifo"

static int parent_fifo_write(void)
{
	int ret, fd;
	int num = 0;

	mkfifo(TEST_FIFO_FILE, 0666);
	fd = open(TEST_FIFO_FILE, O_WRONLY);
	if (fd < 0) {
		printf("open file %s fail\n", TEST_FIFO_FILE);
		return -1;
	}
	printf("open fifo file success, fd: %d\n", fd);

	while (1) {
		/*
		 * 写端写几次后不写了，不写后读端会阻塞
		 * 重新开始写后，读端可继续读取
		 */
		if (num > 10 && num < 20) {
			num++;
			sleep(1);
			continue;
		}
		ret = write(fd, &num, sizeof(num));
		if (ret < 0) {
			printf("write to fifo file fail\n");
			return ret;
		}
		printf("write num to fifo success: %d\n", num);
		num++;
		sleep(1);
	}

	return 0;
}

static int child_fifo_read(void)
{
	int ret, fd;
	int num = 0;

	fd = open(TEST_FIFO_FILE, O_RDONLY);
	if (fd < 0) {
		printf("open fifo file %s fail\n", TEST_FIFO_FILE);
		return -1;
	}

	while (1) {
		ret = read(fd, &num, sizeof(num));
		if (ret == 0) {
			printf("read nothing from fifo\n");
			return 1;
		} else if (ret != sizeof(num)) {
			printf("read dinfo from fifo fail, ret: %d\n", ret);
			return -1;
		} else {
			printf("read from fifo success with num: %d\n", num);
		}
	}


	return 0;
}

int main(int argc, const char *argv[])
{
	pid_t pid;

	pid = fork();
	if (pid == 0) {
		return child_fifo_read();
	} else if (pid > 0) {
		return parent_fifo_write();
	} else {
		printf("fork failed\n");
		return -EFAULT;
	}

	return 0;
}
