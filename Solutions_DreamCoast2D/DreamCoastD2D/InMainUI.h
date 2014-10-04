#pragma once
#include "iInScreenUI.h"

class uiButton;
class sIScreen;

class InMainUI : public iInScreenUI
{
public:
	InMainUI();
	~InMainUI();

public:
	void Render(cD2DRenderer&);
	void Update(float);
	void OnInit(cD2DRenderer&, sIScreen*);

private:
	uiButton* m_btnSelect;
	bool m_bNextSelect;
	//const float m_fKeydelay = 0.1f;
	//float m_fdelaytime = 0.0f;
	//bool m_bisMoved = false;
};

