/*
 * 测试：使用cJSON库读取json文件
 * cJSON: https://github.com/DaveGamble/cJSON.git
 * 2023-08-28
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <cJSON.h>

static void usage(const char *name)
{
	printf("Usage: %s <json>       read json file\n", name);
}

static void test_read_int(cJSON *root)
{
	int age;
	cJSON *item = NULL;

	item = cJSON_GetObjectItem(root, "age");
	if (item == NULL) {
		printf("get age from json file failed\n");
		return;
	}
	if (item->type != cJSON_Number) {
		printf("age type is not number\n");
		return;
	}
	age = item->valueint;
	printf("age: %d\n", age);
}

static void test_read_int_array(cJSON *root)
{
	int i;
	int score;
	int size;
	cJSON *item = NULL, *sc = NULL;

	item = cJSON_GetObjectItem(root, "score");
	if (item == NULL) {
		printf("get score from json file failed\n");
		return;
	}
	size = cJSON_GetArraySize(item);
	printf("score: ");
	for (i = 0; i < size; i++) {
		sc = cJSON_GetArrayItem(item, i);
		if (sc == NULL) {
			printf("get score %d failed\n", i);
			return;
		}
		if (sc->type != cJSON_Number) {
			printf("score %d is not number\n", i);
			return;
		}
		score = sc->valueint;
		printf("%d ", score);
	}
	printf("\n");
}

static void test_read_dobule(cJSON *root)
{
	double weight;
	cJSON *item = NULL;

	item = cJSON_GetObjectItem(root, "weight");
	if (item == NULL) {
		printf("get weight from json file failed\n");
		return;
	}
	if (item->type != cJSON_Number) {
		printf("weight type is not number\n");
		return;
	}
	weight = item->valuedouble;
	printf("weight: %f\n", weight);
}

static void test_read_string(cJSON *root)
{
	char *name;
	cJSON *item = NULL;

	item = cJSON_GetObjectItem(root, "name");
	if (item == NULL) {
		printf("get name from json file failed\n");
		return;
	}
	if (item->type != cJSON_String) {
		printf("name type is not string\n");
		return;
	}
	name = item->valuestring;
	printf("name: %s\n", name);
}

static void test_read_bool(cJSON *root)
{
	cJSON *item = NULL;

	item = cJSON_GetObjectItem(root, "pass");
	if (item == NULL) {
		printf("get pass from json file failed\n");
		return;
	}
	if (item->type == cJSON_True) {
		printf("pass: true\n");
	} else if (item->type = cJSON_False) {
		printf("pass: false\n");
	} else {
		printf("name type is not bool\n");
	}
}

static void test_read_json(cJSON *root)
{
	test_read_string(root);
	test_read_int(root);
	test_read_int_array(root);
	test_read_dobule(root);
	test_read_bool(root);
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

	test_read_json(root);

	cJSON_Delete(root);
	free(fstr);
	fclose(file);
	return 0;
}
