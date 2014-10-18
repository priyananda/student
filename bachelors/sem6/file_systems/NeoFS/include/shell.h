/*
 * @document : shell.h
 * @date     : 23 4 2003
 * @author   : Shenoy
 * @comment  : Shell , what else
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
#define ADDUSER 19 /*enbles super user to add a user*/
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

#endif