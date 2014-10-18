#include <io/video.h>

static u8 currentRow;
static u8 currentColumn;
static u8 attribute;
static u8 screenBuffer[MAX_ROWS][MAX_COLUMNS*2];
u8 iteratorRow,iteratorColumn;

/* Initializes the video buffer by nulling all the video contents */
u32	vd_initializeVideoBuffer(){
	currentRow=0;
	currentColumn=0;
	for(iteratorRow=0;iteratorRow < MAX_ROWS;iteratorRow++)
		for(iteratorColumn=0;iteratorColumn<MAX_COLUMNS * 2;iteratorColumn+=2){
			screenBuffer[iteratorRow][iteratorColumn]=0;
			screenBuffer[iteratorRow][iteratorColumn+1]=attribute;
		}
	vd_flushVideoBuffer();
	vd_setCursor(currentRow,currentColumn/2);
	return 0;
}

/* Puts a printable character on the screen */
u32	vd_putchar(u32 value){
	if(currentColumn == MAX_COLUMNS * 2 ){
		if(currentRow == MAX_ROWS || currentRow - 1==MAX_ROWS){
			vd_newLine();
			return 0;
		}else
			 vd_newLine();
	}
	if(value == '\n'){
		vd_newLine();
		return 0;
	}
	if(value == '\r'){
		vd_returnStartofLine();
		return 0;
	}
	screenBuffer[currentRow][currentColumn]=value;
	screenBuffer[currentRow][currentColumn + 1]=attribute;
	currentColumn+=2;
	vd_flushVideoBuffer();
	vd_setCursor(currentRow,currentColumn/2);
	return 0;
}

/* Puts a new line into the video buffer */
u32	vd_newLine(){
		if(currentRow == MAX_ROWS - 1){
		vd_scrollScreen(1);
				for(iteratorColumn = 0;iteratorColumn < MAX_COLUMNS * 2;iteratorColumn+=2){
						screenBuffer[MAX_ROWS - 1][iteratorColumn]=0;
						screenBuffer[MAX_ROWS - 1][iteratorColumn + 1]=attribute;
				}
		}
	for(iteratorColumn=currentColumn;iteratorColumn<MAX_COLUMNS * 2;iteratorColumn+=2){
		screenBuffer[currentRow][iteratorColumn]=0;
		screenBuffer[currentRow][iteratorColumn + 1]=attribute;
	}
	currentRow++;
	currentColumn=0;
	for(iteratorColumn=0;iteratorColumn<MAX_COLUMNS*2;iteratorColumn+=2){
		screenBuffer[currentRow][iteratorColumn]=0;
		screenBuffer[currentRow][iteratorColumn + 1]=attribute;
	}
	vd_flushVideoBuffer();
	vd_setCursor(currentRow,currentColumn/2);
	return 0;
}

/* Puts the cursor to the beginning of the line */
u32	vd_returnStartofLine(){
	currentColumn=0;
	vd_setCursor(currentRow,currentColumn/2);
	return 0;
}

/* Puts the cursor in the said row and column position */
u32	vd_setCursor(u8 row,u8 column){
	u32 pos ;
	pos = (column + MAX_COLUMNS * row) * 2;
	outb(VIDPORT,14);
	outb(VIDPORT + 1,0xff & (pos >> 9));
	outb(VIDPORT,15);
	outb(VIDPORT + 1,0xff & (pos >> 1));
	return 0;
}

/* Clears the screen */
u32	vd_clearScreen(){
	for(iteratorRow=0;iteratorRow<MAX_ROWS;iteratorRow++){
		for(iteratorColumn=0;iteratorColumn < MAX_COLUMNS*2 ; iteratorColumn+=2){
			screenBuffer[iteratorRow][iteratorColumn]=0;
			screenBuffer[iteratorRow][iteratorColumn + 1]=attribute;
		}
	}
	currentColumn=0;
	currentRow=0;
	vd_flushVideoBuffer();
	vd_setCursor(currentRow,currentColumn/2);
	return 0;
}

/* Sets the attributes for the next output on terminal */
u32	vd_setAttributes(u8 attr){
	attribute=attr;
	return 0;
}

/* Scroll screen by the said amount of lines */
u32	vd_scrollScreen(u32 numberofLine){
	for(iteratorRow=numberofLine;iteratorRow<MAX_ROWS;iteratorRow++){
		for(iteratorColumn=0;iteratorColumn<MAX_COLUMNS*2;iteratorColumn++){
			screenBuffer[iteratorRow-numberofLine][iteratorColumn]=screenBuffer[iteratorRow][iteratorColumn];
		}
	}
	currentRow=currentRow-numberofLine;
	vd_setCursor(currentRow,currentColumn/2);
		vd_flushVideoBuffer();
	return 0;
}

u32	vd_flushVideoBuffer(){
	u32 i;
	u8 * videoBuff= (u8 *)0xB8000;
	for(i = 0;i < (MAX_ROWS * MAX_COLUMNS * 2);i++)
		*videoBuff++ = screenBuffer[0][i];
	return 0;
}

u32	vd_getAttribute(){
	return attribute;
}

u32	vd_getXY(){
	return (currentRow & 0x00FF)<<16 | ((currentColumn / 2) & 0xFF);
}

u32	vd_setXY(u8 row,u8 column){
	vd_setCursor(row,column);
	currentRow=row;
	currentColumn=column * 2;
	return 0;
}

u32	vd_puts(u8 *str){
	u32 i=0;
	while(str[i]!=0){
		vd_putchar(str[i]);
		i++;
	}
	return 0;
}