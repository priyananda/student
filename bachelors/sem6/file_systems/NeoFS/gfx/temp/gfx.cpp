#include "gfx.h"


int GraphicContext::maxX = 0;
int GraphicContext::maxY = 0;

void GraphicContext::init(){
	struct palettetype pal;
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"");
	setbkcolor(LIGHTGRAY);
	cleardevice();
	maxX = getmaxx();
	maxY = getmaxy();
}

void GraphicContext::showTitle(char * _str){
	setcolor(BLUE);
	setfillstyle(SOLID_FILL , BLUE);
	setlinestyle(0,0,1);
	bar3d(1,1,639,50,3,1);
	setcolor(YELLOW);
    settextstyle(4, HORIZ_DIR,5);
	outtextxy(60,0,_str);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
}
void GraphicContext::drawWindow(){
	setcolor(WHITE);
	rectangle(1,1,maxX,maxY);
}

void Button::draw(){
    GraphicContext::hideMouse();
	setcolor(LIGHTGRAY);
	setfillstyle(SOLID_FILL ,LIGHTGRAY);
	setlinestyle(0,0,0);
	int cords[8] = { x - 2, y - 2,
					 x + width +2, y - 2 ,
					 x + width +2 , y + height +2,
					 x - 2 , y + height +2 };
	fillpoly(4,cords);
	setcolor(DARKGRAY);
	rectangle(x, y , x + width , y + height);
	if (state == NORMAL ){
		line( x + width +1 ,y +1 , x + width +1 , y + height +1 );
		line( x + width +2 ,y +2 , x + width +2 , y + height +2 );
		line( x + 1 ,y + height +1 , x + width +1 , y + height +1 );
		line( x + 2 ,y + height +2 , x + width +2 , y + height +2 );
	}
	if (state == HIGH ){
		line( x - 1 ,y -1 , x -1 , y + height -1 );
		line( x - 2 ,y -2 , x -2 , y + height -2 );
		line( x - 1 ,y -1 , x + width -1 , y - 1 );
		line( x - 2 ,y -2 , x + width -2 , y - 2 );
		setcolor(BLUE);
	}
	outtextxy(x + 10, y + 10 , text);
    GraphicContext::initMouse();
}
void GraphicContext::initMouse(){
	union REGS i,o ;
	i.x.ax=1 ;
	int86(0x33,&i,&o) ;return ;
}
int Button::contains(int _x,int _y){
	int ret = 0;
	if ( _x >=  x && _x <= x + width )
		if ( _y >=  y && _y <= y + height )
			ret  = 1;
	return ret;
}
void Button::addActionHandler(ActionHandler _h){
	handler = _h;
}

void Button::respond(){
	if(handler && state != DISABLED)
		handler();
}

void GraphicContext::getMouse(int *bu,int *x,int *y)
{
	union REGS i,o ;
	i.x.ax=3 ;
	int86(0x33,&i,&o) ;
	*bu=o.x.bx ;
	*x=o.x.cx ;
	*y=o.x.dx ;
	return ;
}
void Button::refresh(int _newstate ){
	if ( state != DISABLED && _newstate != state ){
		state = _newstate;
		draw();
	}
}

void GraphicContext::showSplash(){
	setbkcolor(BLACK);
	cleardevice();
	setcolor(RED);
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	int cords[] = { 200 , 150 ,
					450 , 150 ,
					450 , 325 ,
					200 , 325 };
	fillpoly(4, cords);
	rectangle( 203 , 153 , 447 , 322 );
	setcolor(BLUE);
	outtextxy( 210 , 180 , "This is brought to you by:");
	outtextxy( 240 , 200 , " * Naveen Bean");
	outtextxy( 240 , 220 , " * Shenoy The Great");
	outtextxy( 210 , 240 , "    as part of their ");
	outtextxy( 210 , 260 , "File Structures Project");
	outtextxy( 210 , 280 , "**++--Eminem Rulez--++**");
}


Container::Container(int _nButt , int _x,int _y , int _bw , int _bh){
	numButtons = _nButt;
	buttons = new Button[_nButt];
	x = _x ; y = _y;
	bWidth = _bw;
	bHeight = _bh;
	strcpy(title,"Panel");
	titleColor = BLUE;
	for ( int i = 0 ; i < numButtons ; ++i ){
		buttons[i].y = y + i * ( bHeight + 20 ) + 25;
		buttons[i].x = x + 10 ;
		buttons[i].width = bWidth;
		buttons[i].height = bHeight;
	}
}

