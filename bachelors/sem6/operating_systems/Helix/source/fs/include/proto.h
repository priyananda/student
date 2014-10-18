/*
 * @document : proto.h
 * @date     : 23 4 2003
 * @author   : Naveen
 * @comment  : Function Prototypes
 */
#ifndef __FS_PROTO_H
#define __FS_PROTO_H

#include "types.h"
#include "const.h"

#define	strcmp(x,y)	strcmp((char *)(x) , (char *)(y))
#define	strcpy(x,y)	strcpy((char *)(x) , (char *)(y))
#define	strcat(x,y)	strcat((char *)(x) , (char *)(y))
#define	strlen(x)	strlen((char *)(x))


#ifdef __cplusplus
	#include <iostream.h>
    extern "C" {
#endif
/**
    Prototypes of all functions used for the File System
**/

struct   dir_str;
struct   fnode;
struct   rw;

extern   u8 get_block(u8  _dev, u32  _lba , u8   _only_search);
extern   u8 put_block(u8   _buf_no , u8  _front);
extern   u8 all_out(u8 dev);
extern   void clean_buffer(u32 lba);
extern   u32 alloc_bit(u8 dev);
extern   u8 free_bit(u32  _lba,u8 dev);
extern   u8 go_opendir(u8 * path);
extern   u8 go_closedir(u8 fd);
extern   u8 go_seekdir(u8 fd , u8 whence , u8 offset);
extern   u8 go_rewinddir (u8 fd);
extern   u8 go_readdir (u8 fd , u8 count , struct dir_str * dir );
extern   u8 go_removedir(u8 * path);
extern   u8 get_fnode(u32 lba,u8 dev);
extern   void put_fnode(u8 fd);
extern   void clean_fnode(u32 lba);
extern   u8 knock_out(u8 dev);
extern   u32 alloc_node(u8 dev);
extern   void free_node(u32 lba,u8 dev);
extern   void buf_init();
extern   u8 init(u8 dev);
extern   u8 go_link(u8 * original_fl  ,  u8  *  link_fl , u8 dev );
extern   u8 go_unlink (u8 * path);
extern   u8 go_rename (u8 * orgi  , u8  ren[MAX_NAME] );
extern   u8 get_super(u8 dev);
extern   u8 get_user();
extern   u32 get_time();
extern   u8 set_not_in_use();
extern   u8 go_umount(u8 dev);
extern   u8 go_mount(u8 dev);
extern   u32  go_creat( u8 * path, u8 mode);
extern   u32 go_mkdir(u8 * path , u8 mode);
extern   u8 go_open( u8 * path , u8 mode);
extern   u8 truncate (u8 fd);
extern   u8 go_close (u8 fd);
extern   u8 go_lseek(u8 fd,  u32 offset ,u8 whence );
extern   u8 * get_name(u8 * old_name,u8 string[MAX_NAME]);
extern   u32 last_dir(u8 * path, u8 string[MAX_NAME]);
extern   u32 eat_path(u8 * path);
extern   u8 search_dir(u32 dlba  , u8 string[MAX_NAME]  , u32 * slba , u8 flag);
extern   u8 go_finfo (u8 fd , struct fnode * fn );
extern   u8 go_info (u8 * path , struct fnode * fn );
extern   u8 read_map (struct rw * rw , u32 file_pos );
extern   u8 go_read(u8 fd , u8 * dest , u32 count);
extern   u8 go_write(u8 fd , u8 * src , u32 count);
extern   u8 get_super(u8 dev);
extern   u8 getuser();
extern   u8 hash(u8 *);
extern   u8 mkfs(u8 *);
extern   void go_fl_clean();
extern   u8 get_pid();
extern   u8 go_chown(u8 * path ,u8 * newown);
extern   u8 go_chperm(u8 * path ,u8 newperm);
extern   u8 go_ispresent(u8 * path);
extern   u8 go_login(u8 * username,u8 * password);
extern   u8 go_adduser (u8 * name, u8 * password);
extern u8 go_geterror() ;


#ifdef __cplusplus
     	#define handle_error() cout << "Error No:"  << (int) ERROR_NO << "in" <<__LINE__<< "@" << __FILE__ <<endl;
  //  #define handle_error() ;
}
#else
	#define   handle_error()  //{ printf("Error : %u @ %s @ %s @ line : %d\n" ,ERROR_NO, __FUNCTION__ ,__FILE__,__LINE__ );}
#endif

#define BAD_BLOCK   ( ERROR_NO==1   || ERROR_NO==4   || ERROR_NO==7 || ERROR_NO==10   || ERROR_NO==11 || ERROR_NO==16   ||     ERROR_NO==17   || ERROR_NO==64 || ERROR_NO==170 )

#endif
