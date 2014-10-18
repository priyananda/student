#include "string.h"
#include "fileio.h"
#include "proto.h"
#include "dir_str.h"
#include "global.h"
#include "cmdparse.h"

int printf(const char * ,...);
extern char * curr_dir;
#define vd_puts(x) (printf(x))



#define SEEK_BEG                0
#define SEEK_CUR                1
#define SEEK_END                2


s8 openf ( u8 * file , u8 mode){ /*-1 FOR FAILURE AND SOMETHING ELSE FOR SUCCESS*/
	u8 ret;
	ret = go_open(file,mode);
	if (ret == NO_OPEN)
		return -1;
	return ret;
}

s8 closef( u8 fd ){ /*-1 FOR FAILURE AND SOMETHING ELSE FOR SUCCESS*/
	return go_close(fd);
}

s8 seekf( u8 fd , u32 offset , u8 whence ){ /*-1 FOR FAILURE AND SOMETHING ELSE FOR SUCCESS*/
	u8 ret;
	ret = go_lseek(fd,offset,whence);
	if(!ret)
		return -1;
	return ret;
}

s8 readf ( u8 fd , u8 * buff , u32 how_much){ /*-1 FOR FAILURE AND SOMETHING ELSE FOR SUCCESS*/
	u8 ret;
	ret=go_read(fd,buff,how_much);
	if(!ret)
		return -1;
	return ret;
}

s8 writef(u8 fd, u8 * buff , u32 how_much){ /*-1 FOR FAILURE AND SOMETHING ELSE FOR SUCCESS*/
	u8 ret;
	ret=go_write(fd,buff,how_much);
	if(!ret)
		return -1;
	return ret;

}

s8 linkf( u8 * old , u8 * _new){ /*-1 FOR FAILURE AND SOMETHING ELSE FOR SUCCESS*/
	u8 ret;
	ret = go_link(old,_new,FDD);
	if(!ret)
		return -1;
	return ret;

}
s8 unlinkf (u8 * path){ /*-1 FOR FAILURE AND SOMETHING ELSE FOR SUCCESS*/
	u8 ret;
	ret = go_unlink(path);
	if(!ret)
		return -1;
	return ret;

}

/*   STAR RETURN VALUE*/
u32  creatf( u8 * path, u8 mode){ /*NO_LBA on failure and u32 on success*/
	return go_creat(path,mode);
}

s8 opend  ( u8 * dirname){/*-1 FOR FAILURE AND SOMETHING ELSE FOR SUCCESS*/
	u8 ret;
	ret = go_opendir(dirname);
	if(ret == NO_OPEN)
		return -1;
	return ret;
}

s8 closed  ( u8 fd){  /*-1 FOR FAILURE AND SOMETHING ELSE FOR SUCCESS*/
	u8 ret;
	ret =  go_closedir(fd);
	if(!ret)
		return -1;
	return ret;
}

s8 readd  ( u8 fd ,u8 count, struct dir_str * ptr){ /*-1 FOR FAILURE AND SOMETHING ELSE FOR SUCCESS*/
	u8 ret;
	ret = go_readdir(fd,count,ptr);
	if(!ret)
		return -1;
	return ret;
}

s8 seekd (u8 fd, u8 whence, u8 offset){/*-1 FOR FAILURE AND SOMETHING ELSE FOR SUCCESS*/
	u8 ret;
	ret = go_seekdir(fd , whence , offset);
	if(!ret)
		return -1;
	return ret;
}

s8 rewindd ( u8 fd){ /*-1 FOR FAILURE AND SOMETHING ELSE FOR SUCCESS*/
	u8 ret;
	ret = go_rewinddir ( fd);
	if(!ret)
		return -1;
	return ret;
}

s8 removed(u8* path){/*-1 FOR FAILURE AND SOMETHING ELSE FOR SUCCESS*/
	u8 ret;
	ret = go_removedir( path);
	if(!ret)
		return -1;
	return 1;
}

/* STAR  RETURN  VALUE*/
u32 maked   ( u8 * path ){ /*NO_LBA on failure , lba on success*/
	return go_mkdir(path , 064);
}

s8  uloadfs(){ /*-1 FOR FAILURE AND SOMETHING ELSE FOR SUCCESS*/
	u8 ret ;
	ret = go_umount(FDD);
	if(!ret)
		return -1;
    strcpy(curr_dir , "|");
	return ret;
}


s8 loadfs(u8 * username, u8 * password){ /*-1 FOR FAILURE AND SOMETHING ELSE FOR SUCCESS*/
	u8 ret;
	ret = go_mount(FDD);
	if(!ret){
		return -1;
	}
	ret = go_login(username,password);
	if(!ret){
		go_umount(FDD);
		return -1;
	}
	return ret;
}


s8 ren (u8 * orgi  , u8  ren[MAX_NAME]) {/*-1 FOR FAILURE AND SOMETHING ELSE FOR SUCCESS*/
	u8 ret;
	ret= go_rename(orgi,ren);
	if(!ret)
		return -1;
	return ret;
}


s8 info (u8 * path , struct fnode * fn ){
	u8 ret ;
	ret = go_info(path,fn);
	if(!ret)
		return -1;
	return ret;
}


s8 finfo (u8 fd , struct fnode * fn ){/*-1 FOR FAILURE AND SOMETHING ELSE FOR SUCCESS*/
	u8 ret ;
	ret = go_finfo(fd,fn);
	if(!ret)
		return -1;
	return ret;
}


