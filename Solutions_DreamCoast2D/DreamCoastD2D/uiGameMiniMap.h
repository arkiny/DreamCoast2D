#pragma once
#include "uiInterface.h"
class wTileMap;

class uiGameMiniMap :
	public uiInterface
{
public:
	uiGameMiniMap();
	uiGameMiniMap(wTileMap*);
	~uiGameMiniMap();
public:
	void OnInit();
	void Update(float);
	void Render();

	void setTileMap(wTileMap* in){ m_pTileMap = in; }
private:
	wTileMap* m_pTileMap;

	void drawMiniMap();
};

