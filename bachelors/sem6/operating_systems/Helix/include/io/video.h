/*
 *  @document : video.h
 *  @date         : 12April2003
 *  @creator     : Murali Raja . M
 *  @commets  : Contains default descriptions
 */

#ifndef _VIDEO_H
#define _VIDEO_H
#include <types.h>
	#define MAX_ROWS 25
	#define MAX_COLUMNS 80
		/* Fore ground colours */
		#define FG_BLACK 0
		#define FG_BLUE 1
		#define FG_GREEN 2
		#define FG_CYAN 3
		#define FG_RED 4
		#define FG_MAGENTA 5
		#define FG_YELLOW 6
		#define FG_WHITE 7
		/* Back ground colours */
		#define BG_BLACK 0
		#define BG_BLUE 16
		#define BG_GREEN 32
		#define BG_CYAN 48
		#define BG_RED 64
		#define BG_MAGENTA 80
		#define BG_YELLOW 96
		#define BG_WHITE 112
		/* Other attributes    */
		#define INTENSE 8
		#define BLINK 128
	#define VIDPORT		0x3D4


u32 vd_newLine();
u32 vd_returnStartofLine();
u32 vd_putchar(u32 character);
u32 vd_setCursor(u8 row,u8 column);
u32 vd_scrollScreen(u32 noofLine);
u32 vd_setAttributes(u8 attribute);
u32 vd_clearScreen();
u32 vd_initializeVideoBuffer();
u32 vd_flushVideoBuffer();
u32 vd_getAttribute();
u32 vd_getXY();
u32 vd_setXY(u8 row,u8 column);
u32 vd_puts(u8 *str);
#endif