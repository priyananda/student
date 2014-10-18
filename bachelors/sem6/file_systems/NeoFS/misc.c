/*
 * @document : init.c
 * @date : 23 4 2003
 * @author : Naveen
 * @exports : 
 *		get_super(u8 dev);
 */
#include "proto.h"
#include "global.h"

u8 get_super(u8 dev){
/*        u8 i;
	for(i=0; i < CT_SUPER; i++){
		if(super[i].dev == dev)
			return i;
	}
	ERROR_NO=NO_DEVICE_ROOT;
        handle_error();*/
        return 0;
}
/** 
 * typically this function returns the user id of user who has logged in   
 **/
u8 get_user(){
	return USER_ID;
}
u32 get_time(){
	return 0;
}	

u8 set_not_in_use(){
    u8 i;
    for (i=0; i < CT_BUFS ; i++ ){
        buf[i].status=NOT_IN_USE;
    }
    for (i=0; i < CT_OPEN_FILE ; i++ ){
        open[i].f_status=NOT_IN_USE;
    }
	return 1;
}

u8 hash(u8 name[MAX_NAME]){
    return 0;
/*
    u32 i , _hash;
    for ( i = 0;i < MAX_NAME && ( name[i] & name[i+1]) != 0 ;  i += 2 )
        _hash = _hash + name[i] * 19234 >> 3 + name[i+1] * 646;
    return (u8) ( _hash % 255 );
*/
}
u8 get_pid(){
        return 0;
}

u8 go_ispresent(u8 * path){  /* this returns 1 if directory or file is present else returns -1*/
    u32 lba;
    lba = eat_path(path);
    if (lba == NO_LBA )
        return 0;
    return 1;    
}
