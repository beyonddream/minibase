#include <bits/types.h>

#define TTY_MAJOR     4
#define LOOP_MAJOR    7
#define INPUT_MAJOR  13
#define DRI_MAJOR   226

/* dev_t is 64-bit in current kernels! */

static inline long major(uint64_t dev)
{
	return ((dev >>  8) & 0x00000FFF)
	     | ((dev >> 32) & 0xFFFFF000);
}

static inline long minor(uint64_t dev)
{
	return ((dev >>  0) & 0x000000FF)
	     | ((dev >> 12) & 0xFFFFFF00);
}

static inline uint64_t makedev(long maj, long min)
{
	return (((maj)&0xfffff000ULL) << 32) |
	       (((maj)&0x00000fffULL) << 8) |
	       (((min)&0xffffff00ULL) << 12) |
	       (((min)&0x000000ffULL));

}
