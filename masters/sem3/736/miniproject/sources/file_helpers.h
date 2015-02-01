#ifndef FILE_HELPERS_H
#define FILE_HELPERS_H

// #define _POSIX_C_SOURCE 200112L

#include <unistd.h>
#include <fcntl.h>

//removes all pages of this file from cache
inline void flush_cache(int fd)
{
	::posix_fadvise(fd,0,0,POSIX_FADV_DONTNEED);
}

inline void disable_prefetch(int fd)
{
	::posix_fadvise(fd,0,0,POSIX_FADV_RANDOM);
}

#define KILO_BYTE 1024
#define MEGA_BYTE (1024 * 1024)
#define GIGA_BYTE (1024 * 1024 * 1024)

#endif
