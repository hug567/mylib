/*
 * learning linux dtb
 * 2023-06-22
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "fdt.h"

static void usage(const char *name)
{
	printf("Usage: %s <dtb>    dump dtb info\n", name);
}

static int get_fdt_head(int fd)
{
	int ret;
	struct fdt_header header = {0};

	ret = read(fd, (void *)(&header), sizeof(header));
	if (ret < 0) {
		printf("read fdt header failed\n");
		return ret;
	}

#define header_member(member) \
	printf("%-20s: 0x%x\n", #member, fdt32_to_cpu(header.member))

	header_member(magic);
	header_member(totalsize);
	header_member(off_dt_struct);
	header_member(off_dt_strings);
	header_member(off_mem_rsvmap);
	header_member(version);
	header_member(last_comp_version);
	header_member(boot_cpuid_phys);
	header_member(size_dt_struct);

#undef header_member
}

int main(int argc, const char *argv[])
{
	int fd;
	char *fname = NULL;

	if (argc != 2) {
		usage(argv[0]);
		return -1;
	}
	fname = argv[1];
	printf("fname: %s\n", fname);
	fd = open(fname, O_RDWR);
	if (fd < 0) {
		printf("open %s failed\n", fname);
		return -1;
	}

	get_fdt_head(fd);

	close(fd);
	return 0;
}
