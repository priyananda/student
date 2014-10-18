#include <io/keymap.h>


u32 kbmap_normal[] = {
	27,'1','2','3','4','5','6','7','8','9',
	'0','-','=','\b','\t','q','w','e','r','t',
	'y','u','i','o','p','[',']','\n',0,'a',
	's','d','f','g','h','j','k','l',';','\'',
	'`',0,'\\','z','x','c','v','b','n','m',
	',','.','/',0,KEY_SRQ,0,' ',0,KEY_F1,KEY_F2,
	KEY_F3,KEY_F4,KEY_F5,KEY_F6,KEY_F7,KEY_F8,KEY_F9,KEY_F10,KEY_BREAK,0,
	KEY_HOME,KEY_UP,KEY_PUP,'-',KEY_LEFT,'5',KEY_RIGHT,'+',KEY_END,KEY_DOWN,
	KEY_PDN,KEY_INS,KEY_DEL,0,0,0,KEY_F11,KEY_F12
};

u32 kbmap_shifted[] = {
	27,'!','@','#','$','%','^','&','*','(',
	')','_','+','\b','\t','Q','W','E','R','T',
	'Y','U','I','O','P','{','}','\n',0,'A',
	'S','D','F','G','H','J','K','L',':','"',
	'~',0,'|','Z','X','C','V','B','N','M',
	'<','>','?',0,KEY_PSC,0,' ',0,KEY_F1,KEY_F2,
	KEY_F3,KEY_F4,KEY_F5,KEY_F6,KEY_F7,KEY_F8,KEY_F9,KEY_F10,KEY_PAUSE,0,
	KEY_HOME,KEY_UP,KEY_PUP,'-',KEY_LEFT,'5',KEY_RIGHT,'+',KEY_END,KEY_DOWN,
	KEY_PDN,KEY_INS,KEY_DEL,0,0,0,KEY_F11,KEY_F12
};