void Container::draw(){
//	setfillstyle(SOLID_FILL,LIGHTGRAY);
	bar( x , y ,
		x + bWidth + 20 , buttons[numButtons - 1].y + bHeight + 10 );
	setfillstyle(SOLID_FILL,titleColor);
	bar(x + 1 , y + 1 , x + bWidth + 19 , y + 15 );
	rectangle( x , y ,
		x + bWidth + 20 , buttons[numButtons - 1].y + bHeight + 10 );
	setcolor(YELLOW);
	outtextxy(x + 7 , y + 3 , title);
	for (int i = 0; i < numButtons ; ++i ){
		buttons[i].draw();
	}
}
void Container::doDisable(int _index){
	if( _index < numButtons )buttons[_index].state = DISABLED;
}
void Container::doDisable(){
	for (int i = 0; i < numButtons ; ++i ){
		buttons[i].state = DISABLED;
	}
	titleColor = DARKGRAY;
}
void Container::setText(int _index , char * str){
	if( _index < numButtons )
		strcpy(buttons[_index].text , str);
}
void Container::setText(char ** str){
	for (int i = 0; i < numButtons ; ++i ){
		strcpy ( buttons[i].text , str[i] );
	}
}
void Container::checkForEvents(int w,int _x,int _y){
	for (int i = 0; i < numButtons ; ++i ){
		if( buttons[i].contains( _x,_y)){
			buttons[i].refresh(HIGH);
			if ( w & 1 ) respond(i);
			break;
		}
		else buttons[i].refresh(NORMAL);
	}
}
void Container::respond(int index){
	static int x = 1;
	if ( buttons[index].state == DISABLED ) return;
	x++;
	char text[100];
	sprintf( buttons[index].text , "%d" , x);
	buttons[index].draw();
}
void Container::doEnable(int i){
	if( i < numButtons ) buttons[i].state = NORMAL;
}

void Container::doEnable(){
	for (int i = 0; i < numButtons ; ++i ){
		buttons[i].state = NORMAL;
	}
	titleColor = BLUE;
}

void GraphicContext::hideMouse(){
	union REGS i,o;
	i.x.ax=2 ;
	int86(0x33,&i,&o);return ;
}
void ProgressBar::draw(){
	setlinestyle(0,0,1);
	setcolor(DARKGRAY);
	rectangle( x , y , x + width , y + height + 15 );
	changed =  1;
	refresh();
}

void ProgressBar::refresh(){
	int vx1 , vx2 , vy1 , vy2 , tenpx , tenpy;
	double currX;
	if ( !changed  || maxVal == 0) return;
	changed = 0;
	tenpx = width / 20;
	tenpy = height / 5;
	vx1 = x + tenpx ;
	vy1 = y + tenpy ;
	vx2 = x + width - tenpx ;
	vy2 = y + height - tenpy ;
	rectangle ( x + tenpx -1 , y + tenpy -1,
				x + width - tenpx + 1 , y + height - tenpy+1 );
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	bar ( vx1 , vy1, vx2,vy2);
	bar ( x + 3 , y + height + 5 , x + width - 3 , y + height + 12 );
	if ( currentVal == 0 ) return ;
	currX = (float)( vx2 - vx1 ) / maxVal ;
        setfillstyle(SOLID_FILL , BLUE);
        bar( vx1, 
             vy1,
             int ( vx1 + currX * currentVal) ,
             vy2
        );
	sprintf( text , "Completed: %5.2f%%" , float(currentVal) * 100 / maxVal);
	outtextxy( x + 3 , y + height + 5  , text);
}
void ProgressBar::undraw(){
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	bar ( x - 1 , y -1 , x + width + 1 , y + height + 15 );
}
void ProgressBar::increment(unsigned int _step){
	if ( up ){
		if ( currentVal + _step > maxVal )
			currentVal = maxVal;
		else
			currentVal += _step;
		changed = 1;
		if ( currentVal == maxVal ) up = 0;
	}else{
		if ( currentVal - (int) _step < 0 )
			currentVal = 0;
		else
			currentVal -= _step;
		changed = 1;
		if ( currentVal == 0 ) up = 1;
	}
}
void GraphicContext::close(){
	closegraph();
	restorecrtmode();
}

