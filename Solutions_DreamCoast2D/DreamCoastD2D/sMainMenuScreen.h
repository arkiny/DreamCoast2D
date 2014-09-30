#pragma once
#include "sIScreen.h"

//class InMainMenuUI;

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
	//InMainMenuUI* m_pUI;
};

