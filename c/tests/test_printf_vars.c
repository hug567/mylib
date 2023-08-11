/*
 * c语言可变参数
 * 2023-08-11
 */
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

static int my_vprintf(const char *fmt, va_list args)
{
	return 0;
}

#define MAX_LOG_BUF_SIZE 256
static int my_printf(const char *fmt, ...)
{
	int len;
	va_list args;
	char buf[MAX_LOG_BUF_SIZE] = {0};

	va_start(args, fmt);
	len = vsnprintf(buf, MAX_LOG_BUF_SIZE - 1, fmt, args);
	va_end(args);

	printf("%s", buf);

	return len;
}

#define my_log(fmt, ...) \
	my_printf("[%s:%d] " fmt, __func__, __LINE__)

int main(void)
{
	my_log("This is a log\n");

	return 0;
}
