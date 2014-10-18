/*
 * @document : cmdparse.h
 * @date     : 23 4 2003
 * @author   : Shenoy
 * @comment  : Command-Parser for shell
 */
#ifndef __CMDPARSE_H
#define __CMDPARSE_H

#include "shell.h"

int do_wri(u8 * file);  
int do_list(u8 * dir); 
int do_show(u8 * file); 
int do_app(u8 * file);  
int do_helpd(); 
int do_help(u8 * cmd);
int do_mkfs(); 
int do_ren(u8 * _old , u8 * _new);  
int do_info(u8 * file);
int do_link(u8 * file , u8 * link); 
int do_cp(u8 * src , u8 * dst);
int do_load();
int do_uload();
int do_rf(u8 * file);
int do_rmd(u8 * dir);
int do_mkd(u8 * dir);
int do_chown(u8 * path, u8  * ownid);
int do_chperm(u8 * path, u8 * perm);
int do_adduser();
int  check_for_args(int cmd,int nargs);


class CommandParser{
public:
    static u8 command[100];
    static u8 curr_dir[100];
    static u8 first_arg[132];
    static u8 second_arg[132];
    static void init();
    static int  parseCommand();
    static void getCommand();
    static void executeCommand(int cmd);
    static void do_cd();
	static int do_quit();
	static void toAbsolute(u8 * file);
    static void normalize(u8 * path);
};

extern u8 is_loaded;
#endif