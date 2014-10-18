#ifndef H0TT0P_CONFIG_H
#define H0TT0P_CONFIG_H

// Version information
#define MAJOR_VERSION 0
#define MINOR_VERSION 1
#define VERSION (#MAJOR_VERSION "." #MINOR_VERSION)

// Enable or disable debugging
#define CONFIG_DEBUG

// OS Types.
#define OS_WIN32	0x2
#define OS_LIN32	0x4

// set the system ( OS ) type.
#define CONFIG_OS	OS_LIN32

#ifdef CONFIG_DEBUG
#	define dprintf(fmt,arg...)  printf(fmt,##arg)
#else
#	define dprintf(fmt,arg...)  
#endif

#define VAR_HTTP_EXEC_DIR "http.exec.dir"
#define VAR_HTTP_CONFIG_DIR "http.conf.dir"

#endif
