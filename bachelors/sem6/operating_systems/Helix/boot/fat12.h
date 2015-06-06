#ifndef __FAT12_H__
#define __FAT12_H__

/* define standard types to enable portability */
typedef unsigned char	u8;
typedef unsigned short	u16;
typedef unsigned long	u32;
typedef unsigned char * Buffer;
typedef unsigned int uint;


#define NO_OF_LINSEC_PER_HEAD  18
#define NO_OF_LINSEC_PER_TRACK 36
#define NO_OF_FATS 2
#define NO_FAT_SECT 9
#define FAT_START 1

#define ROOT_DIR_SECT (NO_OF_FATS * NO_FAT_SECT + 1)
#define NO_ROOT_DIR_SECT 14

/* Macros to test directory entries */
#define IS_USED( __d) ( (__d).fname[0] != 0 && (__d).fname[0] != 0xe5 )
#define IS_FILE( __d) ( ! ( ((__d).attributes & 0x8) || ((__d).attributes & 0x10) ) )

typedef struct _Directory
{
	u8 fname[8];
	u8 ext[3];
	u8 attributes;
	u8 reserved[10];
	u16 time;
	u16 date;
	u16 cluster;
	u32 size;
} Directory;

uint init();
uint read(uint linear);
int searchRoot();
void load_kernel();

#endif

