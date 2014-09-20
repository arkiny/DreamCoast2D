#pragma once
#include "cD2DRenderer.h"
#include "cIGameMgr.h"
//class cD2DRenderer;
//class mPlayer;

//class mPlayer;
class coControl;
class wWorld;
//class wTileMap;

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
private:
	coControl* m_pControl;
	
	//일단 게임월드를 바로 넣어놨지만
	//차후 아래 포인터에는 각 스크린(메뉴스크린, 게임 스크린)이 들어가게 됩니다.
	wWorld* m_pWorld;
};

