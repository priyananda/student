// NeoUI.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "backend.h"
#include "resource.h"
#include "commctrl.h"

#define MAX_LOADSTRING 100

// Global Variables
HINSTANCE hInst;					// current instance
TCHAR szTitle[MAX_LOADSTRING];		// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];// The title bar text
char szPassword[50];                //The password from  the dialog
unsigned int x = 0 ;                //Counter for WM_TIMER


// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	PasswordProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow){
	MSG msg;
	HACCEL hAccelTable;


	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_NEOUI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance (hInstance, nCmdShow))
		return FALSE;
	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_NEOUI);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)){
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;// What does it contain anyway
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance){
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_NEOUI);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_NEOUI;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);
	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow){
   HWND hWnd;
   hInst = hInstance; // Store instance handle in our global variable
   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
   if (!hWnd)
      return FALSE;
   //ShowWindow(hWnd, nCmdShow); - Invisible
   //UpdateWindow(hWnd);
   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){

    int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch (message) 
	{
		case WM_CREATE:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			PostQuitMessage(0);
			break;
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			RECT rt;
			GetClientRect(hWnd, &rt);
			DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int which;
	char temp[500];

	int i;
	switch (message)
	{
		case WM_INITDIALOG:
			x = 0;
			return TRUE;
		case WM_TIMER:
			SetDlgItemText(hDlg,IDC_EDIT1," ");
			strcpy(temp,"Please Wait ..." );
			for( i = 0 ; i < x ; ++i ){
				if(!(i%5)) strcat(temp,"\r\n");
				strcat(temp,"+");
			}
			++x;
			SetDlgItemText(hDlg,IDC_EDIT1,temp);
			break;
		case WM_COMMAND:
			which = LOWORD(wParam);
			switch(which){
				case IDOK:
				case IDCANCEL:
					EndDialog(hDlg,0);
					return TRUE;
					break;
				case IDC_BUTTON1:
					FormatHandler(hDlg);
					break;
				case IDC_BUTTON2:
					QuickFormatHandler(hDlg);
					break;
				case IDC_BUTTON3:
					CheckFloppyHandler(hDlg);
					break;
				case IDC_BUTTON4:
					InvokeShellHandler(hDlg);
					break;
				case IDC_BUTTON5:
					AboutHandler(hDlg);
					break;
			}
			break;
	}
    return FALSE;
}

LRESULT CALLBACK PasswordProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){
	int which;
	switch(message){
	case WM_INITDIALOG:
		return TRUE;
		break;
	case WM_COMMAND:
		which = LOWORD(wParam);
		switch(which){
			case IDOK:
				GetDlgItemText(hDlg,IDC_EDIT1,szPassword,49);
				if( strlen(szPassword))
					EndDialog(hDlg,0);
				else
					MessageBox(0,"Please Fill the Password","NEOUI",0);
				return TRUE;
				break;
			case IDCANCEL:
				szPassword[0] = 0;
				EndDialog(hDlg,0);
				return TRUE;
				break;
		}
		break;
	
	}
	return FALSE;
}
