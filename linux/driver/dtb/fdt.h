#ifndef __FDT_H__
#define __FDT_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#ifdef __CHECKER__
#define FDT_FORCE __attribute__((force))
#define FDT_BITWISE __attribute__((bitwise))
#else
#define FDT_FORCE
#define FDT_BITWISE
#endif

typedef uint16_t FDT_BITWISE fdt16_t;
typedef uint32_t FDT_BITWISE fdt32_t;
typedef uint64_t FDT_BITWISE fdt64_t;

struct fdt_header {
	fdt32_t magic;			 /* magic word FDT_MAGIC */
	fdt32_t totalsize;		 /* total size of DT block */
	fdt32_t off_dt_struct;		 /* offset to structure */
	fdt32_t off_dt_strings;		 /* offset to strings */
	fdt32_t off_mem_rsvmap;		 /* offset to memory reserve map */
	fdt32_t version;		 /* format version */
	fdt32_t last_comp_version;	 /* last compatible version */

	/* version 2 fields below */
	fdt32_t boot_cpuid_phys;	 /* Which physical CPU id we're
					    booting on */
	/* version 3 fields below */
	fdt32_t size_dt_strings;	 /* size of the strings block */

	/* version 17 fields below */
	fdt32_t size_dt_struct;		 /* size of the structure block */
};

#define FDT_MAGIC	0xd00dfeed	/* 4: version, 4: total size */

static inline uint32_t fdt16_to_cpu(fdt16_t value)
{
    uint32_t cpu = 0U;

    cpu |= ((value << 8) & 0xff00);
    cpu |= ((value >> 8) & 0xff);

    return cpu;
}

static inline uint32_t fdt32_to_cpu(fdt32_t value)
{
    uint32_t cpu = 0U;

    cpu |= value << 24;
    cpu |= ((value << 8) & 0xff0000);
    cpu |= ((value >> 8) & 0xff00);
    cpu |= value >> 24;

    return cpu;
}

#endif
