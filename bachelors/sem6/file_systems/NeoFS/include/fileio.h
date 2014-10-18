/*
 * @document : fileio.h
 * @date     : 23 4 2003
 * @author   : Shenoy
 * @comment  : C-Library IO header file
 */
#ifndef __FILEIO_H
#define __FILEIO_H

#ifdef USEDLL
    #ifdef DLL_DEFINE
        #define QUAL __declspec( dllexport )
    #else
        #define QUAL __declspec( dllimport )
    #endif
#else
    #define QUAL extern
#endif

#include "proto.h"
#include "const.h"

#ifdef __cplusplus
    extern "C" {
#endif

/*file related operations*/
QUAL s8 openf   ( u8 * filename , u8 mode);
QUAL s8 closef  ( u8 fd);
QUAL s8 seekf   ( u8 fd , u32 offset , u8 whence);
QUAL s8 readf  ( u8 fd , u8 * buff , u32 how_much);
QUAL s8 writef ( u8 fd , u8 * buff , u32 how_much);
QUAL s8 linkf   ( u8 * old , u8 * _new);
QUAL s8 unlinkf (u8 * path);
QUAL s8 info (u8 * path , struct fnode * fn );
QUAL s8 finfo (u8 fd , struct fnode * fn );
QUAL u32  creatf( u8 * path, u8 mode);

/*directory related operations*/
QUAL s8 opend   ( u8 * dirname);
QUAL s8 closed  ( u8 fd);
QUAL s8 readd  ( u8 fd , u8 count ,struct dir_str * ptr);
QUAL s8 seekd (u8 fd, u8 whence, u8 offset);
QUAL s8 rewindd ( u8 fd);
QUAL s8 removed(u8* path);
QUAL u32 maked   ( u8 * path );
QUAL s8 rmd     ( u8 * path );

/*general operations*/
QUAL  s8   uloadfs();
QUAL  s8 loadfs(u8 * username, u8 * password);
QUAL  s8 makefs();
QUAL  s8 ren (u8 * orgi  , u8  ren[MAX_NAME]) ;
QUAL s8 chperm(u8 * path, u8 newperm);
QUAL s8 chown(u8 * path, u8 * newown);
QUAL  void fl_clean(void);
QUAL  s8 ispresent(u8 * path);
QUAL s8 useradd(u8 * user , u8 * password);
QUAL u8 geterror();
QUAL void errormessage(u8 error);

#ifdef __cplusplus
}
#endif

#endif