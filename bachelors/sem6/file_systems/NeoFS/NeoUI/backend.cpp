#include "backend.h"

unsigned long   _beginthread( void(*f)(void*),unsigned int , void *);
void            _endthread();
extern HINSTANCE hInst;
static char szCommand[200];
extern unsigned int x;

typedef struct
{
     HWND hwnd ;
     int  cxClient ;
     int  cyClient ;
     int  cyChar ;
     BOOL bKill ;
}
PARAMS, *PPARAMS ;

void dispFile(char * mesg,const char * fileName){
	char buff[100];
	ifstream str;
	str.open(fileName);
	if( str.fail() ){ str.close(); return ;}
	str.getline(buff,98);
	strcat(mesg,buff);
	str.close();
}

VOID QuickFormatHandler(HWND hDlg){
	DialogBox(hInst, (LPCTSTR)IDD_DLGPASS, hDlg, (DLGPROC)PasswordProc);
	if(strlen(szPassword)){
		sprintf(szCommand,
				"%s %s > %s", 
				".\\qformat.exe",
				szPassword,
				"temp.txt"
				);
		InitThread(hDlg);
	}
}

VOID FormatHandler(HWND hDlg){
	DialogBox(hInst, (LPCTSTR)IDD_DLGPASS, hDlg, (DLGPROC)PasswordProc);
	if(strlen(szPassword)){
		sprintf(szCommand,
				"%s %s > %s", 
				".\\format.exe",
				szPassword,
				"temp.txt"
				);
		InitThread(hDlg);
	}
}

VOID CheckFloppyHandler(HWND hDlg){
	sprintf(szCommand,
			"%s  > %s", 
			".\\check.exe",
			"temp.txt"
	);
	InitThread(hDlg);
}

VOID InvokeShellHandler(HWND hDlg){
	sprintf(szCommand,
			"%s", 
			".\\shell.exe "
	);

	InitThread(hDlg);
	Sleep(1000);// Not Nice , But don't blame me
	PostQuitMessage(0);
}

VOID AboutHandler(HWND hDlg){
	MessageBox(0,"NEOFS File System Project\r\nAs Part of the File Structures laboratory Course \r\n\r\nBy\r\n*   Naveen B N\r\n*   Priyananda Shenoy","NEOUI",MB_ICONINFORMATION);
}

void FormatThread(PVOID _pParam){
	system(szCommand);
	PARAMS * pParam = (PARAMS *)_pParam;
	KillTimer(pParam->hwnd,1);
	char ff[100] = {0};
	dispFile(ff,"temp.txt");
	SetDlgItemText(pParam->hwnd,IDC_EDIT1,ff);
}

void InitThread(HWND hWnd){
	static  PARAMS p;
	p.hwnd = hWnd;
	SetTimer(hWnd,1,1000,NULL);
	x = 0 ; 
	_beginthread(FormatThread,0,&p);
}
