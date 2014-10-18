/*
 * @document : const.h
 * @date     : 23 4 2003
 * @author   : Naveen
 * @comment  : File System constants
 */
#ifndef __FS_CONST_H
#define __FS_CONST_H


#define NULL (void *)0 

#define FS                      32     /*32 because error in file system not concerned with floppy, error no varies from 33-63 
which is not return value of biosdisk*/
#define MAGIC                   99
#define VER                     1
#define CT_LBA                  320     /* even though floppy can hold 360 
                                         such sectors it is taken 320 here,
                                         because assuming using only 2 blocks
                                         per track	wasting the other two 
                                         sectors so that a block does not 
                                         span over  tracks  */
#define NO_LBA                  CT_LBA  /* dummy lba, this value since it 
                                         cannot exist as it varies from 0 
                                         to CT_LBA-1  */
#define LBA_SIZE                4       /* no of bits for lba */

#define BOOT_LBA                0       /* lba of bootsector and superblock*/
#define BLOCK_SIZE              (4*1024)
#define FNODE_SIZE              (sizeof(struct fnode))
#define BIT_MAP_SIZE            0       /* 0 blocks because it is small 
                                           enough to keep it along with 
                                           super block itself*/
#define CT_DIRECT_IDX           7
#define CT_FIRST_IDX            2
#define CT_SECOND_IDX           1
#define CT_TOTAL_IDX            (7+2+1) /* total no of indexes in fnode : 
                                           sum of previous three entries*/

#define FDD                     0       /* code for floppy */
#define HDD                     8       /* code for hard disk */
#define NO_DEV                  13      /* this is what buffers are initialised
                                           with , representing no device  */


#define CT_OPEN_FILE            10      /* no of entries in open file table*/
#define NO_OPEN                 CT_OPEN_FILE
#define CT_DUMMY_BLOCKS         2       /* used in type_in_block.h  this can
                                           contain exactly one block  used for 
                                           computaion in them. This is no of 
                                           such blocks  */
#define SUPER_SIZE              (sizeof(struct super_block))


/**
   Buffer management   constants 
 **/
#define	CLEAN                   0       /* buffer is clean ie not changed 
                                            after loaded  */
#define	DIRTY                   1
#define	CT_BUFS                 5       /* no of buffers */
#define NO_BUF                  CT_BUFS /* this is not an error signal but
                                           used for initialisation represents 
                                           an invalid value*/
#define IN_USE                  0       /* whether the buffer is currently 
                                           in use or not  */
#define NOT_IN_USE              1
#define ONLY_SEARCH             0       /* says that the buffer will be 
                                           overwritten just after getting 
                                           it so, if required data not present
                                           , then no need to read from disk */
#define NOT_ONLY_SEARCH         1
#define FRONT                   0
#define NOT_FRONT               1

/**
    These are the various errors that can occur  , set the ERROR_NO variable 
    with this and handle it later  
 **/
#define NO_FORMAT               FS+1    /* could not format floppy because
                                           there is not enough free non 
                                           bad blocks  */
#define NO_EMPTY_BUFS           FS+2    /* all the buffers are currently in 
                                            use so cannot be allocated */
#define NO_BLOCKS               FS+3    /* no free blocks  to use   */
#define SCRAP_CODE              FS+4    /* logical error due to scrap code*/
#define ALREADY_OPEN            FS+5    /* says that the file is already open*/
#define NO_DEVICE_ROOT          FS+6    /* super_block of device not mounted*/
#define FREE_OF_UNALLOCATED_BUFFER   FS+7
                                        /* unallocated buffer is being tried to
                                           be freed, ie put_block without 
                                           corresponding get_block */
#define NOT_DIR                 FS+8    /* specified directory is not 
                                           a directory*/
#define NAME_MISSING            FS+9    /* path ends with | , so the next part
                                           dir or file name is missing*/
#define NO_DIR_FILE             FS+10   /* specified dir or file is not there*/
#define ALREADY_PRESENT         FS+11   /* file or directory being created 
                                           is  already present*/
#define NO_EMPTY_OPEN           FS+12   /* empty open file slot not there*/ 
#define NOT_A_FILE              FS+13   /* some file operation like open is 
                                           applied on nonfile, may be dir*/
#define INVALID                 FS+14   /* invalid argument has been passed */
#define LINK_OVERFLOW           FS+15   /* number of links being created is 
                                           more than that can be accomodated */
#define SEEK_WACKY              FS+16   /* trying to seek out of bounds
                                           of file or directory*/
