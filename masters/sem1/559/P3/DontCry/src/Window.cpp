// CS559 Project 3 : Dont Cry
// author: priyananda( shenoy@cs.wisc.edu )
// date: 17 oct 2007
// random trivia: Dogs have 42 teeth.
// used code: the code in this file is mostly adapted
//   from my old game engine project pixelx( http://pixelx.sourceforge.net )
// That inturn was a mishmash of code taken from various sources
// most prominently from DigiBen's tutorials( http://www.gametutorials.com/ )

#include "resource.h"
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
	window->setupViewPorts();
	window->setCurrentViewPort(ViewPortMain);
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
    pfd.cStencilBits = bpp * 8;
 
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
	wndclass.hCursor = LoadCursor(NULL,NULL);
	wndclass.hbrBackground = (HBRUSH) (COLOR_WINDOW+1);
	//this just has to a unique string no one else will use
	wndclass.lpszClassName = TEXT("PRIYANANDAISGOD");
	wndclass.lpszMenuName = MAKEINTRESOURCE(IDR_QC_MENU);
	RegisterClass(&wndclass);

	HMENU h = LoadMenu( GetModuleHandleA(NULL),L"IDR_QC_MENU");

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

	hWnd = CreateWindowW(
		TEXT("PRIYANANDAISGOD"),
		TEXT("Window"),
		dwStyle, 0, 0,
		rWindow.right - rWindow.left,
		rWindow.bottom - rWindow.top, 
		NULL,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	if( hWnd == 0 ){
		MessageBox(NULL, TEXT("Couldn't create window"), TEXT("Error"), MB_OK);
		PostQuitMessage(0);
	}
	ShowCursor(FALSE);
	windows[hWnd] = this;
}
void Window::initGL()
{
	HGLRC hGlCtx = wglCreateContext(hDC);
	wglMakeCurrent(hDC,hGlCtx);
}
void Window::setupViewPorts()
{
	mainViewPort.set(0,0);
	mainViewPort.setSize(width,height);
	mainViewPort.setFrustrum(.1f,2000.0f,30.0f);

	leftViewPort.set(0,0);
	leftViewPort.setSize(width/2,height);

	rightViewPort.set(width/2,0);
	rightViewPort.setSize(width/2,height);
}
void Window::setCurrentViewPort(ViewPortType vt)
{
	getViewPort(vt).set(this);
}
ViewPort & Window::getViewPort(ViewPortType vt)
{
	switch(vt){
		case ViewPortMain: return mainViewPort;
		case ViewPortLeft: return leftViewPort;
		case ViewPortRight: return rightViewPort;
	}
	return mainViewPort;
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
				eventHandler->handleIdle();
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

void Window::setCaption(const char *p)
{
	::SetWindowTextA(this->hWnd,p);
}

void Window::setMenuVisible(bool val)
{
	if(val){
		if( this->hMenu )
			SetMenu(this->hWnd,this->hMenu);
	}else{
		HMENU h = GetMenu(this->hWnd);
		if( h ){
			this->hMenu = h;
			SetMenu(this->hWnd,NULL);
		}
	}
}

LRESULT CALLBACK windowProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT    lRet = 0; 
    PAINTSTRUCT    ps;

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
			eventHandler->handleMouse(
				eMouseLeftClick,
				pWindow->dragStartX = LOWORD(lParam),
				pWindow->dragStartY = HIWORD(lParam)
			);
			pWindow->dragging = true;
			break;
		case WM_LBUTTONUP:
			eventHandler->handleDrop(
				eMouseLeftClick,
				LOWORD(lParam) - pWindow->dragStartX,
				HIWORD(lParam) - pWindow->dragStartY
			);
			pWindow->dragging = false;
			break;
		case WM_RBUTTONDOWN:
			eventHandler->handleMouse(
				eMouseRightClick,
				pWindow->dragStartX = LOWORD(lParam),
				pWindow->dragStartY = HIWORD(lParam)
			);
			pWindow->dragging = true;
			break;
		case WM_RBUTTONUP:
			eventHandler->handleDrop(
				eMouseRightClick,
				LOWORD(lParam) - pWindow->dragStartX,
				HIWORD(lParam) - pWindow->dragStartY
			);
			pWindow->dragging = false;
		case WM_COMMAND:
			eventHandler->handleMenu(LOWORD(wParam));
			break;
		default:
			lRet = DefWindowProc (hWnd, uMsg, wParam, lParam);
			break;
    } 
	return lRet;
}

void Window::updateFPS()
{
	static float lastTime = 0;
	float currentTime = timeGetTime() / 1000.0f;//this is in milliseconds
	
	if( currentTime - lastTime >= 1.0f ){
		fps = 0;
		lastTime = currentTime;
	}else
		++fps;
}