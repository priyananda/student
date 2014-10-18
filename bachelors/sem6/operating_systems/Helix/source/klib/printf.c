/*****************************************************************
*	Creator       : Murali Raja . M
*   Date          : 11 / 04 / 2003
*	Description   : Code for the printf statement and it requires the
*                   vd_putchar system call and the putNewLine return
*                   StartingofLine system call that moves to next
*                   blank line
*					It displays integers in octal or hexadecimal or
*                   decimal format and strings which must be null
*                   terminated
*****************************************************************/

#include <stdarg.h>
#include <io/video.h>
#include <types.h>


#define putchar(ch) vd_putchar(ch)

static u8 * convertString(u32 number,u32 base);

int printf(u8 *format,...){
	u8 *formatIterator;
	u8 *strIterator;
	u8 *inputString;
	u32 intContainer;
	va_list argCon;
	va_start(argCon,format);

	formatIterator=format;
	for( ; *formatIterator!='\0' ; formatIterator++){
		if(*formatIterator != '%'){
			putchar(*formatIterator);
			continue;
      	}
		formatIterator++;
		switch( *formatIterator){
			case 'c' :
					intContainer=va_arg(argCon,u8);
					putchar(intContainer);
					break;
			case 'd':
					intContainer=va_arg(argCon,u32);
					strIterator=convertString(intContainer,10);
					for(;*strIterator!='\0';strIterator++){
						putchar(*strIterator);
					}
					break;
			case 'u':
					intContainer=va_arg(argCon,u32);
					strIterator=convertString(intContainer,10);
					for(;*strIterator!='\0';strIterator++){
						putchar(*strIterator);
					}
					break;
			case 'x':
					intContainer=va_arg(argCon,u32);
					strIterator=convertString(intContainer,16);
					for(;*strIterator!='\0';strIterator++){
						putchar(*strIterator);
					}
					break;
			case 'o':
					intContainer=va_arg(argCon,u32);
					strIterator=convertString(intContainer,8);
					for(;*strIterator!='\0';strIterator++){
						putchar(*strIterator);
					}
					break;
			case 's':
					inputString=va_arg(argCon,u8 *);
					for(;*inputString!='\0';inputString++){
						putchar(*inputString);
					}
					break;
			case '%':
					putchar('%');
					break;
		}
	}
	va_end(argCon);
}

/* Conversion between bases and returns a character string */
static u8 * convertString(u32 number,u32 base){
	static u8 buffer[33];
	u8 * endStringPointer;
	endStringPointer=&buffer[sizeof(buffer) - 1];
	*endStringPointer='\0';
	do{
		*( -- endStringPointer ) ="0123456789abcdef"[number % base ];
			number /= base;
	}while(number != 0 );
	return endStringPointer;
}
