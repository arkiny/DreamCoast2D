#pragma once
class cIChatMgr
{
public:
	cIChatMgr();
	virtual ~cIChatMgr();
	virtual void Render() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, HINSTANCE hinst) = 0;
	virtual void OnInit() = 0;
};

