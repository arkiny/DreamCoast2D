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
	
	const float m_fKeydelay = 0.2f;
	float m_fdelaytime = m_fKeydelay;
	
	bool m_bExecute = false;
	int m_nSelectedMenu = 0;
};

