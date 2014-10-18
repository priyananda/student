#include <io/keyboard.h>
#include <io/keymap.h>

#define SCROLL_LOCK_BIT 0x1
#define NUM_LOCK_BIT    0x2
#define CAPS_LOCK_BIT   0x4

static u32 buffer[KB_BUFF_SIZE];
static u32 buffer_read = -1;
static u32 buffer_write = 0;

static u32 left_key_status = 0;
static u32 right_key_status= 0;
static u8 lock_keys = 0;
static u8 prev_scancode = 1;

u32 kb_get_key(){
	u32 retVal = 0;
	if(buffer_read == -1){
		return 0;
	}
	retVal = buffer[buffer_read];
	buffer_read = (buffer_read + 1)%KB_BUFF_SIZE;
	if(buffer_read == buffer_write){
		buffer_read  = -1;
		buffer_write = 0;
	}
	return retVal;
}

static u32 kb_add_key(u32 key){
	if(buffer_read == buffer_write)return 0;
	buffer[buffer_write] = key;
	if(buffer_read == -1){
		buffer_write = 1;
		buffer_read = 0;
	}else{
		buffer_write = (buffer_write + 1)%KB_BUFF_SIZE;
	}
	return 0;
}

u32 kb_get_status(){
	return (buffer_read == -1) ? (KEY_STATUS_EMPTY) : (KEY_STATUS_OK);
}

static u32 kb_wait(){
	u32 retries = MAX_RETRIES;
	while(--retries && inb(KB_STATUS) & KB_BUSY);
	return retries != 0;
}

static u32 kb_ack(){
	u32 retries = MAX_RETRIES;
	while(--retries && inb(KB_DATA_PORT) != KB_ACK);
	return retries != 0;
}

u32 kb_set_leds(u8 led_state){
	kb_wait();
	outb(KB_DATA_PORT,(u8)KB_LED_CODE);
	kb_ack();
	kb_wait();
	outb(KB_DATA_PORT,(u8)led_state);
	kb_ack();
	return 1;
}

#define isalpha(c) ( (((c) >= 'a') && ((c) <= 'z')) || (((c) >= 'A') && ((c) <= 'Z')) )

u32 kb_map_key(u8 key){
	u32 reKey;
	if(key > RKEY_MAP_SIZE)return 0;
	if(IS_SHIFTED(left_key_status) || IS_SHIFTED(right_key_status)){
		reKey = kbmap_shifted[key - 1];
		if(!reKey)return 0;
		SHIFT_SET(reKey);
	}else{
		reKey = kbmap_normal[key - 1];
		if(!reKey)return 0;
	}
	if(lock_keys & CAPS_LOCK_BIT && isalpha(reKey & 0xff)){
		reKey ^= 0x20;
	}
	if(IS_CTRLED(left_key_status) || IS_CTRLED(right_key_status))
		CTRL_SET(reKey);
	if(IS_ALTED(left_key_status) || IS_ALTED(right_key_status))
		ALT_SET(reKey);
	return reKey;
}

void kb_int_handler(){
	u32 key;
	u8 code = inb(0x60);// Read the scan-code
	outb(0x20,0x20);	// Cancel interrupt at 8259
	if(code == 0xfe)return;//Acer sends this I donot know why?
	if(code == 0xe0 || code == 0xe1){
		prev_scancode = code;
		return;
	}

	/* 0xFF is sent by a few keyboards, ignore it. 0x00 is error */
	if (code == 0x00 || code == 0xff){
		prev_scancode = 0;
		return;
	}

	if(!prev_scancode)return;
	if(code & 0x80){	// Released Key
		code &= 0x7f;
		switch(code){
			case RKEY_LSHIFT:
				SHIFT_UNSET(left_key_status);break;
			case RKEY_RSHIFT:
				SHIFT_UNSET(right_key_status);break;
			case RKEY_CTRL:
				CTRL_UNSET(left_key_status);break;
			case RKEY_ALT:
				ALT_UNSET(left_key_status);break;
			case RKEY_NUM_LOCK:
				lock_keys ^= NUM_LOCK_BIT;kb_set_leds(lock_keys);break;
			case RKEY_SCROLL_LOCK:
				lock_keys ^= SCROLL_LOCK_BIT;kb_set_leds(lock_keys);break;
			case RKEY_CAPS_LOCK:
				lock_keys ^= CAPS_LOCK_BIT;kb_set_leds(lock_keys);break;
		}
	}else{
		key = kb_map_key(code);
		if(key){
			kb_add_key(key);
		}else{
			switch(code){
				case RKEY_LSHIFT:
					SHIFT_SET(left_key_status);break;
				case RKEY_RSHIFT:
					SHIFT_SET(right_key_status);break;
				case RKEY_CTRL:
					CTRL_SET(left_key_status);break;
				case RKEY_ALT:
					ALT_SET(left_key_status);break;
			}
		}
	}
}
