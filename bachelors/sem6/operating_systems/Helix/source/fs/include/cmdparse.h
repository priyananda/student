/*
 * @document : cmdparse.h
 * @date     : 23 4 2003
 * @author   : Shenoy
 * @comment  : Command-Parser for shell
 */
#ifndef __CMDPARSE_H
#define __CMDPARSE_H


#include "shell.h"

extern u8 is_loaded ;
int do_wri(u8 * file);
int do_list(u8 * dir);
int do_show(u8 * file);
int do_app(u8 * file);
int do_help();
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
void initc();
int  parseCommand();
void getCommand();
int executeCommand(int cmd);
void do_cd();
int do_quit();
void toAbsolute(u8 * file);
int check_for_args(int cmd,int nargs );
void normalize(u8 * path);

#endif