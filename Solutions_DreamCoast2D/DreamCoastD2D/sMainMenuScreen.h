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

	void OnInit(cD2DRenderer&);
	void Update(float);
	void Render(cD2DRenderer&);
	void OnExit();

private:
	iInScreenUI* m_pUI;
};

