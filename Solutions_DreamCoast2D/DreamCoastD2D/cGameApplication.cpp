#include "stdAfx.h"
#include "cGameApplication.h"
#include "cIGameMgr.h"
#include "cIChatMgr.h"
#include "cChatManager.h"
#include "cD2DRenderer.h"
#include "chat_client.h"
#include <MMSystem.h>
#include  <atlstr.h>

cIGameMgr* g_pGameMgr;
cIChatMgr* g_pChatMgr;
cD2DRenderer d2dRender;

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
HINSTANCE _hInst;
HWND _hw;
HWND _hwMemo;

CIPMessage MyMessObj;
char buffer3[4096]; // out
char buffer4[4096]; // in

// ���� �ѹ� �Ÿ��� �޽��� ó��
void PreTranslateMessage(LPMSG msg){
	if (msg->message == WM_KEYUP)
	{
		switch (msg->wParam)
		{
		case VK_RETURN:
			if (GetFocus() == _hwMemo){
				GetDlgItemTextA(_hw, EDIT1, buffer2, sizeof(buffer2));
				if (strlen(buffer2) != 0){
					//ID
					string a = buffer2;
					GetDlgItemTextA(_hw, EDIT4, buffer2, sizeof(buffer2));
					string b = buffer2;
					a = b + ": " + a;

					MyMessObj.SendMessagePort(a);
					SetWindowText(GetDlgItem(_hw, EDIT1), L"");
				}
				else {
					SetFocus(_hw);
				}				
				break;
				//return;/*i don't want this message to reach the procedures anway*/
			}
		}
	}

	TranslateMessage(msg);
	DispatchMessage(msg);
}

RECT cGameApplication::_wndRect = { 0, 0, 1024, 768 };
cGameApplication::cGameApplication(cIGameMgr* pGameMgr, cIChatMgr* pChatMgr)
{
	g_pGameMgr = pGameMgr;
	g_pChatMgr = pChatMgr;
}


cGameApplication::~cGameApplication(void)
{
	delete g_pGameMgr;
	delete g_pChatMgr;
}

bool cGameApplication::Init(HINSTANCE hInstance, WCHAR* title, WCHAR* className, int nCmdShow)
{
	_hInst = hInstance;

	// ���ڿ��� �ʱ�ȭ�մϴ�.
	wsprintf(_szTitle, title);
	wsprintf(_szWindowClass, className);
	MyRegisterClass(hInstance);

	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	return TRUE;

}

//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
//  ����:
//
//    Windows 95���� �߰��� 'RegisterClassEx' �Լ����� ����
//    �ش� �ڵ尡 Win32 �ý��۰� ȣȯ�ǵ���
//    �Ϸ��� ��쿡�� �� �Լ��� ����մϴ�. �� �Լ��� ȣ���ؾ�
//    �ش� ���� ���α׷��� �����
//    '�ùٸ� ������' ���� �������� ������ �� �ֽ��ϴ�.
//
ATOM cGameApplication::MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASS wc = {};
	wc.hInstance = hInstance;
	wc.lpszClassName = _szWindowClass;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.style = 
		CS_VREDRAW | CS_HREDRAW | 
		CS_DBLCLKS;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpfnWndProc = WndProc;
	wc.lpszMenuName = NULL;

	return RegisterClass(&wc);
}


//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL cGameApplication::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	

	_hInst = hInstance; // �ν��Ͻ� �ڵ��� ��� ������ �����մϴ�.

	// Window Size���� Client�� ��Ȯ�ϰ� ���ϴ� ������� �����.
	//::AdjustWindowRect(&_wndRect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME, NULL);

	::AdjustWindowRect(&_wndRect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, NULL);
	hWnd = CreateWindow(_szWindowClass, _szTitle,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		| WS_THICKFRAME,
		CW_USEDEFAULT, 0, 
		_wndRect.right - _wndRect.left, 
		_wndRect.bottom - _wndRect.top, 
		/*1028,
		_wndRect.bottom - _wndRect.top,*/
		NULL, NULL, hInstance, NULL);


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