#define READ_FRENZY             FS+17   /* trying to read out of bounds*/
#define DIR_GRAVID              FS+18   /* not empty directory  to be removed*/
#define NO_SUPER                FS+19   /* super block not found*/
#define NOT_NEOFS               FS+20   /*magic incompatible not my file system*/
#define NOT_ENOUGH_PRIVILEGE FS+21 /*do not have enough privilege for operation tried */
#define NOT_READ                  FS+22  /*file not opened in read mode but tried to be read*/
#define NOT_WRITE                  FS+23  /*file not opened in write mode but tried to be write*/
#define BAD_USER_OR_PASSWORD     FS+24  /* either the user id or password is wrong */ 
#define DUPLICATE_USER         FS+25   /* user with this user name already present*/        
#define USER_OVERFLOW         FS+26    /*max users already present*/
#define INVALID_USER             FS+27   /*invalid user given in the func, say in chown*/

#define DIR_ENTRY_SIZE          (sizeof(struct dir_str))
#define MAX_NAME                32      /* max size of file name */
#define ORD_FILE                00      /* code for recognising ordinary 
                                           file MSB is zero*/
#define DIRECTORY               128     /* code for recognising directory
                                           most significant bit is  1*/
#define CT_DIR_FNODE            ((BLOCK_SIZE-FNODE_SIZE)/DIR_ENTRY_SIZE)
                                        /* no of directory entries in block 
                                           containg fnode */
#define CT_DIR_NO_FNODE         ((BLOCK_SIZE)/DIR_ENTRY_SIZE)
                                        /* no of directory entries in block
                                           not containg fnode */
#define IFS                     '|'

/**
    These are used in search_dir()  function as flag argument to indicate
    what to do with directory file
 **/
#define LOOK_UP                 0       /* search only*/
#define ENTER                   1       /* add entry*/
#define DELETE                  2       /* remove entry*/
#define IS_EMPTY                3       /* check whether directory is empty, is
                                           contains only '.' and '..' entries*/

/**
    These are used in open.c for opening a file
**/

#define O_READ                  1
#define O_WRITE                 2
#define O_RW                    3
#define O_APPEND                4
#define O_TRUNC                 8
#define O_CREAT                 16
#define O_ACCMODE               3
/**
    seek constants
 **/
#define SEEK_BEG                0
#define SEEK_CUR                1
#define SEEK_END                2

#define CT_SUPER                1       /* max no of 	super blocks that can 
                                           be held, usefull in mounting  */
#define SUPER_LBA               0

#define IS_ORD_FILE(mode)       (!(mode >> 7))

/**
        permission check constants
**/

#define OWNER_READ         (1<< 5)
#define OWNER_WRITE       (1<< 4)
#define OWNER_EXECUTE   (1<< 3)

#define OTHER_READ         (1<< 2)
#define OTHER_WRITE       (1<< 1)
#define OTHER_EXECUTE   (1<< 0)

#define PASSWORD_LENGTH 20
#define MAX_USER        10

/*************************************/
/*ERRORS ASSOCIATED WITH DISK*/
/*************************************/
#define BAD_PARAM	1	/* head,track,sector out of range or drive not installed */
#define ADD_MARK	2	/* media damaged or not formatted						 */
#define WRITE_PRT	3	/* media write protected								 */
#define SEC_ABSNT	4	/* sector not found					 */
#define RES_FAIL	5	/* reset operation failed								 */
#define CHG_SIG		6	/* drive door open since last operation , diff diskette  */
#define DRV_PRM		7	/* hardware problem										 */
#define BUFF_OFLOW	       9	/* buffer crosses 64K boundary							 */
#define BAD_SEC		10	/* bad sector					 						 */
#define BAD_CYLN	11	/* bad cylinder											 */
#define BAD_MTYPE	12	/* media type not supported								 */
#define BAD_NOSEC	13	/* bad no. of sectors mentioned for the drive			 */
#define BAD_ECC		16	/* uncorrectable ecc and sectors are damaged			 */
#define COR_ECC		17	/* data corrupted but corrected through ecc				 */
#define CON_FAIL	32	/* controller failure									 */
#define SEEK_FAIL	64	/* seek operation failed								 */
#define DRV_NREADY	128	/* diskette not inserted into drive						 */
#define DRV_ANREADY	170	/* drive not ready due to timing problem				 */
#define UND_ERR		187	/* undefined error										 */
#define WRT_ERR		204	/* hardware problem										 */
#define ST_ERR		224	/* hardware problem										 */
#define SN_FAIL		255	/* sense failed											 */

const char * error2string(const int error);




#endif
