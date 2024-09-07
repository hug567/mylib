/*
 * unix时间戳转UTC时间
 * UTC时间转北京时间：北京时间 = UTC时间 + 8小时
 * 2024-09-07
 */
#include <time.h>
#include <stdio.h>
#include <string.h>

static int get_timestamp_utc(time_t *timestamp)
{
	int ret;
	time_t rawtime;

	if (timestamp == NULL) {
		return -1;
	}
	ret = time(&rawtime);
	if (ret < 0) {
		return -1;
	}
	*timestamp = rawtime;

	return 0;
}

static int get_timestamp_gmt8(time_t *timestamp)
{
	int ret;
	time_t rawtime;

	if (timestamp == NULL) {
		return -1;
	}
	ret = time(&rawtime);
	if (ret < 0) {
		return -1;
	}
	/* UTC timestamp to GMT+8 */
	*timestamp = rawtime + 8 * 60 * 60;

	return 0;
}

static time_t utc_timestamp_to_gmt8(time_t tsp)
{
	return tsp + 8 * 60 * 60;
}

static int timestamp_to_readable(time_t time, char *buf, int size)
{
	int wr_len;
	struct tm tm_info = {0};
	struct tm *tm_ret = NULL;

	if (buf == NULL) {
		return -1;
	}
	tm_ret = localtime_r(&time, &tm_info);
	if (tm_ret == NULL) {
		return -1;
	}

	(void)memset(buf, 0, size);
	wr_len = snprintf(buf, size - 1, "%d-%02d-%02d %02d:%02d:%02d",
			  tm_info.tm_year + 1900, tm_info.tm_mon + 1,
			  tm_info.tm_mday, tm_info.tm_hour, tm_info.tm_min,
			  tm_info.tm_sec);
	if (wr_len < 0) {
		return -1;
	}

	return wr_len;
}

static int test_timestamp(void)
{
	int ret;
	time_t utc, gm8;
	char gm8_str[32] = {0};

	printf("[%s]: -----------------------------------------\n", __func__);
	ret = get_timestamp_utc(&utc);
	if (ret < 0) {
		printf("get unix timestame utc failed\n");
		return ret;
	}
	printf("timestamp utc: %ld\n", utc);
	gm8 = utc_timestamp_to_gmt8(utc);
	printf("timestamp gm8: %ld\n", gm8);
	ret = timestamp_to_readable(gm8, gm8_str, 32);
	if (ret < 0) {
		printf("timestamp to readable string failed\n");
		return ret;
	}
	printf("current gm8 time: %s\n", gm8_str);

	gm8 = 1725691959;
	ret = timestamp_to_readable(gm8, gm8_str, 32);
	if (ret < 0) {
		printf("timestamp to readable string failed\n");
		return ret;
	}
	printf("current gm8 time: %s\n", gm8_str);

	return 0;
}

int main(void)
{
	test_timestamp();
	return 0;
}
