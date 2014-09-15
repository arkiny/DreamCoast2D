#pragma once
#include <Windows.h>
#pragma comment(lib, "winmm.lib")
class cIGameMgr;
class cGameApplication
{
public:
	cGameApplication(cIGameMgr*);
	virtual ~cGameApplication(void);

	bool Init(HINSTANCE hInstance, WCHAR* title, WCHAR* className, int nCmdShow);
	void Run();
	virtual void Update(float deltaTime);
	virtual void Render();

	virtual void Draw(HDC hdc){}
	HWND GetHWND(){ return _hwnd; }
	static RECT _wndRect;
private:
	BOOL	InitInstance(HINSTANCE, int);
	ATOM	MyRegisterClass(HINSTANCE hInstance);
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	HINSTANCE _hInst;								// ���� �ν��Ͻ��Դϴ�.
	HWND _hwnd;
	TCHAR _szTitle[128];					// ���� ǥ���� �ؽ�Ʈ�Դϴ�.
	TCHAR _szWindowClass[128];			// �⺻ â Ŭ���� �̸��Դϴ�.

	/// ���ø����̼��� ���� FPS(�ֱ� 1��)�� ����Ѵ�
	float _fps;
protected:

};

