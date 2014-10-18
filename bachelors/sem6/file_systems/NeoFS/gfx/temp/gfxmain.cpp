#include "gfx.h"
#include "floppy.h"

#define DispatchMessage(ptr)       \
        if ( ptr->contains(x,y) ){ \
            ptr->refresh(HIGH);    \
            if ( wh & 1 )          \
                ptr->respond();    \
        }


ProgressBar * ptrPB  = NULL;
Button      * ptrExit = NULL,
            * ptrBFormat = NULL ,
            * ptrBQuickFormat = NULL,
            * ptrHelp = NULL,
            * ptrBAbout = NULL ,
            * ptrBCheck = NULL,
            * ptrBShell = NULL;

HCDialogBox * ptrDlgExit  = NULL ,
            * ptrDlgFormat = NULL,
            * ptrDlgAboutUs = NULL,
            * ptrDlgCheck = NULL;

void bFormat_handler();
void bQuickFormat_handler();
void bAbout_handler();
void bCheck_handler();
void bHelp_handler();
void bShell_handler();

int main(){
    int wh,x,y;

    GraphicContext::init();
    GraphicContext::showTitle("Welcome to N E O F S" );
    GraphicContext::drawWindow();
    GraphicContext::showSidePanel();
    GraphicContext::initMouse();

    ptrPB   = new ProgressBar( 250, GraphicContext::maxY / 2 ,150,30,100);
    ptrDlgExit = new HCDialogBox( "Do You Really Want to quit?" ,
                                   "****N E O F S****" ,
                                   YES_NO_DIALOG );
    ptrDlgFormat = new HCDialogBox("This will remove all your data , Continue?" ,
                                   "Formatting FDD0" ,
                                    YES_NO_DIALOG);
    ptrDlgAboutUs = new HCDialogBox("By Naveen B N & Priyananda Shenoy P " ,
                                   "****N E O F S****" ,
                                    OK_DIALOG);
    ptrDlgCheck = new HCDialogBox("Checking floppy for bad sectors , Continue?" ,
                                   "****N E O F S****" ,
                                    YES_NO_DIALOG);

    ptrBFormat = new Button( "Format" , 68 ,150 , 110 , 30);
    ptrBQuickFormat = new Button("Quick Format" , 58 ,200  , 110 , 30 );
    ptrExit = new Button ( "Exit" ,102,100,110,30);
    ptrBShell = new Button ( "Invoke Shell",58,250,110,30);

    ptrHelp = new Button ( "Help" , 470,250,110,30);
    ptrBAbout = new Button ( "About Us", 460,300 , 110,30);
    ptrBCheck = new Button ( "Check Floppy",415,350,110,30);


    ptrExit->draw();
    ptrBFormat->draw();
    ptrBQuickFormat->draw();
    ptrHelp->draw();
    ptrBAbout->draw();
    ptrBCheck->draw();
    ptrBShell->draw();

    ptrBFormat->addActionHandler( bFormat_handler);
    ptrBQuickFormat->addActionHandler( bQuickFormat_handler);
    ptrBAbout->addActionHandler( bAbout_handler);
    ptrBCheck->addActionHandler( bCheck_handler);
    ptrHelp->addActionHandler( bHelp_handler);
    ptrBShell->addActionHandler(bShell_handler);
    fflush(stdin);
    //Message Loop
    while(1){
        wh = 0 ;
        ptrBFormat->refresh(NORMAL);
        ptrBQuickFormat->refresh(NORMAL);
        ptrExit->refresh(NORMAL);
        ptrHelp->refresh(NORMAL);
        ptrBAbout->refresh(NORMAL);
        ptrBCheck->refresh(NORMAL);
        ptrBShell->refresh(NORMAL);

        GraphicContext::getMouse(&wh,&x,&y);
        if ( ptrExit->contains(x,y) ){
            ptrExit->refresh(HIGH);
            if ( ( wh & 1 ) &&  ptrDlgExit->showDialog() == YES )
                break;
        }
        DispatchMessage(ptrBFormat)
        DispatchMessage(ptrBQuickFormat)
        DispatchMessage(ptrHelp)
        DispatchMessage(ptrBAbout)
        DispatchMessage(ptrBCheck)
        DispatchMessage(ptrBShell)
        delay(70);
    }
    GraphicContext::hideMouse();
    fflush(stdin);
    GraphicContext::showSplash();
    getch();
    GraphicContext::close();
    return 0;
}


