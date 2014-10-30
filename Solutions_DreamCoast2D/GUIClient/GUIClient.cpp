// GUIClient.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "GUIClient.h"
#include "chat_client.h"
#include  <atlstr.h>

#define MAX_LOADSTRING 100
#define BUTTON1 501
#define BUTTON2 502
#define EDIT1 601
#define EDIT2 602
#define EDIT3 603
#define EDIT4 604
#define MEMO1 701
#define UN 100		
#define TIMER 1001
TCHAR buffer1[4096];
char buffer2[4096];
string sServerAddress;

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GUICLIENT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GUICLIENT));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GUICLIENT));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_GUICLIENT);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
HWND hWnd;
RECT wndRect = { 0, 0, 360, 190 };

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable
   ::AdjustWindowRect(&wndRect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, NULL);

  /* hWnd = CreateWindow(_szWindowClass, _szTitle,
	   WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
	   CW_USEDEFAULT, 0,
	   _wndRect.right - _wndRect.left,
	   _wndRect.bottom - _wndRect.top,
	   NULL, NULL, hInstance, NULL);*/


   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
	   CW_USEDEFAULT, 0, wndRect.right - wndRect.left, wndRect.bottom - wndRect.top, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//

HWND CreateButton(TCHAR *Titel, int x0, int y0, int w, int h, int ID, HWND hW, HINSTANCE hInst)
{
	return CreateWindowEx(WS_EX_PALETTEWINDOW, L"BUTTON", Titel,
		WS_VISIBLE | WS_CHILD,
		x0, y0, w, h, hW, (HMENU)ID, hInst, NULL);
}
HWND CreateEdit(TCHAR *Titel, int x0, int y0, int w, int h, int ID, HWND hW, HINSTANCE hInst)
{
	return CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", Titel,
		/*WS_VISIBLE | WS_CHILD |
		ES_LEFT | ES_MULTILINE | WS_HSCROLL,*/
		WS_CHILD|WS_VISIBLE|
		ES_MULTILINE|ES_AUTOHSCROLL,
		x0, y0, w, h, hW,
		(HMENU)ID, hInst, NULL);
}

HWND CreateMemo(TCHAR *Titel, int x0, int y0, int w, int h, int ID, HWND hW, HINSTANCE hInst)
{
	return CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", Titel,
		WS_VISIBLE | WS_CHILD |
		ES_LEFT | ES_MULTILINE | ES_READONLY |
		WS_HSCROLL | WS_VSCROLL,
		x0, y0, w, h,
		hW, (HMENU)ID, hInst, NULL);
}

void Puts(HWND hW, int ID_EDIT, char *str)
{
	int nLen = GetWindowTextLength(GetDlgItem(hW, ID_EDIT));
	SendMessage(GetDlgItem(hW, ID_EDIT), EM_SETSEL, nLen, nLen);
	SendMessage(GetDlgItem(hW, ID_EDIT), EM_REPLACESEL, TRUE, (long)(LPCTSTR)str);
	nLen = GetWindowTextLength(GetDlgItem(hW, ID_EDIT));
	SendMessage(GetDlgItem(hW, ID_EDIT), EM_SETSEL, nLen, nLen);
	SendMessage(GetDlgItem(hW, ID_EDIT), EM_REPLACESEL, TRUE, (long)(LPCTSTR)"\r\n");
}

CIPMessage MyMessObj;
char buffer3[4096]; // out
char buffer4[4096]; // in

UINT  MessageRecThread(LPVOID pParam)
{
	while (1)
	{
		if (MyMessObj.RecMessagePort(hWnd, MEMO1));
			break;
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hW, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	char buf[4096];

	switch (message)
	{
	case WM_CREATE:{
		SetTimer(hW, TIMER, 50, NULL);

		CreateButton(L"Send", 10, 22, 50, 20, BUTTON1, hW, hInst);
		CreateButton(L"Start", 10, 2, 50, 20, BUTTON2, hW, hInst);

		FILE *fp = fopen("server.ini", "r");
		if (fp == NULL)
		{
			MessageBox(hW, L"Unable to open server.ini. Please specify server IPsddress in server.ini", L"Warning", MB_OK);
			PostQuitMessage(NULL);
		}

		while ((fgets(buf, 4096, fp)) != NULL)
		{
			if (buf[0] == '#')
				continue;
			sServerAddress = buf;

		}
		fclose(fp);

		if (sServerAddress.size() == 0)
		{
			MessageBox(hW, L"Unable to find server IPaddress in server.ini", L"Warning", MB_OK);
			PostQuitMessage(NULL);
		}

		TCHAR szProxyAddr[16];
		_tcscpy_s(szProxyAddr, CA2T(sServerAddress.c_str()));
		//
		CreateEdit(szProxyAddr, 70, 2, 180, 20, EDIT2, hW, hInst); // ip
		CreateEdit(L"8084", 260, 2, 90, 20, EDIT3, hW, hInst); // port
		//
		CreateEdit(L"", 70, 22, 180, 20, EDIT1, hW, hInst);
		CreateEdit(L"ID", 260, 22, 90, 20, EDIT4, hW, hInst);

		CreateMemo(L"Info.\n", 2, 45, 350, 120, MEMO1, hW, hInst);

		SetFocus(GetDlgItem(hW, BUTTON1));
		EnableWindow(GetDlgItem(hW, BUTTON1), FALSE);
		EnableWindow(GetDlgItem(hW, BUTTON2), TRUE);
		break;
	}
	case WM_SETFOCUS:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case EDIT1:
			//SendMessage(GetDlgItem(hW, EDIT1), EM_SETSEL, -1, -1);
			SetWindowText(GetDlgItem(hW, EDIT1), L"");
			break;
		case EDIT4:
			SetWindowText(GetDlgItem(hW, EDIT4), L"");
			break;
		default:
			break;
		}
		break;
	case WM_TIMER:{
		AfxBeginThread(MessageRecThread, 0);
		break;
	}
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		
		case BUTTON1:{
			GetDlgItemTextA(hW, EDIT4, buffer2, sizeof(buffer2));
			string a = buffer2;
			GetDlgItemTextA(hW, EDIT1, buffer2, sizeof(buffer2));
			a = a + ": " + buffer2;
			//basic_string<TCHAR> str = buffer2;
			
			MyMessObj.SendMessagePort(a);
			//SendMessage(GetDlgItem(hW, EDIT1), EM_SETSEL, -1, -1);
			SetWindowText(GetDlgItem(hW, EDIT1), L"");
			break;
		}
		case BUTTON2:
			EnableWindow(GetDlgItem(hW, BUTTON2), FALSE);
			EnableWindow(GetDlgItem(hW, BUTTON1), TRUE);
			EnableWindow(GetDlgItem(hW, EDIT2), FALSE);
			EnableWindow(GetDlgItem(hW, EDIT3), FALSE);
			MyMessObj.Init(sServerAddress, 8084);
			if (!MyMessObj.IsConnected())
			{
				MessageBox(hW, L"Unable to connect to the IPaddress specified in server.ini", L"Warning", MB_OK);
				PostQuitMessage(NULL);
			}
			AfxBeginThread(MessageRecThread, 0);
			SetFocus(GetDlgItem(hW, EDIT1));
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hW, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hW);
			break;
		default:
			return DefWindowProc(hW, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hW, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hW, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hW, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
