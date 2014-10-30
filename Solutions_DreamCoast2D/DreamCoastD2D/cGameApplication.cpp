#include "stdAfx.h"
#include "cGameApplication.h"
#include "cIGameMgr.h"
#include "cD2DRenderer.h"
#include "chat_client.h"
#include <MMSystem.h>
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
cIGameMgr* g_pGameMgr;
cD2DRenderer d2dRender;
HINSTANCE _hInst;
HWND _hw;

CIPMessage MyMessObj;
char buffer3[4096]; // out
char buffer4[4096]; // in

RECT cGameApplication::_wndRect = { 0, 0, 1024, 768 };
cGameApplication::cGameApplication(cIGameMgr* pGameMgr)
{
	g_pGameMgr = pGameMgr;
}


cGameApplication::~cGameApplication(void)
{
	delete g_pGameMgr;
}

bool cGameApplication::Init(HINSTANCE hInstance, WCHAR* title, WCHAR* className, int nCmdShow)
{
	_hInst = hInstance;

	// 문자열을 초기화합니다.
	wsprintf(_szTitle, title);
	wsprintf(_szWindowClass, className);
	MyRegisterClass(hInstance);
//	MyRegisterClass2(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	return TRUE;

}

//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
//  설명:
//
//    Windows 95에서 추가된 'RegisterClassEx' 함수보다 먼저
//    해당 코드가 Win32 시스템과 호환되도록
//    하려는 경우에만 이 함수를 사용합니다. 이 함수를 호출해야
//    해당 응용 프로그램에 연결된
//    '올바른 형식의' 작은 아이콘을 가져올 수 있습니다.
//
ATOM cGameApplication::MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASS wc = {};
	wc.hInstance = hInstance;
	wc.lpszClassName = _szWindowClass;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpfnWndProc = WndProc;
	wc.lpszMenuName = NULL;

	return RegisterClass(&wc);
}

//ATOM cGameApplication::MyRegisterClass2(HINSTANCE hInstance)
//{
//	WNDCLASS wc = {};
//	wc.hInstance = hInstance;
//	wc.lpszClassName = _szWindowClass;
//	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
//	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wc.style = CS_VREDRAW | CS_HREDRAW;
//	wc.cbClsExtra = 0;
//	wc.cbWndExtra = 0;
//	wc.lpfnWndProc = ChatProc;
//	wc.lpszMenuName = NULL;
//
//	return RegisterClass(&wc);
//}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL cGameApplication::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	HWND hWnd2;
	//HWND hWndChild;

	_hInst = hInstance; // 인스턴스 핸들을 멤버 변수에 저장합니다.

	// Window Size내의 Client를 정확하게 원하는 사이즈로 만든다.
	//::AdjustWindowRect(&_wndRect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME, NULL);

	::AdjustWindowRect(&_wndRect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, NULL);
	hWnd = CreateWindow(_szWindowClass, _szTitle,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME,
		CW_USEDEFAULT, 0, 
		_wndRect.right - _wndRect.left, 
		_wndRect.bottom - _wndRect.top, 
		/*1028,
		_wndRect.bottom - _wndRect.top,*/
		NULL, NULL, hInstance, NULL);


	hWnd2 = CreateWindow(_szWindowClass, _szTitle,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME,
		CW_USEDEFAULT, 0,
		360,
		190,
		/*1028,
		_wndRect.bottom - _wndRect.top,*/
		NULL, NULL, hInstance, NULL);
	//hWndChild = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"CHAT",
	//	/*WS_VISIBLE | WS_CHILD |
	//	ES_LEFT | ES_MULTILINE | WS_HSCROLL,*/
	//	WS_CHILD | WS_VISIBLE |
	//	WS_OVERLAPPEDWINDOW,
	//	CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hWnd,
	//	(HMENU)1004, hInstance, NULL);
	
	//hWndChild = CreateWindow(TEXT("Edit"), TEXT("test"), WS_CHILD | WS_VISIBLE | WS_BORDER, 
	//	100, 20, 140, 20, hWnd, NULL, NULL, NULL);


	if (!hWnd)
	{
		return FALSE;
	}

	_hwnd = hWnd;
	_hw = hWnd;
	GetClientRect(_hwnd, &_wndRect);

	d2dRender.InitializeD2D();
	d2dRender.Setup(hWnd);
	g_pGameMgr->OnInit();


	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	ShowWindow(hWnd2, nCmdShow);
	UpdateWindow(hWnd2);

	/*ShowWindow(hWndChild, nCmdShow);
	UpdateWindow(hWndChild);*/
	return TRUE;
}

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
		WS_CHILD | WS_VISIBLE |
		ES_MULTILINE | ES_AUTOHSCROLL,
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