void bFormat_handler(){
    int h=0,count=0,t=0,s=0;
    char temp[200];
    if (ptrDlgFormat->showDialog() == CANCEL)
        return;
    ptrPB->setValue(0);
    ptrPB->draw();
    reset_floppy();
    if(!check_for_floppy()){
        HCDialogBox( "Floppy Not Ready",
                 "****N E O F S****" ,
                 OK_DIALOG ).showDialog();
        ptrPB->undraw();
        ptrPB->setMax(100);
        return;
    } 
    for ( t = 0 ; t < 80 ; ++t){
        ptrPB->refresh(1);       
        for ( s = 1 ; s <= 18 ; ++s )
            for ( h = 0 ; h < 2 ; ++h )
                if ( get_sector_status(h,t,s) )
                    count++;
    }    
    sprintf(temp,"Number of Bad Sectors : %d " , count); 
    HCDialogBox( temp,
                 "****N E O F S****" ,
                 OK_DIALOG ).showDialog();
    /********************** Call MKFS SomeHow ******************/
    ptrPB->undraw();
}

void bQuickFormat_handler(){
    if (ptrDlgFormat->showDialog() == CANCEL) return;
    ptrPB->draw();
    int i;
    ptrPB->setValue(0);
    for (i = 0 ;i < 100 ;++i ){
        ptrPB->refresh(1);
        delay(30);
    }
    ptrPB->undraw();
}

void bAbout_handler(){
    ptrDlgAboutUs->showDialog();
}
void bCheck_handler(){
    char temp[100];
    int x;
    int count = 0,t,h,s;
    if (ptrDlgCheck->showDialog() == CANCEL)
        return;
    ptrPB->draw();
    ptrPB->setValue(0);
    ptrPB->setMax(80);
    reset_floppy();
    if(!check_for_floppy()){
        HCDialogBox( "Floppy Not Ready",
                 "****N E O F S****" ,
                 OK_DIALOG ).showDialog();
        ptrPB->undraw();
        ptrPB->setMax(100);
        return;
    } 
    for ( t = 0 ; t < 80 ; ++t){
            ptrPB->refresh(1);       
            for ( s = 1 ; s <= 18 ; ++s )
                    for ( h = 0 ; h < 2 ; ++h )
                            if ( get_sector_status(h,t,s) )count++;
    }
    sprintf(temp,"Number of Bad Sectors : %d " , count); 
    HCDialogBox( temp,
                 "****N E O F S****" ,
                 OK_DIALOG ).showDialog();
    ptrPB->undraw();
    ptrPB->setMax(100);
}
void bHelp_handler(){
    delay(50);
    int wh,x,y;
    GraphicContext::showMessage("Move Mouse on buttons for help");
    while(1){
        delay(100);
        GraphicContext::getMouse(&wh,&x,&y);
        if ( ptrExit->contains(x,y) )
            GraphicContext::showMessage("Quits from application");
        if ( ptrBShell->contains(x,y) )
            GraphicContext::showMessage("Invokes Command Line Shell");
        if ( ptrBFormat->contains(x,y) )
            GraphicContext::showMessage("Full Formats the floppy");
        if ( ptrBQuickFormat->contains(x,y) )
            GraphicContext::showMessage("Quick Formats the Floppy");
        if ( ptrBCheck->contains(x,y) )
            GraphicContext::showMessage("Checks floppy for bad sectors");
        if ( ptrExit->contains(x,y)  && ( wh &1 )){
            GraphicContext::showMessage("  ");
            return ;
        }
    }
}

void bShell_handler(){
    GraphicContext::hideMouse();
    GraphicContext::close();
    system("shell");
    exit(0);
}