UINT  MessageRecThread(LPVOID pParam)
{
	while (1)
	{
		if (MyMessObj.RecMessagePort(_hw, MEMO1))
		break;
	}
	return 0;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND	- ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT	- �� â�� �׸��ϴ�.
//  WM_DESTROY	- ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
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
		//SetTimer(hWnd, TIMER, 50, NULL);

		//CreateButton(L"Send", 10, 62, 50, 20, BUTTON1, hWnd, _hInst);
		//CreateButton(L"Start", 10, 42, 50, 20, BUTTON2, hWnd, _hInst);

		FILE *fp = fopen("server.ini", "r");
		if (fp == NULL)
		{
			//MessageBox(hWnd, L"Unable to open server.ini. Please specify server IPsddress in server.ini", L"Warning", MB_OK);
			//PostQuitMessage(NULL);
			cChatManager::GetInstance().addToChatLog("���� ���� �ε� �Ұ�");
			break;
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
			cChatManager::GetInstance().addToChatLog("�������ϳ����� �ּ� �ε� �Ұ�");
			break;
			//MessageBox(hWnd, L"Unable to find server IPaddress in server.ini", L"Warning", MB_OK);
			//PostQuitMessage(NULL);
		}

		TCHAR szProxyAddr[16];
		_tcscpy_s(szProxyAddr, CA2T(sServerAddress.c_str()));
		//
		//CreateEdit(szProxyAddr, 70, 42, 180, 20, EDIT2, hWnd, _hInst); // ip
		//CreateEdit(L"8084", 260, 42, 90, 20, EDIT3, hWnd, _hInst); // port
		//
		_hwMemo = CreateEdit(L"", 730, 686, 180, 20, EDIT1, hWnd, _hInst);
		CreateEdit(L"ID", 260, 62, 90, 20, EDIT4, hWnd, _hInst);		
		CreateMemo(L"Info.\n", 2-800, 85, 350, 120, MEMO1, hWnd, _hInst);

		//SetFocus(GetDlgItem(hWnd, BUTTON1));
		//EnableWindow(GetDlgItem(hWnd, BUTTON1), FALSE);
		EnableWindow(GetDlgItem(hWnd, EDIT1), FALSE);
		EnableWindow(GetDlgItem(hWnd, BUTTON2), TRUE);
		EnableWindow(GetDlgItem(hWnd, BUTTON2), FALSE);
		//EnableWindow(GetDlgItem(hWnd, BUTTON1), TRUE);
		EnableWindow(GetDlgItem(hWnd, EDIT2), FALSE);
		EnableWindow(GetDlgItem(hWnd, EDIT3), FALSE);
		MyMessObj.Init(sServerAddress, 8084);
		if (!MyMessObj.IsConnected())
		{
			//MessageBox(hWnd, L"Unable to connect to the IPaddress specified in server.ini", L"Warning", MB_OK);
			cChatManager::GetInstance().addToChatLog("�������ӺҰ�");
			EnableWindow(GetDlgItem(hWnd, EDIT1), FALSE);
			break;
			//PostQuitMessage(NULL);
		}
		else {
			cChatManager::GetInstance().addToChatLog("ä�� �������ӿϷ�");
		}
		EnableWindow(GetDlgItem(hWnd, EDIT1), TRUE);
		AfxBeginThread(MessageRecThread, 0);

		SetFocus(hWnd);
		break;
	}
	case WM_SETFOCUS:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case EDIT1:
			SetWindowText(GetDlgItem(hWnd, EDIT1), L"");
			break;
		case EDIT4:
			SetWindowText(GetDlgItem(hWnd, EDIT4), L"");
			break;
		default:
			break;
		}
		break;
	/*case WM_TIMER:{
			
			break;
	}*/
	case WM_KEYUP:
		switch (wParam){
		case VK_RETURN : 
			if (IsWindowEnabled(GetDlgItem(hWnd, EDIT1))){
				SetFocus(_hwMemo);
			}			
			break;
		}
		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{		
		//case BUTTON2:
			//EnableWindow(GetDlgItem(hWnd, BUTTON2), FALSE);
			////EnableWindow(GetDlgItem(hWnd, BUTTON1), TRUE);
			//EnableWindow(GetDlgItem(hWnd, EDIT2), FALSE);
			//EnableWindow(GetDlgItem(hWnd, EDIT3), FALSE);
			//MyMessObj.Init(sServerAddress, 8084);
			//if (!MyMessObj.IsConnected())
			//{
			//	//MessageBox(hWnd, L"Unable to connect to the IPaddress specified in server.ini", L"Warning", MB_OK);
			//	cChatManager::GetInstance().addToChatLog("�������ӺҰ�");
			//	//PostQuitMessage(NULL);
			//}
			//EnableWindow(GetDlgItem(hWnd, EDIT1), TRUE);
			//AfxBeginThread(MessageRecThread, 0);
			//SetFocus(GetDlgItem(hWnd, EDIT1));
			//break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
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

	// �⺻ �޽��� �����Դϴ�.
	/// todo : ����FPS�� ���������� ������ ���Ӽӵ� ����
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			/*TranslateMessage(&msg);
			DispatchMessage(&msg);*/
			PreTranslateMessage(&msg);
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
				_fps = (accumFrame*1000.0f) / accumTime;	// �־��� ��� 1 frame�� ������ ���� �� �ִ�

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
	if (g_pChatMgr != nullptr)
		g_pChatMgr->Render();

	hr = d2dRender.GetRenderTarget()->EndDraw();
	assert(hr == S_OK);

	d2dRender.EndRender();
}

void cGameApplication::Update(float deltaTime)
{
	g_pGameMgr->Update(deltaTime);
	g_pChatMgr->Update(deltaTime);
}
