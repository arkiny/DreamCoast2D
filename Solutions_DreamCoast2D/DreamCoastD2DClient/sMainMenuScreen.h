#pragma once
#include "sIScreen.h"

//class InMainMenuUI;
class iInScreenUI;

class sMainMenuScreen :
	public sIScreen
{
public:
	sMainMenuScreen();
	~sMainMenuScreen();
	sMainMenuScreen(cGameManager* cg);

	void OnInit();
	void Update(float);
	void Render();
	void OnExit();

	void setActivate(int nextScreenID, bool in){
		m_bNextScreenBtn[nextScreenID] = in;
	}

	bool isScreenActivated(int screenNum){
		return m_bNextScreenBtn[screenNum];
	}

private:
	iInScreenUI* m_pUI;
	bool m_bNextScreenBtn[BUTTONID::BTN_BUTTONTYPEMAX];
};

