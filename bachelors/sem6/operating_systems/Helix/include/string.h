/*	
 * @document : string.h
 * @date     : 5May2003
 * @author   : Shenoy
 * @comment  : most important C-Lib functions - string manipulation
 *
 */	
#include "types.h"

#ifndef __STRING_H
#define __STRING_H

s32     memcmp      (void *_s1,   void *_s2, s32 _n);
void *  memcpy      (void *_dest, void *_src, s32 _n);
void *  memset      (void *_s,    s32 _c, s32 _n);

s8 *    strcat      (s8 *_s1,     s8 *_s2);
s8 *    strchr      (s8 *_s,      s32 _c);
s32     strcmp      (s8 *_s1,     s8 *_s2);
s8 *    strcpy      (s8 *_s1,     s8 *_s2);
s32     strcspn     (s8 *_s1,     s8 *_s2);
s8 *    strerror    (s32 _errcode);
s32     strlen      (s8 *_s);
s8 *    strncat     (s8 *_s1,     s8 *_s2, s32 _n);
s32     strncmp     (s8 *_s1,     s8 *_s2, s32 _n);
s8 *    strncpy     (s8 *_s1,     s8 *_s2, s32 _n);



#endif