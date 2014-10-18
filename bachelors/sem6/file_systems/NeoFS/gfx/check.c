#include "types.h"
#include <dos.h>
#include <bios.h>
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

int main(){
    int h , t , s , count =0;
    u8 buff[512];
    if(!check_for_floppy())
        return printf("Floppy Read Error");
    for( t = 0 ; t < 80 ; ++t)
       for(s = 1 ; s <= 18 ; ++s)
           for (h = 0 ; h < 2; ++h)
                if(read_sect(h,t,s,buff)) ++count;
    printf("No of bad Sectors : %d",count);
    return 0;
}