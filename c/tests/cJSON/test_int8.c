/*
 * 测试cJSON库读写int8类型
 * 2024-08-01
 */
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "cJSON.h"

#define JSON_FILE_NAME "test.json"

typedef char s8;
typedef unsigned char u8;

static size_t get_file_size(int fd)
{
	int ret;
	struct stat stat = {0};

	ret = fstat(fd, &stat);
	if (ret < 0) {
		printf("get file size failed\n");
		return 0;
	}

	return stat.st_size;
}

static char *read_file(const char *fname)
{
	int fd = -1;
	char *fstr;
	size_t fsize, rd_size;

	fd = open(fname, O_RDWR);
	if (fd < 0) {
		printf("open %s failed\n", fname);
		return NULL;
	}

	fsize = get_file_size(fd);
	fstr = malloc(fsize + 1);
	if (fstr == NULL) {
		printf("malloc for read failed: %d\n", fd);
		close(fd);
		return NULL;
	}
	(void)memset(fstr, 0, fsize + 1);
	rd_size = read(fd, fstr, fsize);
	if (rd_size != fsize) {
		printf("read file failed: %d\n", fd);
		free(fstr);
		close(fd);
		return NULL;
	}

	close(fd);
	return fstr;;
}

static int read_json_s8(cJSON *root, const char *member)
{
	s8 val;
	cJSON *item = NULL;

	item = cJSON_GetObjectItem(root, member);
	if (item == NULL) {
		printf("get %s from json file failed\n", member);
		return -1;
	}
	if (item->type != cJSON_Number) {
		printf("json %s type is not number\n", member);
		return -1;
	}
	val = item->valueint;
	printf("json member %s: %hhd\n", member, val);

	return 0;
}

static int read_json_member(cJSON *root)
{
	read_json_s8(root, "s8_01");
	read_json_s8(root, "s8_02");
	read_json_s8(root, "s8_03");

	return 0;
}

static int write_json_to_file(const char *fname, const cJSON *root)
{
	int ret;
	int fd = -1;
	char *json_str = NULL;
	size_t json_size, wr_size;

	fd = open(fname, O_RDWR);
	if (fd < 0) {
		printf("open %s failed\n", fname);
		return -1;
	}
	/* json_str need free */
	json_str = cJSON_Print(root);
	if (json_str == NULL) {
		printf("print cjson item to string failed\n");
		close(fd);
		return -1;
	}
	json_size = strlen(json_str);

	ret = ftruncate(fd, 0); /* clear file */
	if (ret < 0) {
		printf("ftruncate json file to 0 failed: %s\n", fname);
		free(json_str);
		close(fd);
		return ret;
	}
	lseek(fd, 0, SEEK_SET);
	wr_size = write(fd, json_str, json_size);
	if (wr_size != json_size) {
		printf("write to json file failed: %s\n", fname);
		free(json_str);
		close(fd);
		return -1;
	}

	free(json_str);
	close(fd);
	return 0;
}

static int set_json_member_s8(cJSON *root, const char *member, s8 val)
{
	int ret;

	ret = cJSON_ReplaceItemInObject(root, member, cJSON_CreateNumber(val));
	if (!ret) {
		printf("change parameter value failed: %s\n", member);
		return -1;
	}
	printf("change member %s to %hhd\n", member, val);

	return 0;
}

static int write_json_member(const char *fname, cJSON *root)
{
	set_json_member_s8(root, "s8_01", -5);
	set_json_member_s8(root, "s8_02", 2);
	set_json_member_s8(root, "s8_03", 4);

	write_json_to_file(fname, root);

	return 0;
}

int main()
{
	char *fstr = NULL;
	cJSON *root = NULL;

	fstr = read_file(JSON_FILE_NAME);
	if (fstr == NULL) {
		printf("read json file failed\n");
		return -1;
	}

	root = cJSON_Parse(fstr);
	if (root == NULL) {
		printf("parse json str failed\n");
		free(fstr);
		return -1;
	}
	read_json_member(root);
	write_json_to_file(JSON_FILE_NAME, root);

	free(fstr);
	return 0;
}
