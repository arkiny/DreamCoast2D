#pragma once
#include "cD2DRenderer.h"
#include "cIGameMgr.h"

class coControl;
class wWorld;
class sIScreen;

class cGameManager :
	public cIGameMgr
{
public:
	cGameManager(void);
	virtual ~cGameManager(void);
	virtual void Render(cD2DRenderer&);
	virtual void Update(float deltaTime);
	virtual void MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual void OnInit(cD2DRenderer&);

	// 스크린 관리, 각 스크린이 콜백으로 받아와서, 씬관리를 한다?
	void changeScreen(sIScreen* in);
private:
	coControl* m_pControl;
	
	// 스크린 포인터, 스크린 관리
	sIScreen* m_pCurrentScreen;
};