//LRESULT CALLBACK cGameApplication::ChatProc(HWND hW, UINT message, WPARAM wParam, LPARAM lParam) {
//	int wmId, wmEvent;
//	PAINTSTRUCT ps;
//	HDC hdc;
//	char buf[4096];
//
//	switch (message)
//	{
//	case WM_PAINT:
//		hdc = BeginPaint(hW, &ps);
//		// TODO: 여기에 그리기 코드를 추가합니다.
//		EndPaint(hW, &ps);
//		break;
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//	default:
//		return DefWindowProc(hW, message, wParam, lParam);
//	}
//	return 0;
//}
UINT  MessageRecThread(LPVOID pParam)
{
	while (1)
	{
		if (MyMessObj.RecMessagePort(_hw, MEMO1));
		break;
	}
	return 0;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND	- 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT	- 주 창을 그립니다.
//  WM_DESTROY	- 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK cGameApplication::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	g_pGameMgr->MsgProc(hWnd, message, wParam, lParam, _hInst);
	
	char buf[4096];
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;	
	//HWND hWndChild;

	switch (message)
	{		
	case WM_CREATE:{
		SetTimer(hWnd, TIMER, 50, NULL);

		CreateButton(L"Send", 10, 22, 50, 20, BUTTON1, hWnd, _hInst);
		CreateButton(L"Start", 10, 2, 50, 20, BUTTON2, hWnd, _hInst);

		FILE *fp = fopen("server.ini", "r");
		if (fp == NULL)
		{
			MessageBox(hWnd, L"Unable to open server.ini. Please specify server IPsddress in server.ini", L"Warning", MB_OK);
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
			MessageBox(hWnd, L"Unable to find server IPaddress in server.ini", L"Warning", MB_OK);
			PostQuitMessage(NULL);
		}

		TCHAR szProxyAddr[16];
		_tcscpy_s(szProxyAddr, CA2T(sServerAddress.c_str()));
		//
		CreateEdit(szProxyAddr, 70, 2, 180, 20, EDIT2, hWnd, _hInst); // ip
		CreateEdit(L"8084", 260, 2, 90, 20, EDIT3, hWnd, _hInst); // port
		//
		CreateEdit(L"", 70, 22, 180, 20, EDIT1, hWnd, _hInst);
		CreateEdit(L"ID", 260, 22, 90, 20, EDIT4, hWnd, _hInst);
		
		CreateMemo(L"Info.\n", 2, 45, 350, 120, MEMO1, hWnd, _hInst);

		SetFocus(GetDlgItem(hWnd, BUTTON1));
		EnableWindow(GetDlgItem(hWnd, BUTTON1), FALSE);
		EnableWindow(GetDlgItem(hWnd, BUTTON2), TRUE);
		break;
	}
	case WM_SETFOCUS:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case EDIT1:
			//SendMessage(GetDlgItem(hW, EDIT1), EM_SETSEL, -1, -1);
			SetWindowText(GetDlgItem(hWnd, EDIT1), L"");
			break;
		case EDIT4:
			SetWindowText(GetDlgItem(hWnd, EDIT4), L"");
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
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{

		case BUTTON1:{
			GetDlgItemTextA(hWnd, EDIT4, buffer2, sizeof(buffer2));
			string a = buffer2;
			GetDlgItemTextA(hWnd, EDIT1, buffer2, sizeof(buffer2));
			a = a + ": " + buffer2;
			//basic_string<TCHAR> str = buffer2;

			MyMessObj.SendMessagePort(a);
			//SendMessage(GetDlgItem(hW, EDIT1), EM_SETSEL, -1, -1);
			SetWindowText(GetDlgItem(hWnd, EDIT1), L"");
			break;
		}
		case BUTTON2:
			EnableWindow(GetDlgItem(hWnd, BUTTON2), FALSE);
			EnableWindow(GetDlgItem(hWnd, BUTTON1), TRUE);
			EnableWindow(GetDlgItem(hWnd, EDIT2), FALSE);
			EnableWindow(GetDlgItem(hWnd, EDIT3), FALSE);
			MyMessObj.Init(sServerAddress, 8084);
			if (!MyMessObj.IsConnected())
			{
				MessageBox(hWnd, L"Unable to connect to the IPaddress specified in server.ini", L"Warning", MB_OK);
				PostQuitMessage(NULL);
			}
			AfxBeginThread(MessageRecThread, 0);
			SetFocus(GetDlgItem(hWnd, EDIT1));
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 그리기 코드를 추가합니다.
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

void cGameApplication::Run()
{
	DWORD prevTime = timeGetTime();
	DWORD curTime = prevTime;
	DWORD deltaTime = 0;
	DWORD accumTime = 0;
	int   accumFrame = 0;

	MSG msg;

	// 기본 메시지 루프입니다.
	/// todo : 가변FPS에 비의존적인 일정한 게임속도 구현
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			curTime = timeGetTime();
			deltaTime = curTime - prevTime;
			prevTime = curTime;

			accumTime += deltaTime;
			accumFrame++;

			static WCHAR fpsString[20] = L"";

			if (accumTime >= 1000)
			{
				_fps = (accumFrame*1000.0f) / accumTime;	// 최악의 경우 1 frame의 오차가 있을 수 있다

				accumTime -= 1000;
				accumFrame = 0;

				swprintf(fpsString, 20, L"FPS : %2.2f", _fps);
				SetWindowText(_hwnd,fpsString);
			}

			Update(deltaTime / 1000.0f);
			Render();
		}
	}
}

void cGameApplication::Render()
{
	d2dRender.BeginRender(_hwnd);
	HRESULT hr = E_FAIL;
	d2dRender.GetRenderTarget()->BeginDraw();
	d2dRender.GetRenderTarget()->SetTransform(::D2D1::Matrix3x2F::Identity());
	d2dRender.GetRenderTarget()->Clear(::D2D1::ColorF(::D2D1::ColorF::White));

	if (g_pGameMgr != nullptr)
		g_pGameMgr->Render();

	hr = d2dRender.GetRenderTarget()->EndDraw();
	assert(hr == S_OK);

	d2dRender.EndRender();
}

void cGameApplication::Update(float deltaTime)
{
	g_pGameMgr->Update(deltaTime);
}
