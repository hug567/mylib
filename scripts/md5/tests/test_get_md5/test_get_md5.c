/*
 * 使用C语言计算文件md5值
 * 经测试，计算出的值与md5sum计算出的值相同
 * 2023-08-29
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <md5.h> /* https://github.com/util-linux/util-linux/blob/master/include/md5.h */

static void usage(const char *name)
{
	printf("usage: %s <file>              get file md5 value\n", name);
}

static void calculate_md5(const char *str, size_t len)
{
	struct UL_MD5Context ctx = {0};
	unsigned char md5[UL_MD5LENGTH] = {0};

	ul_MD5Init(&ctx);
	ul_MD5Update(&ctx, str, len);
	ul_MD5Final(md5, &ctx);

	for (int i = 0; i < UL_MD5LENGTH; i++) {
		printf("%02x", md5[i]);
	}
	printf("  <- calculate_md5 with c\n");
}

int main(int argc, const char *argv[])
{
	FILE *file = NULL;
	const char *fname;
	size_t fsize, rd_size;
	char *fstr;

	if (argc != 2) {
		usage(argv[0]);
		return -1;
	}
	fname = argv[1];
	file = fopen(fname, "r");
	if (file == NULL) {
		printf("open %s failed\n", fname);
		return -1;
	}
	fseek(file, 0, SEEK_END);
	fsize = ftell(file);
	fseek(file, 0, SEEK_SET);

	fstr = malloc(fsize);
	if (fstr == NULL) {
		printf("malloc for read file failed\n");
		fclose(file);
		return -1;
	}
	(void)memset(fstr, 0, fsize);
	rd_size = fread(fstr, 1, fsize, file);
	if (rd_size != fsize) {
		printf("read %s failed\n", fname);
		fclose(file);
		free(fstr);
		return -1;
	}
	printf("read %s success, file size: %ld\n", fname, fsize);
	calculate_md5(fstr, fsize);

	free(fstr);
	fclose(file);
	return 0;
}