s8 makefs(u8 * passwd){ /*-1 FOR FAILURE AND SOMETHING ELSE FOR SUCCESS*/
	u8 ret;
	ret = mkfs(passwd);
	if(!ret)
		return -1;
	return ret;
}

s8 chperm(u8 * path, u8 newperm){
		u8 ret;
		ret = go_chperm(path,newperm);
		if(!ret)
				return -1;
		return ret;
}

s8 chown(u8 * path, u8  * newown){
		u8 ret;
		ret = go_chown(path,newown);
		if(!ret)
				return -1;
		return ret;
}

void fl_clean(){
 go_umount(FDD);
   go_mount(FDD);
 }

/*STAR RETURN RETURNS 0 ON FAILURE*/
s8 ispresent(u8 * path){  /* this returns 1 if directory or file is present else returns -1*/
	u8 ret;
	ret = go_ispresent(path);
	if (ret == 0){
		return -1;
	}
	return ret;
}

s8 useradd(u8 * user , u8 * password){
		s8 ret;
		ret=go_adduser(user ,  password);
		if( ! ret )
				return -1;
		return ret;
}

u8 geterror(){
		return go_geterror();
}


void errormessage(u8 error){
		switch (error)
		{
				case 1:
						vd_puts("head,track,sector out of range or drive not installed\n");
						break;
				case 2:
						vd_puts("media damaged or not formatted\n");
						break;
				case 3:
						vd_puts("media write protected\n");
						break;
				case 4:
						vd_puts("media damaged or not formatted\n");
						break;
				case 5:
						vd_puts("reset operation failed\n");
						break;
				case 6:
						vd_puts("drive door open since last operation , diff diskette  \n");
						vd_puts("FLOPPY CHANGED , FS UNLOADED\n");
						uloadfs();
						is_loaded = 0;
						break;
				case 7:
						vd_puts("hardware problem\n");
						break;
				case 8:
						vd_puts("Internal Buffer Problem\n");
						break;
				case 9:
						vd_puts("buffer crosses 64K boundary\n");
						break;
				case 10:
						vd_puts("bad sector\n");
						break;
				case 11:
						vd_puts("bad cylinder\n");
						break;
				case 12:
						vd_puts("media type not supported\n");
						break;
				case 13:
						vd_puts("bad no. of sectors mentioned for the drive\n");
						break;
				case 16:
						vd_puts("uncorrectable ecc and sectors are damaged\n");
						break;
				case 17:
						vd_puts("data corrupted but corrected through ecc\n");
						break;
				case 32:
						vd_puts("controller failure\n");
						break;
				case 64:
						vd_puts("seek operation failed\n");
						break;
				case 128:
						vd_puts("Drive not ready\n");
						break;
				case 170:
						vd_puts("drive not ready due to timing problem\n");
						break;
				case 187:
						vd_puts("undefined error\n");
						break;
				case 204:
						vd_puts("hardware problem\n");
						break;
				case 224:
						vd_puts("hardware problem\n");
						break;
				case 255:
						vd_puts("sense failed\n");
						break;
				case FS+1:
						vd_puts("could not format floppy because there is not enough free non  bad blocks\n");
						break ;
				case FS+2:
						vd_puts( "all the buffers are currently in use so cannot be allocated \n");
						break ;
				case FS+3:
						vd_puts( "  no free blocks  to use  \n");
						break ;
				case FS+4:
						vd_puts( "logical error due to scrap code \n");
						break ;
				case FS+5:
						vd_puts( " says that the file is already open\n");
						break ;
				case FS+6:
						vd_puts( " super_block of device not mounted\n");
						break ;
				case FS+7:
						vd_puts( "  unallocated buffer is being tried to be freed, ie put_block without  corresponding get_block \n");
						break ;
				case FS+8:
						vd_puts( " specified directory is not   a directory\n");
						break ;
				case FS+9:
						vd_puts( " path ends with | , so the next part dir or file name is missing\n");
						break ;
				case FS+10:
						vd_puts( " specified dir or file is not there \n");
						break ;
				case FS+11:
						vd_puts( " file or directory being created is  already present \n");
						break ;
				case FS+12:
						vd_puts( "  empty open file slot not there\n");
						break ;
				case FS+13:
						vd_puts( " some file operation like open is applied on nonfile, may be dir\n");
						break ;
				case FS+14:
						vd_puts( " invalid argument has been passed \n");
						break ;
				case FS+15:
						vd_puts( "  number of links being created is more than that can be accomodated \n");
						break ;
				case FS+16:
						vd_puts( " trying to seek out of bounds of file or directory\n");
						break ;
				case FS+17:
						vd_puts( " trying to read out of bounds\n");
						break ;
				case FS+18:
						vd_puts( " not empty directory  to be removed\n");
						break ;
				case FS+19:
						vd_puts( " super block not found\n");
						break ;
				case FS+20:
						vd_puts( " magic incompatible not my file system\n");
						break ;
				case FS+21:
						vd_puts( " do not have enough privilege for operation tried\n");
						break ;
				case FS+22:
						vd_puts( " file not opened in read mode but tried to be read\n");
						break ;
				case FS+23:
						vd_puts( " file not opened in write mode but tried to be write\n");
						break ;
				case FS+24:
						vd_puts( " either the user id or password is wrong\n");
						break ;
				case FS+25:
						vd_puts( " user with this user name already present\n");
						break ;
				case FS+26:
						vd_puts( " max users already present\n");
						break ;
				 default:
						printf("Unknown Error: %d",error);

		}
}