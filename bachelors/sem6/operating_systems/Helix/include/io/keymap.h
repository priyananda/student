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

#define KEY_UP		0x100
#define KEY_DOWN	0x200
#define KEY_RIGHT	0x300
#define KEY_LEFT	0x400

#define KEY_HOME	0x500
#define KEY_PUP		0x600
#define KEY_PDN		0x700
#define KEY_END  	0x800
#define KEY_INS  	0x900
#define KEY_DEL  	0xA00
#define KEY_PAUSE 	0xB00
#define KEY_BREAK 	0xC00

#define KEY_F1   	0xD00
#define KEY_F2   	0xE00
#define KEY_F3   	0xF00
#define KEY_F4   	0x1000
#define KEY_F5   	0x1100
#define KEY_F6   	0x1200
#define KEY_F7   	0x1300
#define KEY_F8   	0x1400
#define KEY_F9   	0x1500
#define KEY_F10  	0x1600
#define KEY_F11  	0x1700
#define KEY_F12  	0x1800

#define KEY_SRQ  	0x1900
#define KEY_PSC  	0xA000

#define KEY_CTRL	0x10000
#define KEY_SHIFT	0x20000
#define KEY_ALT		0x40000

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
