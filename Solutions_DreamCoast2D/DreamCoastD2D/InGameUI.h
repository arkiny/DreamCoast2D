#pragma once
#include <vector>
#include "iInScreenUI.h"
#include "IGObject.h"

class uiInterface;
class wTileMap;

// UI Screen has UI interface classes.
// Using as a layer of the game screen
// therefore, ui layer is not a screen 
// -> does not hierarchy screen class
class InGameUI : public iInScreenUI
{
public:
	InGameUI();
	InGameUI(ICharacter*, wTileMap*);
	~InGameUI();
	void Render();
	void Update(float);
	void OnInit(sIScreen*);
private:
	std::vector<uiInterface*> m_pInterfaceCanMove;
	bool m_bGameUIActivate = true;
	//bool RectCheck(uiInterface*, POINTFLOAT&);
};

