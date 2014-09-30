#pragma once
#include "cD2DRenderer.h"

class cResourceManager
{
public:
	cResourceManager();
	~cResourceManager();

	void load(cD2DRenderer&);
	ID2D1Bitmap* getPlayerBitMap() { return m_Bitmap_Player; }
	ID2D1Bitmap* getTileMapBitMap() { return m_Bitmap_TileMap; }
	ID2D1Bitmap* getPoringBitMap() { return m_Bitmap_Poring; }

private:
	ID2D1Bitmap* m_Bitmap_Player;		// 플레이어
	ID2D1Bitmap* m_Bitmap_TileMap;		// 타일맵
	ID2D1Bitmap* m_Bitmap_Poring;		// 몬스터 포링 주소	
};

