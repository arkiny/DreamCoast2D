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
};

