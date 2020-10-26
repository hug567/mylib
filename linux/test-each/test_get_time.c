/*
 * 获取系统时间
 */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define TIME_STR_LEN 20
char g_time_str[TIME_STR_LEN];

char *get_cur_time(void)
{
	time_t now;
	struct tm *tm = NULL;

	now = time(NULL);
	if (now < 0) {
		return NULL;
	}

	tm = localtime(&now);
	if (tm == NULL) {
		return NULL;
	}
	memset(g_time_str, 0, TIME_STR_LEN);
	sprintf(g_time_str, "%4d-%02d-%02d %02d-%02d-%02d",
		tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
		tm->tm_hour, tm->tm_min, tm->tm_sec);

	return g_time_str;
}

#define mt_info(fmt, ...)  \
	printf("[%s][INFO][%s@%d]: "  fmt, get_cur_time(), __func__, __LINE__, ##__VA_ARGS__)

int main(void)
{
	printf("current time is: [%s]\n", get_cur_time());
	mt_info("current time is: [%s]\n", get_cur_time());
	sleep(1);
	mt_info("current time is: [%s]\n", get_cur_time());
	sleep(1);
	mt_info("current time is: [%s]\n", get_cur_time());
	sleep(1);
	mt_info("current time is: [%s]\n", get_cur_time());
	sleep(1);
	mt_info("current time is: [%s]\n", get_cur_time());
	sleep(1);
	mt_info("current time is: [%s]\n", get_cur_time());
	sleep(1);
	mt_info("current time is: [%s]\n", get_cur_time());

	return 0;
}
