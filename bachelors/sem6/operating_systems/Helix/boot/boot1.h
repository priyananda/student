#ifndef __BOOT1_H__
#define __BOOT1_H__

void copy_gdt();
void switch_prot();
void put_string();

void outString(const char * str);
void puts(const char * str);
void putch(char ch);
int  getch();

void load_kernel();

void show_gfx();
void show_graphics();
void dispint();
void get_mem_size();
void get_cpu();
extern char cpu_str[13];
void error_msg(const char * message);

#define INT(x) ((unsigned int*)(x))
#define CHAR(x) ((unsigned char*)(x))
#define reboot() __asm__ __volatile__ ("int $0x19")

#endif
