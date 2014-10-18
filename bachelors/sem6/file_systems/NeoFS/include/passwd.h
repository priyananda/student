#ifndef __PASSWD_H
#define __PASSWD_H

#define PACKED __attribute__ ( packed )

struct logininfo{
	u8 name[MAX_NAME];
	u8 password[PASSWORD_LENGTH];
	u8 uid;
};
#endif