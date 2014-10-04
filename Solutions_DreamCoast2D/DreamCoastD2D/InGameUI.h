#pragma once
#include <vector>
#include "iInScreenUI.h"

class uiInterface;
class cD2DRenderer;
class mIObject;
class wTileMap;

// UI Screen has UI interface classes.
// Using as a layer of the game screen
// therefore, ui layer is not a screen 
// -> does not hierarchy screen class
class InGameUI : public iInScreenUI
{
public:
	InGameUI();
	InGameUI(mIObject*, wTileMap*);
	~InGameUI();
	void Render(cD2DRenderer&);
	void Update(float);
	void OnInit(cD2DRenderer&, sIScreen*);

};

