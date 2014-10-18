#include "proto.h"
#include "fsio.h"
#include <dos.h>
#include <bios.h>
int is_loaded;
static int init_f(){
    return biosdisk(0,0,0,0,0,0,0);
}

int read_sect(int head , int track , int sector , u8 * buff){
    int x = biosdisk(2,0,head,track,sector,1,buff);
    if(x != 0) init_f();
    return x;
}
int check_for_floppy(){
    unsigned int st;
    u8 buff[513];
    st = read_sect(0,0,1,buff);
    if( st == 0 || st == 0xA0 || st == 0xB0 ) return 1;
    return 0;
}

int main(int argc,char * argv[]){
    int h , t = 0, s , count =0;
    union type_in_block blk;
    if(!check_for_floppy())
        return printf("Floppy Read Error");
    if(!Read(&blk,0,0))
        return printf("Error: Cannot create FS - floopy damaged\r\n");
    if(argc < 2 ) return 0;
    mkfs((u8*)argv[1]);
    printf("Quick Format Completed");
    return 0;
}