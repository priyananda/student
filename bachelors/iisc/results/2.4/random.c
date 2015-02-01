#include <shenoy/lottery.h>
fs
static unsigned long mcgn, srgn;
  
#define MULT 69069L
  
void pp_random_start (long i1, long i2)
{
      mcgn = (unsigned long)((i1 == 0L) ? 0L : i1 | 1L);
      srgn = (unsigned long)((i2 == 0L) ? 0L : (i2 & 0x7FFL) | 1L);
}
  
static long uni(void)
{
      unsigned long r0, r1;

      r0 = (srgn >> 15);
      r1 = srgn ^ r0;
      r0 = (r1 << 17);
      srgn = r0 ^ r1;
      mcgn = MULT * mcgn;
      r1 = mcgn ^ srgn;
      return (r1 >> 1);
}
  
static long vni(void)
{
      unsigned long r0, r1;

      r0 = (srgn >> 15);
      r1 = srgn ^ r0;
      r0 = (r1 << 17);
      srgn = r0 ^ r1;
      mcgn = MULT * mcgn;
      r1 = mcgn ^ srgn;
      return r1;
}
long pp_random(long range)
{
	long x = uni();
	x = ( x + x >> ( sizeof(long) << 2 ) ) & 0x0000ffff;
	return x % range;
}
