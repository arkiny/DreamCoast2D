#pragma once
#include "uiInterface.h"
class uiInGameMenu :
	public uiInterface
{
public:
	uiInGameMenu();
	~uiInGameMenu();
	virtual void OnInit();
	virtual void Update(float);
	virtual void Render();

private:
	D2D1_RECT_F m_HUDRect;
	D2D1_RECT_F m_StatRect;
	D2D1_RECT_F m_InvenRect;
	D2D1_RECT_F m_MenuRect;
};

