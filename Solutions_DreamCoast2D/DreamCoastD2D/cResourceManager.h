#pragma once
#include "cD2DRenderer.h"
#include "Singleton.h"

enum BUTTONID{SPACETOPLAY, NEWGAME, LOAD, CONFIG};

class cResourceManager : public Singleton<cResourceManager>
{
public:
	cResourceManager();
	~cResourceManager();

	void load(cD2DRenderer&);
	void loadMainMenuResource(cD2DRenderer&);

	ID2D1Bitmap* getPlayerBitMap() { return m_Bitmap_Player; }
	ID2D1Bitmap* getTileMapBitMap() { return m_Bitmap_TileMap; }
	ID2D1Bitmap* getPoringBitMap() { return m_Bitmap_Poring; }
	ID2D1Bitmap* getBackGround() { return m_Bitmap_MainBG; }
	ID2D1Bitmap* getButton(int buttonID) { return m_Bitmap_Button[buttonID]; }

private:
	ID2D1Bitmap* m_Bitmap_Player;		// 플레이어(차후 클래스 number vector로 관리)
	ID2D1Bitmap* m_Bitmap_TileMap;		// 타일맵(차후 레벨 vector로 관리)
	ID2D1Bitmap* m_Bitmap_Poring;		// 몬스터 포링 주소(차후 몬스터 번호 vector로 관리)

	//
	ID2D1Bitmap* m_Bitmap_MainBG;
	ID2D1Bitmap* m_Bitmap_Button[20];
};

