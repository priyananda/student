/*	
 * @document : stdarg.h
 * @date     : 5May2003
 * @author   : Shenoy
 * @comment  : variable args  header
 *
 */	

#ifndef __STDARG_H
#define __STDARG_H

#define	VA_SIZE(TYPE)		\
	((sizeof(TYPE) + sizeof(_stackitem) - 1) & ~(sizeof(_stackitem) - 1))

/* &(LASTARG) points to the LEFTMOST argument of the function call */
#define	va_start(AP, LASTARG)	\
	(AP=((va_list)&(LASTARG) + VA_SIZE(LASTARG)))

#define va_end(AP)	/* nothing */

#define va_arg(AP, TYPE)	\
	(AP += VA_SIZE(TYPE), *((TYPE *)(AP - VA_SIZE(TYPE))))

typedef char *va_list;
typedef int _stackitem;	/* stack holds nothing narrower than this type */


#endif
