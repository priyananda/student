#include "cmdparse.h"
#include "shell.h"
#include <stdio.h>
#include <conio.h>


#define DOT     (u8)('.')
#define PIP     (u8)('|')
#define vd_puts(_____x) printf(_____x)
#define printf(__str)   printf((char *)__str)
#define cprintf(__str)  cprintf((char *)__str)

int do_help(u8 * cmds){
	int cmd = -1,i;
	const struct man_message * msg ;
	for ( i = 0 ; i < NUM_CMD ; ++i )
		if(!strcmp((char *)cmds,(char *)cmd_str[i]))    cmd = i ;
	if (cmd == -1){
		printf("Command Not Found :");
		printf(cmds);
		printf("\n\r");
		return 0;
	}
	msg = &man_msg[cmd];
	cprintf ("-----------+--------------------------------------------------------------------");

	textcolor(GREEN);
	cprintf("Command    :");
	textcolor(WHITE);
	cprintf(msg->command);
	cprintf("\n\r\r");

	textcolor(GREEN);
	cprintf("Arguments  :");
	textcolor(WHITE);
	cprintf(msg->args);
	cprintf("\n\r");

	textcolor(GREEN);
	cprintf("Explanation:");
	textcolor(WHITE);
	cprintf(msg->explanation);
	cprintf("\n\r");

	textcolor(RED);
	cprintf("Note       :");
	textcolor(WHITE);
	cprintf(msg->note);
	cprintf("\n\r");
	cprintf ("-----------+--------------------------------------------------------------------\n\r");
	return 0;
}

int do_helpd(){
	int i;
	vd_puts("+----------------------------------------------------------+\n|");
	textcolor(BLINK | YELLOW);
	vd_puts( "                    qsh v 0.1 - Quick Shell               ");
	textcolor(WHITE);
	vd_puts("|\n+----------------------------------------------------------+\n");
	for ( i = 0 ; i < NUM_CMD ; ++i ){
		vd_puts(cmd_help_str[i]);
        if ( i % 23 == 19 ){
            vd_puts("\n--CONTINUE--");
            getch();
        }
		vd_puts("\n");
	}
	return 0;
}