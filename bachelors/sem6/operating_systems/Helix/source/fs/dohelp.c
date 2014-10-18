#include "cmdparse.h"
#include "shell.h"

#define FG_BLACK 0
#define FG_BLUE 1
#define FG_GREEN 2
#define FG_CYAN 3
#define FG_RED 4
#define FG_MAGENTA 5
#define FG_YELLOW 6
#define FG_WHITE 7

u32 vd_setAttributes(u8 attribute);
#define textcolor(color) vd_setAttributes(FG_##color)
#define cprintf printf
#define DOT     (u8)('.')
#define PIP     (u8)('|')


int do_help(u8 * cmds){
	int cmd = -1,i;
	const struct man_message * msg ;

	for ( i = 0 ; i < NUM_CMD ; ++i )
		if(!strcmp((char *)cmds,(char *)cmd_str[i]))    cmd = i ;
	if (cmd == -1){
		printf("Command Not Found :");
		printf(cmds);
		printf("\n");
		return 0;
	}
	msg = &man_msg[cmd];
	cprintf ("-----------+--------------------------------------------------------------------");

	textcolor(GREEN);
	cprintf("Command    :");
	textcolor(WHITE);
	cprintf(msg->command);
	cprintf("\n");

	textcolor(GREEN);
	cprintf("Arguments  :");
	textcolor(WHITE);
	cprintf(msg->args);
	cprintf("\n");

	textcolor(GREEN);
	cprintf("Explanation:");
	textcolor(WHITE);
	cprintf(msg->explanation);
	cprintf("\n");

	textcolor(RED);
	cprintf("Note       :");
	textcolor(WHITE);
	cprintf(msg->note);
	cprintf("\n");
	cprintf ("-----------+--------------------------------------------------------------------\n");
	return 0;
}

int do_helpd(){
	int i;
	vd_puts("+----------------------------------------------------------+\n|");
	vd_setAttributes(128 | FG_YELLOW);
	vd_puts( "                    qsh v 0.1 - Quick Shell               ");
	vd_setAttributes(7);
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