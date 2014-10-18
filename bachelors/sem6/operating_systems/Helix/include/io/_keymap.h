#ifndef __KEYMAP_H__
#define __KEYMAP_H__

#include <types.h>

#define RKEY_MAP_SIZE 88

extern u32 kbmap_normal[RKEY_MAP_SIZE];
extern u32 kbmap_shifted[RKEY_MAP_SIZE];

#define RKEY_LSHIFT 42
#define RKEY_RSHIFT 54
#define RKEY_CTRL 29
#define RKEY_ALT 56

#define RKEY_NUM_LOCK 69
#define RKEY_CAPS_LOCK 58
#define RKEY_SCROLL_LOCK 70

#define ASCII_MAX 255
#define KEY_UP ASCII_MAX + 1
#define KEY_DOWN ASCII_MAX + 2
#define KEY_RIGHT ASCII_MAX + 3
#define KEY_LEFT ASCII_MAX + 4

#define KEY_HOME ASCII_MAX + 5
#define KEY_PUP  ASCII_MAX + 6
#define KEY_PDN  ASCII_MAX + 7
#define KEY_END  ASCII_MAX + 8
#define KEY_INS  ASCII_MAX + 9
#define KEY_DEL  ASCII_MAX + 10
#define KEY_PAUSE ASCII_MAX + 11
#define KEY_BREAK ASCII_MAX + 12

#define KEY_F1   ASCII_MAX + 14
#define KEY_F2   ASCII_MAX + 15
#define KEY_F3   ASCII_MAX + 16
#define KEY_F4   ASCII_MAX + 17
#define KEY_F5   ASCII_MAX + 18
#define KEY_F6   ASCII_MAX + 19
#define KEY_F7   ASCII_MAX + 20
#define KEY_F8   ASCII_MAX + 21
#define KEY_F9   ASCII_MAX + 22
#define KEY_F10  ASCII_MAX + 23
#define KEY_F11  ASCII_MAX + 24
#define KEY_F12  ASCII_MAX + 25

#define KEY_SRQ  ASCII_MAX + 26
#define KEY_PSC  ASCII_MAX + 27

#define KEY_CTRL	0x100
#define KEY_SHIFT	0x200
#define KEY_ALT		0x400

#define SHIFT_SET(ch)	( (ch) |= KEY_SHIFT )
#define CTRL_SET(ch)	( (ch) |= KEY_CTRL  )
#define ALT_SET(ch)		( (ch) |= KEY_ALT   )

#define SHIFT_UNSET(ch)	( ch &= ~KEY_SHIFT )
#define CTRL_UNSET(ch)	( (ch) &= ~KEY_CTRL  )
#define ALT_UNSET(ch)	( (ch) &= ~KEY_ALT   )


#define IS_SHIFTED(ch)	( (ch) & KEY_SHIFT )
#define IS_CTRLED(ch)	( (ch) & KEY_CTRL  )
#define IS_ALTED(ch)	( (ch) & KEY_ALT   )

#endif
