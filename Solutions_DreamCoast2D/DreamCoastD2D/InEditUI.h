#pragma once
#include "iInScreenUI.h"
class InEditUI :
	public iInScreenUI
{
public:
	InEditUI();
	~InEditUI();

	virtual void Render();
	virtual void Update(float);
	virtual void OnInit(sIScreen*);
};

