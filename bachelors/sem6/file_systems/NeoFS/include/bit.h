/*	
 * @document : bit.h
 * @date     : 23 4 2003
 * @author   : Naveen
 * @comment  : bit pattern
 *
 */

#ifndef __FS_BIT_H
#define __FS_BIT_H

#include "types.h"

struct pattern {
	unsigned b0 :1;     /* In the union that follows this bit
                           ie b0 forms the lsb of octet */
	unsigned b1 :1;
	unsigned b2 :1;
	unsigned b3 :1;
	unsigned b4 :1;
	unsigned b5 :1;
	unsigned b6 :1;
	unsigned b7 :1;
};
/**
    represents the union of an octet and 8 bits which hold bit map  
**/
union bit_map {
	struct pattern pat;
	u8  octet;
};
#endif