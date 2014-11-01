#pragma once
#include "cIChatMgr.h"

class cChatManager : public cIChatMgr
{
public:
	cChatManager();
	~cChatManager();
	virtual void Render() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, HINSTANCE hinst) = 0;
	virtual void OnInit() = 0;
};

