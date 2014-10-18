/*
 * @document : dir_str.h
 * @date     : 23 4 2003
 * @author   : Naveen
 * @comment  : Directory Structure
 */
#ifndef __FS_DIR_STR_H
#define __FS_DIR_STR_H

#include "types.h"
#include "const.h"

struct dir_str{
    u8 name[MAX_NAME];      /* name of file */
    u8 hash;                /* this field is based of name , produced 
                               by some hashing function , so that when 
                               searching for some file , the act becomes 
                               easier .The hash value varies from 0 to 255, 
                             */
    u32  lba;
};
/*directory size is 37 octets*/

#endif