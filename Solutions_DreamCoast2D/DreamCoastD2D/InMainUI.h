#pragma once
#include "iInScreenUI.h"

class InMainUI : public iInScreenUI
{
public:
	InMainUI();
	~InMainUI();

public:
	void Render(cD2DRenderer&);
	void Update(float);
	void OnInit(cD2DRenderer&);
};

