#pragma once
#include "cD2DRenderer.h"
#include "Singleton.h"


class cResourceManager : public Singleton<cResourceManager>
{
public:
	cResourceManager();
	~cResourceManager();

	void load(cD2DRenderer&);
	ID2D1Bitmap* getPlayerBitMap() { return m_Bitmap_Player; }
	ID2D1Bitmap* getTileMapBitMap() { return m_Bitmap_TileMap; }
	ID2D1Bitmap* getPoringBitMap() { return m_Bitmap_Poring; }

private:
	ID2D1Bitmap* m_Bitmap_Player;		// �÷��̾�
	ID2D1Bitmap* m_Bitmap_TileMap;		// Ÿ�ϸ�
	ID2D1Bitmap* m_Bitmap_Poring;		// ���� ���� �ּ�	
};

