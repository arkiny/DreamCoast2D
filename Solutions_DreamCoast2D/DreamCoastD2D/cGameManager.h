#pragma once
#include "cD2DRenderer.h"
#include "cIGameMgr.h"

class cD2DRenderer;
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
	// ���� �Ŵ������� asset�����ϴ� �� �߰��Ҽ� ������ ������
	// assets
	ID2D1Bitmap* m_ipD2DBitmapBG;
	ID2D1Bitmap* m_ipD2DBitmap;
	ID2D1Bitmap* m_ipD2DBitmapFlip;
	
	float x;
	float y;
	float m_fAngle;
	float m_fAlpha;
};

