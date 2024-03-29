#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include "log.h"

#define CPU0_ID 1
#define CPU1_ID 2

int raise_sgi_interrupt(unsigned int cpu_id, unsigned int sgi_num)
{
	int fd;
	void *ptr;
	unsigned int val;
	unsigned int addr, page_addr, page_offset;
	unsigned int page_size = sysconf(_SC_PAGESIZE);

	if (cpu_id != CPU0_ID && cpu_id != CPU1_ID) {
		log_err("invalid cpu id: %u\n", cpu_id);
		return -1;
	}
	if (sgi_num >= 16) {
		log_err("invalid sgi num: %u\n", sgi_num);
		return -1;
	}

	fd = open("/dev/mem", O_RDWR);
	if(fd < 1) {
		log_err("open /dev/mem failed\n");
		return -1;
	}

	addr = 0xF8F01F00;
	val = (cpu_id << 16) + sgi_num;

	page_addr = (addr & ~(page_size - 1));
	page_offset = addr - page_addr;

	ptr = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd,
		   (addr & ~(page_size - 1)));
	if(ptr == MAP_FAILED) {
		log_err("mmap failed\n");
		close(fd);
		return -1;
	}
	*((unsigned *)(ptr + page_offset)) = val;

	close(fd);
	return 0;
}

int main(int argc, char *argv[])
{
	int ret;

	ret = raise_sgi_interrupt(CPU1_ID, 10);
	if (ret < 0) {
		log_err("raise cpu %d sgi interrupt %d failed\n", CPU1_ID, 10);
		return ret;
	}

	return 0;
}
