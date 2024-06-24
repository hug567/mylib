/*
 * 循环缓冲区操作
 * 2024.6.24
 */
#include <stdio.h>

#define MAX_BUF_SIZE 32
struct ring_buf {
	char buf[MAX_BUF_SIZE];
	size_t head;
	size_t tail;
	size_t len;
}

static int init_ring_buf(struct ring_buf *rbuf)
{
	if (rbuf == NULL) {
		return -1;
	}
	(void)memset(rbuf->buf, 0, MAX_BUF_SIZE);
	rbuf->head = 0;
	rbuf->tail = 0;
	rbuf->len = 0;

	return 0;
}

/* 允许覆盖时的写入 */
static int write_to_ring_buf(struct ring_buf *rbuf, const char *buf, size_t len)
{
}


/******************************************************************************/
static int test_ring_buf(void)
{
	return 0;
}

int main(void)
{
	return 0;
}
