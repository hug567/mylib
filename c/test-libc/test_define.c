#include <stdio.h>

#define mt_log(...) printf("[mytest]: "__VA_ARGS__)
#define mt_info(fmt, ...) printf("[mytest][INFO][%s@%d]: " fmt, __func__, __LINE__, ##__VA_ARGS__)

int main(void)
{
	mt_log("hello mt_log\n");
	mt_info("Enter %s success\n", __func__);
	return 0;
}
