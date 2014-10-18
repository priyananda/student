/*
 * @document : init.c
 * @date : 23 4 2003
 * @author : Naveen
 * @exports :  go_mount ,  go_umount
 */
#include "proto.h"
#include "global.h"
#include "super.h"
#include "bit.h"
#include "fsio.h"


u8 go_umount(u8 dev){
	u8 i,bufr;
    struct super_sect sect8;
	knock_out(dev);
	all_out(dev);
    sect8.block=super[get_super(dev)] ;
    buf[bufr].data.ini.sb = super[get_super(dev)] ;
       for (i=0;i < 45 ;i++ ){
          sect8.bit_mapa[i] = bit_map[i];
    }
    write_sector( 0,0,8,(u8 *)&sect8);
	super[get_super(dev)].dev=NO_DEV;
    return 1;
} 

u8 go_mount(u8 dev){
    u8 ret;
	ret = init(dev);
    if (!ret){
        return  0;
    }
    return 1;
}

