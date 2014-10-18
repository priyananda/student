/*	
 * @document : keyboard.h
 * @date     : 29March2003
 * @author   : Harish.J.P
 * @comment  : File containing the keyboard constants.
 *
 */	

#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <io/iodrv.h>
#include <types.h>

#define SCROLL_LOCK 0x1
#define CAPS_LOCK   0x2
#define NUM_LOCK    0x4

#define KEY_STATUS_EMPTY 0
#define KEY_STATUS_OK    1


u32 kb_get_key();
u32 kb_get_status();
u32 kb_set_leds(u8 led_states);
void kb_int_handler();

//These definitions are for the Internal Handling

//Ports for the keyboard
#define KB_DATA_PORT 0x60
#define KB_COMMAND   0x64
#define KB_STATUS    0x64

//Other constants for keyboard
#define KB_BUFF_SIZE 0x100
#define MAX_RETRIES  1000  
#define KB_LED_CODE  0xED
#define KB_ACK       0xFA
#define KB_BUSY      0x02


#endif
