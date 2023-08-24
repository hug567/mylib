/*
 * 测试系统大小端
 * 2023-08-34
 */
#include <stdio.h>

static void test_endian(void)
{
	unsigned int num = 1;
	unsigned char *byte = (unsigned char *)&num;

	if (*byte == 1) {
		printf("Little Endian\n");
	} else {
		printf("Big Endian\n");
	}
}

int main(void)
{
    test_endian();

    return 0;
}
