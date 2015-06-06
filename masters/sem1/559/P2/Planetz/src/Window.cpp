// CS559 Project 2 : Quantum Coaster
// author: priyananda( shenoy@cs.wisc.edu )
// date: 17 oct 2007
// random trivia: Dogs have 42 teeth.
// used code: the code in this file is mostly adapted
//   from my old game engine project pixelx( http://pixelx.sourceforge.net )
// That inturn was a mishmash of code taken from various sources
// most prominently from DigiBen's tutorials( http://www.gametutorials.com/ )

#include "Window.h"
#include <GL/gl.h>

//a sample of horrors to come...
static LRESULT CALLBACK windowProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam);

//map of all windows in the application
map<HWND,Window *> Window::windows;
static bool isClassRegistered = false;

//creates a window of given dimensions
Window * Window::create(int w, int h, int bpp, bool fullscreen)
{
	Window * window = new Window();
	window->height = h;
	window->width = w;
	window->bpp = bpp;

	registerClass();
	window->createWindow(fullscreen);
	window->setPixelFormat();
	window->initGL();
	window->setViewPorts(1);
	window->setCurrentViewPort(0);
	if( fullscreen )
		window->switchToFullScreen();
	return window;
}

//sets the pixel format of the window: 16/24/32 bits per pixel
void Window::setPixelFormat()
{
	PIXELFORMATDESCRIPTOR pfd;
    int pixelformat;
 
	hDC = GetDC(this->hWnd);

    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER; 
    pfd.dwLayerMask = PFD_MAIN_PLANE;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = bpp * 8;
    pfd.cDepthBits = bpp * 8;
	//todo: enable stencil and accumulator buffers
    pfd.cAccumBits = 0;
    pfd.cStencilBits = 0;
 
    if ((pixelformat = ChoosePixelFormat(hDC, &pfd)) == FALSE ){ 
        MessageBox(NULL, TEXT("ChoosePixelFormat failed"), TEXT("Error"), MB_OK);
		PostQuitMessage(0);
    } 
    if (SetPixelFormat(hDC, pixelformat, &pfd) == FALSE){ 
        MessageBox(NULL, TEXT("SetPixelFormat failed"), TEXT("Error"), MB_OK);
		PostQuitMessage(0);
    }
}

//full screen mode
void Window::switchToFullScreen()
{
	DEVMODE dmSettings;
	memset(&dmSettings,0,sizeof(dmSettings));
	if(!EnumDisplaySettings(NULL,-1,&dmSettings)){
		MessageBox(NULL, TEXT("Could Not Enum Display Settings"), TEXT("Error"), MB_OK);
		return;
	}
	dmSettings.dmPelsWidth	= this->width;
	dmSettings.dmPelsHeight	= this->height;
	dmSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
	if(ChangeDisplaySettings(&dmSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL){
		MessageBox(NULL, TEXT("Display Mode Not Compatible"), TEXT("Error"), MB_OK);
		PostQuitMessage(0);
	}
}
//register the windows class
void Window::registerClass()
{
	if( isClassRegistered )
		return;

	WNDCLASS wndclass;	
	memset(&wndclass, 0, sizeof(WNDCLASS));
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = windowProc;
	wndclass.hInstance = GetModuleHandle(NULL);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH) (COLOR_WINDOW+1);
	//this just has to a unique string no one else will use
	wndclass.lpszClassName = TEXT("PRIYANANDAISGOD");
	RegisterClass(&wndclass);

	isClassRegistered = true;
}
void Window::createWindow(bool fs)
{
	DWORD dwStyle;
	if(fs)
		dwStyle = WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	else
		dwStyle = WS_OVERLAPPEDWINDOW;

	RECT rWindow;
	rWindow.left	= 0;
	rWindow.right	= width;
	rWindow.top	    = 0;
	rWindow.bottom	= height;

	AdjustWindowRect( &rWindow, dwStyle, false);

	hWnd = CreateWindow(
		TEXT("PRIYANANDAISGOD"),
		TEXT("Window"),
		dwStyle, 0, 0,
		rWindow.right - rWindow.left,
		rWindow.bottom - rWindow.top, 
		NULL, NULL,
		GetModuleHandle(NULL),
		NULL
	);

	if( hWnd == 0 ){
		MessageBox(NULL, TEXT("Couldn't create window"), TEXT("Error"), MB_OK);
		PostQuitMessage(0);
	}
	windows[hWnd] = this;
}
void Window::initGL()
{
	HGLRC hGlCtx = wglCreateContext(hDC);
	wglMakeCurrent(hDC,hGlCtx);
}
void Window::setViewPorts(int number)
{
	if( viewports != NULL )
		delete [] viewports;
	viewports = new ViewPort*[number];
	for( int i = 0 ; i < number; ++i ){
		viewports[i] = new ViewPort();
		viewports[i]->setPosition(0,0);
		viewports[i]->setSize(width,height);
	}
}
void Window::setCurrentViewPort(int idx)
{
	viewports[idx]->set(this);
}
ViewPort * Window::getViewPort(int idx)
{
	return viewports[idx];
}
void Window::show()
{
	ShowWindow(this->hWnd,SW_SHOWNORMAL);
	SetFocus(this->hWnd);

	if(eventHandler != NULL)
		eventHandler->handleInit(this);

	MSG msg;
	while(true){
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			if(msg.message == WM_QUIT)
				break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
		else
			if( eventHandler != NULL )
				eventHandler->handleIdle( this );
	}
}

void Window::flush()
{
	glFlush();
	SwapBuffers(this->hDC);
}

void Window::close()
{
	//if fullscreened, go back to normal
	ChangeDisplaySettings(NULL,0);
	//kill the opengl context
	HGLRC hrc = wglGetCurrentContext();
	wglMakeCurrent(NULL,NULL);
	wglDeleteContext(hrc);
	//clear the DC
	ReleaseDC(hWnd,hDC);
	//get rid of the window
	DestroyWindow(hWnd);
}

LRESULT CALLBACK windowProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT    lRet = 0; 
    PAINTSTRUCT    ps;
	int xPos,yPos;

	Window * pWindow = Window::getWindow(hWnd);
	WindowEventHandler * eventHandler;
	if( pWindow != NULL )
		eventHandler = pWindow->getEventHandler();

    switch (uMsg)
	{ 
		case WM_PAINT:
			BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;
		case WM_KEYDOWN:
			eventHandler->handleKey( int(wParam) , eKeyStateDown );
			break;
		case WM_KEYUP:
			eventHandler->handleKey( int(wParam) , eKeyStateUp );
			break;
		case WM_CLOSE:
			PostQuitMessage(0);
			break;
		case WM_LBUTTONDOWN:
			xPos = LOWORD(lParam); 
			yPos = HIWORD(lParam); 
			eventHandler->handleMouse( eMouseLeftClick,xPos,yPos );
			break;
		case WM_RBUTTONDOWN:
			xPos = LOWORD(lParam); 
			yPos = HIWORD(lParam);
			eventHandler->handleMouse( eMouseRightClick ,xPos,yPos );
			break;
		default:
			lRet = DefWindowProc (hWnd, uMsg, wParam, lParam);
			break;
    } 
	return lRet;
}