int  HCDialogBox::showDialog(){
	int width = 400;
	int height = 200;
	int retVal = CANCEL;
	x = GraphicContext::maxX / 2 -  width / 2 ;
	y = GraphicContext::maxY / 2 -  height / 2 ;
	GraphicContext::hideMouse();
	int _imgsize = imagesize(x - 20 ,y - 20,x + width + 20 , y + height + 20);
	char * buffer = new char [ _imgsize ];
	getimage( x - 20 ,y - 20 ,x + width + 20 , y + height + 20 , buffer);
	setfillstyle(SOLID_FILL , LIGHTGRAY);
	bar( x , y , x + width  , y + height);
	setfillstyle(SOLID_FILL,BLUE);
	bar(x , y , x + width  , y + 15 );
	rectangle( x , y ,
		x + width  , y + height );
	line( x + 1 , y + height +1 , x+ width +1 , y + height + 1);
	line( x + 1 , y + height -1 , x+ width +1 , y + height - 1);
	line( x + width + 1, y + 1 , x+ width +1 , y + height + 1);
	line( x + width - 1 ,y + 1 , x+ width -1 , y + height + 1);
	setcolor(YELLOW);
	outtextxy(x + 7 , y + 3 , title);
	setcolor(DARKGRAY);
	outtextxy(x + 40 , y + 40 , message );
	setcolor(RED);
	GraphicContext::initMouse();
	Button * bFirst = NULL;
	Button * bSecond = NULL;
	switch ( type ){
		case OK_CANCEL_DIALOG:
			bFirst = new Button("OK" , x + 100 , y + 110 , 70 , 30 );
			bSecond = new Button("Cancel" , x + 200 , y + 110 , 70 , 30 );
			bFirst->draw();
			bSecond->draw();
			break;
		case OK_DIALOG       :
			bFirst = new Button("OK" , x + 100 , y + 110 , 70 , 30 );
			bFirst->draw();
			break;
		case YES_NO_DIALOG   :
			bFirst = new Button("Yes" , x + 100 , y + 110 , 70 , 30 );
			bSecond = new Button("No" , x + 200 , y + 110 , 70 , 30 );
			bFirst->draw();
			bSecond->draw();
			break;
	}
	while(1){
		int wh,x,y;
		wh = 0 ;
		GraphicContext::getMouse(&wh,&x,&y);
		if ( bFirst && bFirst->contains(x,y) ){
			bFirst->refresh(HIGH);
			if (bSecond) bSecond->refresh(NORMAL);
			if ( wh & 1){ retVal = OK ; break; }
		}
		if ( bSecond && bSecond->contains(x,y) ){
			bSecond->refresh(HIGH);
			if (bFirst) bFirst->refresh(NORMAL);
			if ( wh & 1){ retVal = CANCEL ; break; }
		}

		delay(70);
	}
	GraphicContext::hideMouse();
	putimage( x - 20 , y - 20 , buffer , COPY_PUT );
	free(buffer);
	GraphicContext::initMouse();
	return retVal;
}

void TextBlock::draw(){
	int width = 400 , height = 200 ;
	setfillstyle(SOLID_FILL,WHITE);
	setcolor(BLACK);
	rectangle( x , y , x + width , y + height);
	bar3d( x , y , x + width , y + height , 3 , 1);
	if ( numRows == 0 )return;
	setcolor(DARKGRAY);
	for ( int i = 0 ; i < 10 && i < numRows ; ++i)
		outtextxy( x + 10 , y + i * 15 + 10 , text[i] );
}

void TextBlock::setText(char * txt){
	strcpy( text[0] , txt);
	numRows = 1;
}
void TextBlock::setText(int _num , char ** tarr ){
	numRows = _num;
	for ( int i = 0 ; i < numRows ; ++ i )
		strcpy(text[i],tarr[i]);
}
void TextBlock::appendText(char * str){
	strcpy(text[numRows++],str);
}

void GraphicContext::showSidePanel(){
    setcolor(BLUE);
    circle( maxX / 2 , maxY /2 , 150 );
    circle( maxX / 2 , maxY /2 , 149 );
    setcolor(WHITE);
    circle( maxX / 2 , maxY /2 , 148 );
    circle( maxX / 2 , maxY /2 , 147 );
}

void GraphicContext::showMessage(char * mgs){
    setcolor(LIGHTGRAY);
    int x = maxX / 2 - 120;
    int y = maxY / 2;
    bar(x,y,x + 240 ,y + 20);
    setcolor(BLUE);
    outtextxy(x,y,mgs);
}

void GraphicContext::clearMessage(char * msg){
    
}