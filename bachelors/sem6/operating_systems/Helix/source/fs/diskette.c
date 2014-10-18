/*
 * @document : dir.c
 * @date : 23 4 2003
 * @author : Naveen
 * @exports :
 *
 */
#include "type_blk.h"
#include "fsio.h"
#include "global.h"
#include "const.h"
#include "proto.h"
/**
    This is to try the fs with dos using dos.h file
    , the union regs is given by them
 **/

static void init_f(){
    biosdisk(0,0,0,0,0,0,0);
}

u8 Write(union type_in_block * tib, u32 lba,u8 dev){
	union type_in_block * tibp = tib;
    u8 i;
	/* lba conversion portion  */
	u8 head= lba >159 ?1:0;
        /* 320 blocks on 2 sides of floppy so */
	u8 track,sector;
	track = (head ==0) ? lba/2 : (lba-160)/2;
        /*each track has 2 blocks so this*/
	sector= ((u64)lba % 2) ? 9 : 1;
        /* sector 1-8 for first lba and 9-16 for next */
	/* end of lba portion  */
    i = biosdisk(3,dev,head,track,sector,8,tib);
    if (!i) {
        return 1;      /*   SUCCESS  */
    }
	if (i == 6)
		flpchange=1;
    init_f();
    ERROR_NO=i;
    handle_error();
    /*CALL THE RESET OPERATION*/
    return 0;
}

u8 Read(union type_in_block * tib, u32 lba,u8 dev){
	union type_in_block * tibp = tib;
    u8 i;
	/* lba conversion portion  */
	u8 head= lba >159 ?1:0;
        /* 320 blocks on 2 sides of floppy so */
	u8 track,sector;
	track = (head ==0) ? lba/2 : (lba-160)/2;
        /*each track has 2 blocks so this*/
	sector= ((u64)lba % 2) ? 9 : 1;
        /* sector 1-8 for first lba and 9-16 for next */
	/* end of lba portion  */

    i=  biosdisk(2,dev,head,track,sector,8,tib);
    if(!i ){
        return 1;
    }
    if (i == 6)
       	flpchange=1;
    init_f();
     ERROR_NO=i;
     handle_error();
 /*CALL THE RESET OPERATION*/
     return 0;
}

u8 write_sector(int head , int track , int sector , u8 * buff){
    int x = biosdisk(3,0,head,track,sector,1,buff);
    if(x==6){
    	flpchange=1;
    }
    if (x){
    	ERROR_NO=x;
    	handle_error();
        init_f();
    }
    return x;
}

u8 read_sector(int head , int track , int sector , u8 * buff){
    int x = biosdisk(2,0,head,track,sector,1,buff);
    if (x==6){
    	flpchange=1;
    }
    if(x){
    	ERROR_NO=x;
    	handle_error();
        init_f();
    }
    return x;
}