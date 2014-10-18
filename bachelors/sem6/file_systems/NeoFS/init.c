/*
 * @document : init.c
 * @date : 23 4 2003
 * @author : Naveen
 * @exports :
 *
 */
#include "proto.h"
#include "fsio.h"
#include "global.h"
#include "super.h"
#include "bit.h"

/**
    buffer initialisation function
**/
void buf_init(){
    u8 i;
    for(i=0; i < CT_BUFS; i++){
        buf[i].next=i+1;
        buf[i].status = CLEAN;
        buf[i].used = NOT_IN_USE;
        buf[i].dev=NO_DEV;
        buf[i].lba=NO_LBA;
    }
    buf[CT_BUFS-1].next = NO_BUF;   /* last element pointing to null */
    BUF_START=0;
    BUF_END = CT_BUFS-1;            /* pointer to last element  */
}

/**
    initialise super block  and bit_map
 **/


u8 super_bit_map_init(u8 dev){
        u8 i=0;
        u8 ret;
        struct super_sect sect8;
        ret = read_sector(0,0,8,(u8 *)&sect8); /* read the lba 1 to block[0] the dummy
                                block not to buffer because because
                                no use in buffer  */
        if (ret  &&  ret != 17) {
                return 0;
        }
        super[0]=sect8.block;    /* extract the super block portion and
                                        save in super[0] */
        CUR_ROOT=0;                  /* currently there is only one fs with
                                        no other mounted, then we may change it
                                        for refering to mounted ones so always
                                        use super[CUR_ROOT]  */
        for(i=0; i < 45; i++)
            bit_map[i].octet=sect8.bit_mapa[i].octet;
                                     /* there is a global bit_map array that
                                        is initialised to that read from device
                                        , ie the one in block[0]  */
                return 1;
}
void file_table_init(){
    u8 i=0;
    for(i=0; i <CT_OPEN_FILE; i++){
        open[i].dev=NO_DEV;
        open[i].used=NOT_IN_USE;
        open[i].f_status=CLEAN;
        open[i].lba=NO_LBA;
    }
}

u8 init(u8 dev){
        u8 ret;
    buf_init();
    ret = super_bit_map_init(dev);
        if (!ret) {
                return 0;
        }
    if (super[0].magic != 99){
        ERROR_NO=NOT_NEOFS;
        handle_error();
        return 0;
    }
    file_table_init();
        USER_ID=get_user();               /* USER_ID = getuserid()  should give
                                        user id   now 0 */
    CUR_MAX_SUPER=0;                 /* current maximum value of super . 0 since
    flpchange=0;                                    only floppy is there now*/
    return 1;
}
