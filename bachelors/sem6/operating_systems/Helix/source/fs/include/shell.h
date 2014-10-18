/*
 * @document : shell.h
 * @date     : 23 4 2003
 * @author   : Shenoy
 * @comment  : Open File table
 */
#ifndef __SHELL_H
#define __SHELL_H

#include "types.h"
#include "string.h"


#ifdef _COMPLETE_
 #include "include.h"
#endif

/*
 * return code - representing all the commands
 */
#define WRI     0  /* copy con , cat > */
#define LIST    1  /* ls */
#define SHOW    2  /* cat */
#define APP     3  /* cat >> */
#define CD      4  /* cd */
#define HELP    5  /* help ( dos ) */
#define MKFS    6  /* format + mkfs */
#define REN     7  /* ren ( dos ) */
#define FINFO   8  /* stat */
#define LINK    9  /* ln */
#define QUIT    10 /* exit */
#define CP      11 /* cp */
#define LOAD    12 /* mount  */
#define ULOAD   13 /* umount */
#define RF      14 /* rm */
#define RMD     15 /* rmdir */
#define MKD     16 /* mkdir */
#define CHOWN   17 /*change ownership*/
#define CHPERM  18 /*change permission*/
#define ADDUSER 19 /*enbles super user to sdd a user*/
#define BAD_CMD 255/* Bad Command Or File Name */
#define CLS     20 /* cls,clear */
#define REBOOT  21 /* reboot */

extern const char cmd_str[][10];
extern const char cmd_help_str[][100];
extern u8 NUM_CMD ;
struct man_message{
	u8 command[100];
	u8 args[50];
	u8 explanation[400];
	u8 note[150];
};
extern const struct man_message man_msg[];
/*
const char  cmd_str[][10] =  {
 	"wri"  ,
 	"list" ,
 	"show" ,
 	"app"  ,
 	"cd"   ,
 	"help" ,
 	"mkfs" ,
 	"ren"  ,
 	"finfo",
 	"link" ,
    "quit" ,
    "cp"   ,
    "load" ,
    "uload",
    "rf"   ,
    "rmd"  ,
    "mkd"  ,
    "chown",
    "chperm",
    "adduser",
    "clr"
};

const char  cmd_help_str[][100] =  {
	"wri FILE \t:\tWrites a new file"  ,
	"list \t\t:\tLists directory contents" ,
	"show FILW \t:\tDisplays a file" ,
	"app FILE \t:\tAppends to existing file"  ,
	"cd DIR \t\t:\tChange directory"   ,
	"help [CMD] \t:\tDisplays a help message" ,
	"mkfs \t\t:\tCreate a new FileSystem" ,
	"ren OLD NEW\t:\tRename a file"  ,
	"finfo FILE\t:\tFile information",
	"link OLD NEW\t:\tCreate a link" ,
	"quit \t\t:\tQuits from shell",
	"cp OLD NEW\t:\tCopies files"   ,
	"load\t\t:\tLoads filesystem" ,
	"uload\t\t:\tUnloads filesystem",
	"rf FILE\t\t:\tDeletes a file"   ,
	"rmd DIR\t\t:\tDeletes a directory"  ,
	"mkd DIR\t\t:\tCreates a directory",
    "chown FILE NEW_OWNER_ID\t:\tchanges the owner ",
    "chperm FILE NEW_PERM\t:\tchanges the permission ",
    "adduser \t:\tadds a user",
    "clr \t\t: Clears the screen"
};

#define NUM_CMD ( sizeof(cmd_str) / sizeof(cmd_str[0]) )  */

#endif