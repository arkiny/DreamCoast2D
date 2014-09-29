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
	void OnInit(cD2DRenderer&);
	void Update(float);
	void Render(cD2DRenderer&);

	void setTileMap(wTileMap* in){ m_pTileMap = in; }
private:
	wTileMap* m_pTileMap;

	void drawMiniMap(cD2DRenderer&);
};

