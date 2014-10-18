#ifndef __FS__FLOPPY__H
#define __FS__FLOPPY__H

#include <dos.h>
#include <bios.h>
#include "types.h"

int get_sector_status(int head , int track , int sector);
void reset_floppy();
int check_for_floppy();
void errormessage(u8 error ,char * str );

#endif