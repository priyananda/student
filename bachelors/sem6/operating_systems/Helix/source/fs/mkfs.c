
/*
 * @document : mkfs.c
 * @date : 23 4 2003
 * @author : Naveen
 * @exports : mkfs
 *
 */
#include "proto.h"
#include "global.h"
#include "fsio.h"
#include "passwd.h"
#include "super.h"

#define	strcmp_(x,y)	strcmp((const char *)(x) , (const char *)(y))
#define	strcpy_(x,y)	strcpy((char *)(x) , (const	char *)(y))
#define	strcat_(x,y)	strcat((char *)(x) , (const	char *)(y))
#define	strlen_(x)		strlen((const char *)(x))

extern union type_in_block block[2];
/**
 * Changes 5/15/03 made block extern because it is defined in global.c
 */
/**
 * NOTE THAT LBA START WITH 0  WHICH IS USED TO HOLD BOOT LOADER
 * AND SUPER BLOCK AND BIT MAP IN CASE OF FLOPPY DISK
 **/
u8 mkfs(u8 * passwd){
	u64 i;
	u8 ret_val,ret,fd;
	u32 temp,lba;
    struct logininfo l[MAX_USER] ;
	struct super_sect sect8;
//	USER_ID=0;
	/* writing the super block to the disk on format  */
	block[0].ini.sb.magic=99;
	block[0].ini.sb.ver=VER;
	block[0].ini.sb.ct_lba=CT_LBA;  /* no of lba  */
	block[0].ini.sb.dev=FDD;
	block[0].ini.sb.empty_lba= CT_LBA  -1  - BIT_MAP_SIZE    -1 ;
	/* no of empty lba is total - 1 for boot+super - those for bit-map
	 * , again one less because root directory is created*/
	block[0].ini.sb.root_dir_lba = 1 + BIT_MAP_SIZE ;
	/* this is initial value . changes if bad sector found */
	block[0].ini.sb.ff_lba = block[0].ini.sb.root_dir_lba  +1 ;
	/* !!IMP! when we start with we have an empty root directory file
	 * so cannot span over	blocks to next block, even kernel image
	 * is placed later by official write routines so initial empty
	 * lba available can be this */
	block[0].ini.sb.bit_map_bytes= 45; /*   ct_lba /8   for FLOPPY ONLY  */
	block[0].ini.sb.bit_map_blocks= 0; /*   0 FOR FLOPPY ONLY else bytes / 4K
											blocks in approx because some part
											stored along with super block*/

    block[1].fadr.hc_fnode.uid=0;
    block[1].fadr.hc_fnode.c_time=0;
	/* fnode change time like that due to changing uid  */
    block[1].fadr.hc_fnode.size=0;    /* . and ..  directories*/
    block[1].fadr.hc_fnode.m_time=0;
    block[1].fadr.hc_fnode.mode= DIRECTORY |065 ;
	/* DIRECTORY indicated by  MSB being 1,  octal 65 represent
	 * default permissions namely rw-r-x for owner and others  */
    block[1].fadr.hc_fnode.ct_links=0;

	for(i=0; i < CT_TOTAL_IDX; i++)
	   	block[1].fadr.hc_fnode.index[i]=NO_LBA;
    /* writing the directory part */
    block[1].fadr.dir[0].name[0]='.' ;
    block[1].fadr.dir[0].name[1]=0 ;
    block[1].fadr.dir[0].hash = hash(dot1) ;
    block[1].fadr.dir[1].name[0]='.' ;
    block[1].fadr.dir[1].name[1]='.' ;
    block[1].fadr.dir[1].name[2]=0 ;
    block[1].fadr.dir[0].hash= hash(dot2) ;

	while(1){
		/* this while loop is to make root directory portable so
		 * that it is not affected by bad sectors  */
		ret_val = Write( &block[1],block[0].ini.sb.root_dir_lba,FDD);
		if (ret_val ){
			block[1].fadr.dir[0].lba=block[0].ini.sb.root_dir_lba;
			/* when we wrote at top that was to check for bad sector,
			 * now we fill 	all columns like lba of . directory and
			 * then write it */
			block[1].fadr.dir[1].lba=block[0].ini.sb.root_dir_lba;
			Write( &block[1],block[0].ini.sb.root_dir_lba,FDD);
			break;
		}else{
                        if (BAD_BLOCK){
                        	block[0].ini.sb.root_dir_lba+=1;
                        	block[0].ini.sb.empty_lba-=1;
                        }else
                                return 0;
		}
		if (block[0].ini.sb.root_dir_lba == CT_LBA  ) {
			/* 1 because lba varies from  0 to CT_LBA  -1 and before this
			 * step root_dir_lba has been incremented*/
			ERROR_NO = NO_FORMAT;
			handle_error();
			return 0;
		}
	}
	/* writing super block  */
	block[0].ini.sb.ff_lba = block[0].ini.sb.root_dir_lba  +1 ;
	/* IMP!!!IMP  : when we start with we have an empty root directory
	 * file so cannot span over blocks to next block, even kernel image
	 * is placed later by official write routines so initial empty lba
	 * available can be this this part of initialising super block is
	 * placed here because its value is dependent on root directory lba  */

	/*  writing the bit map portion , super block portion is written
	 *  to disk in this section  */
	temp =  block[0].ini.sb.root_dir_lba;
	for(i=0; i < 45; i++)
		block[0].ini.bit_map[i].octet=255;
	/* bit value 1 represents unused block and zero otherwise , 255
	 * means that every lba  is free  */
	i=0;
	/* AT THIS STAGE LOOKING AT ROOT DIRECTORY WE NEED TO SET ALL
	 * PREVIOUS BITS TO USED=0 */
	while(1){
		if (temp >= 8){
			/*  number of bit map bytes before the one containg the root
			 *  directory lba  , does like this because u32/8 may or may
			 *  not be an integer division */
			block[0].ini.bit_map[i].octet=0;
			/* all these bytes marked 0 saying completely used  */
			temp -=8;
			i++;
		}else{
			switch((u8)temp){
				/*  byte which contains the root directory lba, so that and
				 *  previous ones should be called USED  */
				case 7: block[0].ini.bit_map[i].pat.b7=0;  /* CHECK THIS OUT */
				case 6: block[0].ini.bit_map[i].pat.b6=0;
				/*  no break statement so if temp is k, all bits 0 to K
				 *  are set to used  */
				case 5: block[0].ini.bit_map[i].pat.b5=0;
				case 4: block[0].ini.bit_map[i].pat.b4=0;
				case 3: block[0].ini.bit_map[i].pat.b3=0;
				case 2: block[0].ini.bit_map[i].pat.b2=0;
				case 1: block[0].ini.bit_map[i].pat.b1=0;
				case 0: block[0].ini.bit_map[i].pat.b0=0;
			}
				break;
		}
   }
	/* ret = Write(&block[0],0,FDD);  */
    sect8.block=block[0].ini.sb ;
    for(i=0; i < 45; i++){
    sect8.bit_mapa[i]=block[0].ini.bit_map[i];
    }
    ret = write_sector(0,0,8,(u8 *)&sect8);
        if (ret && ret!=17) {
                return 0;
        }
	/* finally writing the super block out to the disk  LBA 0 sector no 8 */
	/* finished writing super block  */

    USER_ID=0;
    go_mount(FDD);
    lba = go_creat((u8 *)"|passwd",060);
    if (lba == NO_LBA){
        return 0;
    }
    fd = go_open((u8 *)"|passwd",O_RW);
    if (fd == NO_OPEN){
        return 0;
    }

    strcpy_(l[0].name, (u8 *)"admin");
    strcpy_(l[0].password,passwd);
    l[0].uid=0;
    for(i=1; i < MAX_USER; i++){
        l[i].name[0]=0;
    }
    ret = go_write(fd,(u8 * )&l, MAX_USER * sizeof(struct logininfo));
    go_close(fd);
    if ( !ret ){
        return 0;
    }
   ret = go_umount(FDD);
    if (!ret){
        return 0;
    }

  	return 1;
}


/*  NOTE THAT ONCE IT IS RECOGNISED AS DIRECTORY  the first two entries for any directory are always . and ..
		we do not store any information regarding . and .. directory here to maintain data consistency and avoid redundancy
		the only field of interest is lba for these fields  .

		WELL these are true for other directories but, as root has no parent to hold it's attributes we need to keep it in the . directory.
*/


