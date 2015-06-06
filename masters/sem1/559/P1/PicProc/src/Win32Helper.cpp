// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 24 sep 2007
// random quote: [Pulp Fiction] Winston Wolf: Just because you are a character doesn't mean you have character.
// note: various portions of this file have been modified from various win32 tutorials
//		The largest chunk came from http://www.codeguru.com/cpp/w-d/console/article.php/c3957/

#include "Win32Helper.h"
#include "TargaImage.h"
#include "SymbolTable.h"
#include <cstdio>

static HINSTANCE hInstance;
static TargaImage * image;

//extraordinarily unoptimised
//todo: create a bitmap and draw into it offline, and then just draw it everytime
static LRESULT CALLBACK windowProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam)
{  
	PAINTSTRUCT ps;
	HDC hdc;
	int width = image->width();
	int height = image->height();
	unsigned char * pixels = image->pixels();

    switch (uMsg) 
    { 
        case WM_CREATE:
		case WM_SIZE:
		case WM_DESTROY: 
            return 0; 
 
        case WM_PAINT: 
            hdc = BeginPaint(hWnd,&ps);
			for( int i = 0 ; i < width; ++i )
				for( int j = 0 ; j < height; ++j )
					SetPixel(hdc,i,j,
						RGB(
							pixels[ 4 * ( width * j + i )],
							pixels[ 4 * ( width * j + i ) + 1],
							pixels[ 4 * ( width * j + i ) + 2]
						)
					);
			EndPaint(hWnd,&ps);
            return 0; 
 		case WM_CLOSE:
			PostQuitMessage(0);
			break;
        default: 
            return DefWindowProc(hWnd, uMsg, wParam, lParam); 
    }
    return 0;
}


//registers a window class
static void registerWindow()
{
	static bool isRegistered = false;
	if(isRegistered)
		return;

	isRegistered = true;
	hInstance = static_cast<HINSTANCE>(GetModuleHandleA(NULL));

	WNDCLASS wndclass;	
	memset(&wndclass, 0, sizeof(WNDCLASS));
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = windowProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH) (COLOR_WINDOW+1);
	//this just has to a unique string no one else will use
	wndclass.lpszClassName = "PRIYANANDAISGOD";
	RegisterClass(&wndclass);
}

//blocking call.
void Win32Helper::showImage(char varName)
{
	image = SymbolTable::getSymbol(varName);
	if(image == NULL){
		printf( "No image found for variable %c\n",varName);
		return;
	}

	registerWindow();

	DWORD dwStyle = WS_OVERLAPPEDWINDOW;

	RECT rWindow;
	rWindow.left	= 0;
	rWindow.right	= image->width();
	rWindow.top	    = 0;
	rWindow.bottom	= image->height();

	AdjustWindowRect( &rWindow, dwStyle, false);

	static char buffer[100];
	sprintf_s(buffer,"%c %dx%d", varName,image->width(),image->height());

	HWND hWnd = CreateWindow(
		"PRIYANANDAISGOD",
		buffer,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rWindow.right  - rWindow.left,
		rWindow.bottom - rWindow.top,
		NULL,NULL,hInstance,NULL
	);

	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);
	SetFocus(hWnd);

	MSG msg;
	//todo: should I do this in another thread and make this non blocking?
	while (GetMessage(&msg, NULL, NULL, NULL)){
	  TranslateMessage(&msg);
	  DispatchMessage(&msg);
	}
	DestroyWindow(hWnd);
}