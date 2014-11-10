#pragma once
class cPlayer;
class cIGameMgr
{
public:
	cIGameMgr(void);
	virtual ~cIGameMgr(void);
	virtual void Render() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, HINSTANCE hinst) = 0;
	virtual void OnInit() = 0;
};

