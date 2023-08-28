/*
 * 测试：使用cJSON库读取json文件
 * cJSON: https://github.com/DaveGamble/cJSON.git
 * 2023-08-28
 */
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <cJSON.h>

#define CJSON_WRITE_FILE "output.json"

static void usage(const char *name)
{
	printf("Usage: %s <json>       get init json info from file\n", name);
}

static void test_change_int(cJSON *root)
{
	cJSON_ReplaceItemInObject(root, "age", cJSON_CreateNumber(20));
}

static void test_change_int_array(cJSON *root)
{
	int score[] = { 98, 87, 76 };
	cJSON_ReplaceItemInObject(root, "weight", cJSON_CreateIntArray(score, 3));
}

static void test_change_dobule(cJSON *root)
{
	float weight = 60.3;
	cJSON_ReplaceItemInObject(root, "weight", cJSON_CreateFloatArray(&weight, 1));
}

static void test_change_string(cJSON *root)
{
	cJSON_ReplaceItemInObject(root, "name", cJSON_CreateString("Jerry"));
}

static void test_change_bool(cJSON *root)
{
	cJSON_ReplaceItemInObject(root, "pass", cJSON_CreateFalse());
}

static void test_change_json(cJSON *root)
{
	test_change_string(root);
	test_change_int(root);
	test_change_int_array(root);
	test_change_dobule(root);
	test_change_bool(root);
}

static int test_write_to_file(const char *fname, cJSON *root)
{
	FILE *file = NULL;
	char *json_str = NULL;
	size_t json_size, wr_size;

	file = fopen(fname, "w+");
	if (file == NULL) {
		printf("open %s failed\n", fname);
		return -1;
	}
	json_str = cJSON_Print(root);
	if (json_str == NULL) {
		printf("print cjson item to str failed\n");
		fclose(file);
		return -1;
	}
	printf("%s\n", json_str);
	json_size = strlen(json_str);

	wr_size = fwrite(json_str, 1, json_size, file);
	if (wr_size != json_size) {
		printf("fwrite to file failed, json_size: %ld, wr_size: %ld, "
		       "errno: %d(%s)\n", json_size, wr_size, errno,
		       strerror(errno));
		fclose(file);
		return -1;
	}

	fclose(file);
	return 0;
}

int main(int argc, const char *argv[])
{
	char *fname = NULL;
	FILE *file = NULL;
	char *fstr = NULL;
	long fsize, rd_size;
	cJSON *root = NULL;

	if (argc != 2) {
		usage(argv[0]);
		return -1;
	}
	fname = argv[1];

	file = fopen(fname, "rw");
	if (file == NULL) {
		printf("open %s failed\n", fname);
		return -1;
	}
	fseek(file, 0, SEEK_END);
	fsize = ftell(file);
	fseek(file, 0, SEEK_SET);

	fstr = malloc(fsize);
	if (fstr == NULL) {
		printf("malloc failed\n");
		fclose(file);
		return -1;
	}
	(void)memset(fstr, 0, fsize);
	rd_size = fread(fstr, 1, fsize, file);
	if (rd_size != fsize) {
		printf("read file failed\n");
		fclose(file);
		free(fstr);
		return -1;
	}

	root = cJSON_Parse(fstr);
	if (root == NULL) {
		printf("parse json str failed\n");
		fclose(file);
		free(fstr);
		return -1;
	}

	test_change_json(root);
	test_write_to_file(CJSON_WRITE_FILE, root);

	cJSON_Delete(root);
	free(fstr);
	fclose(file);
	return 0;
}
