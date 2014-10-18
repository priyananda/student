#include <stdio.h>
#include "floppy.h"

/** 
    Tries to read a sector and returns the error status 
 **/
int get_sector_status(int head , int track , int sector){
    char buff[512];
    reset_floppy();
    return  biosdisk(2,0,head,track,sector,1,buff);
}

/** 
    Resets the drive after use
**/
void reset_floppy(){
    biosdisk(0,0,0,0,1,0,0);
}

/**
    checks for a floppy or some hardware errors . Excludes bad sectors as they
    are software problems
 **/
int check_for_floppy(){
    unsigned char st;
    reset_floppy();
    st = get_sector_status(1,1,1);
    if( st == 0 || st == 11 || st == 10  ) return 1;
    return 0;
}

/**
    Prints The Error Message for error into the string 
 **/
void errormessage(u8 error ,char * str ){
    switch (error){
        case 1:
                sprintf(str,"head,track,sector out of range or drive not installed\n");
                break;
        case 2:
                sprintf(str,"media damaged or not formatted\n");
                break;
        case 3:
                sprintf(str,"media write protected\n");
                break;
        case 4:
                sprintf(str,"media damaged or not formatted\n");
                break;
        case 5:
                sprintf(str,"reset operation failed\n");
                break;
        case 6:
                sprintf(str,"drive door open since last operation , diff diskette  \n");
                break;
        case 7:
                sprintf(str,"hardware problem\n");
                break;
        case 8:
                sprintf(str,"Internal Buffer Problem\n");
                break;
        case 9:
                sprintf(str,"buffer crosses 64K boundary\n");
                break;
        case 10:
                sprintf(str,"bad sector\n");
                break;
        case 11:
                sprintf(str,"bad cylinder\n");
                break;
        case 12:
                sprintf(str,"media type not supported\n");
                break;
        case 13:
                sprintf(str,"bad no. of sectors mentioned for the drive\n");
                break;
        case 16:
                sprintf(str,"uncorrectable ecc and sectors are damaged\n");
                break;
        case 17:
                sprintf(str,"data corrupted but corrected through ecc\n");
                break;
        case 32:
                sprintf(str,"controller failure\n");
                break;
        case 64:
                sprintf(str,"seek operation failed\n");
                break;
        case 128:
                sprintf(str,"Drive not ready\n");
                break;
        case 170:
                sprintf(str,"drive not ready due to timing problem\n");
                break;
        case 187:
                sprintf(str,"undefined error\n");
                break;
        case 204:
                sprintf(str,"hardware problem\n");
                break;
        case 224:
                sprintf(str,"hardware problem\n");
                break;
        case 255:
                sprintf(str,"sense failed\n");
                break;
        case 0:
                sprintf(str,"No Error");
                break;
        default:
                sprintf(str,"Error nknown : %d" , error);
    }
}