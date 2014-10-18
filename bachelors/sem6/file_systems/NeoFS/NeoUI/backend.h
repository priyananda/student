#include <windows.h>
#include <winbase.h>
#include "resource.h"
#include <process.h>
#include <stdio.h>
#include <math.h>
#include <fstream>
using namespace std;

VOID QuickFormatHandler(HWND hDlg);
VOID FormatHandler(HWND hDlg);
VOID CheckFloppyHandler(HWND hDlg);
VOID InvokeShellHandler(HWND hDlg);
VOID AboutHandler(HWND hDlg);
VOID InitThread(HWND hWnd);
LRESULT CALLBACK	PasswordProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
extern char  szPassword[];