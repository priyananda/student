/*	
 * @document : ctype.h
 * @date     : 5May2003
 * @author   : Shenoy
 * @comment  : common functions for char manips
 *
 */	
#ifndef __CTYPE_H
#define __CTYPE_H

#include <types.h>

s32	isalnum(s32 c);
s32	isalpha(s32 c);
s32	iscntrl(s32 c);
s32	isdigit(s32 c);
s32	isgraph(s32 c);
s32	islower(s32 c);
s32	isprs32(s32 c);
s32	ispunct(s32 c);
s32	isspace(s32 c);
s32	isupper(s32 c);
s32	isxdigit(s32 c);
s32	tolower(s32 c);
s32	toupper(s32 c);

s32	isascii(s32 c);
s32	toascii(s32 c);

#endif