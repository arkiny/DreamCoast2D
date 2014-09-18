#pragma once
#include "cD2DRenderer.h"
#include "cIGameMgr.h"
//class cD2DRenderer;
//class mPlayer;

class mPlayer;
class coControl;
class mTileMap;

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
	// 차후 매니저에서 asset관리하는 것 추가할수 있으면 좋겠음
	// assets
	/*ID2D1Bitmap* m_ipD2DBitmapBG;
	ID2D1Bitmap* m_ipD2DBitmap;
	ID2D1Bitmap* m_ipD2DBitmapFlip;*/

	mPlayer* m_player;
	mTileMap* m_map;
	coControl* m_pControl;

	//float x;
	//float y;
	//float m_fAngle;
	//float m_fAlpha;

	//float m_fframe;
	//int m_nframe;
};

