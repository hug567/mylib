#include <stdio.h>

#define mt_log(...) printf("[mytest]: "__VA_ARGS__)

int main(void)
{
	mt_log("hello mt_log\n");
	return 0;
}
