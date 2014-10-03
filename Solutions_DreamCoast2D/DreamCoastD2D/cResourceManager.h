#pragma once
#include "cD2DRenderer.h"
#include "Singleton.h"

enum BUTTONID{SPACETOPLAY, NEWGAME, LOAD, CONFIG, BUTTONTYPEMAX};
enum UIID{STATBAR, BLUEBAR, REDBAR, MAP_L_BORDER, MAP_TAG, UI_ID_MAX};

class cResourceManager : public Singleton<cResourceManager>
{
public:
	cResourceManager();
	~cResourceManager();

	void load(cD2DRenderer&);
	void loadMainMenuResource(cD2DRenderer&);
	void exitMainMenu();
	void releaseGameResource();

	ID2D1Bitmap* getPlayerBitMap() { return m_Bitmap_Player; }
	ID2D1Bitmap* getTileMapBitMap() { return m_Bitmap_TileMap; }
	ID2D1Bitmap* getPoringBitMap() { return m_Bitmap_Poring; }
	ID2D1Bitmap* getBackGround() { return m_Bitmap_MainBG; }
	
	ID2D1Bitmap* getButton(int buttonID) { return m_Bitmap_Button[buttonID]; }
	D2D_POINT_2F getButtonSize(int buttonID) { return m_ButtonSize[buttonID]; }
	
	ID2D1Bitmap* getUIBitMap(int uiID) { return m_Bitmap_UI[uiID]; }
	D2D_POINT_2F getUISize(int uiID) { return m_UI_SIZE[uiID]; }

private:
	ID2D1Bitmap* m_Bitmap_Player;		// 플레이어(차후 클래스 number vector로 관리)
	ID2D1Bitmap* m_Bitmap_TileMap;		// 타일맵(차후 레벨 vector로 관리)
	ID2D1Bitmap* m_Bitmap_Poring;		// 몬스터 포링 주소(차후 몬스터 번호 vector로 관리)

	//
	ID2D1Bitmap* m_Bitmap_MainBG;
	ID2D1Bitmap* m_Bitmap_UI[UI_ID_MAX];
	::D2D_POINT_2F m_UI_SIZE[UI_ID_MAX];

	ID2D1Bitmap* m_Bitmap_Button[BUTTONTYPEMAX];
	::D2D_POINT_2F m_ButtonSize[BUTTONTYPEMAX];
};

