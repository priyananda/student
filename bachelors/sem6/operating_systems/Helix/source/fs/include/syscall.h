/*	
 * @document : syscall.h
 * @date     : 23 4 2003
 * @author   : Shenoy
 * @comment  : System calls header file - actually C_Lib exports
 *
 */	

#ifndef __SYSCALL_H
#define __SYSCALL_H

#include "types.h"

struct fileinfo;
struct dir_str;

/*
    This is the header for system calls - declares psuedo system calls 
    These functions are C Wrappers over the actual system calls 
    The actual system calls are in the kenel and are linked at 
    runtime . The psuedo- and real syscalls share the same name 
 */

/*
 *  Process and Memory System Calls
 */

pid_t   spawn(char * filename);
void    quit(u32 status);
void *  pmalloc(u32 size);
void *  dmalloc(u32 size);
void *  kmalloc(u32 size);
void    dump();

/* 
 *  File System Calls
 */

u32     open(char * filepath);
void    close(u32 fd);
u32     read(u32 fd,void * buff , u32 size);
u32     write(u32 fd,void * buff, u32 size);
u32     seek(u32 fd,u32 whence , u32 offset);
void    finfo( char * path , struct fileinfo * st_ptr);
u32     link( char * old , char * _new );
u32     rm( char * path);

u32     open_dir(char * path);
struct dir_str *
		read_dir(u32 d_fd);
u32     close_dir(u32 d_fd);
u32     mk_dir(char * path);
u32     rm_dir(char * path);
u32     ren(char * path , char * _new );


#endif