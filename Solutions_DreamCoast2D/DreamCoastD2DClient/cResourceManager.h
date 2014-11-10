#pragma once
#include "cD2DRenderer.h"
#include "Singleton.h"
#include "cResourceID.h"
#include <vector>

struct SpriteAnimationInfo{
	DWORD typ;
	DWORD direction;
	float x;
	float y;
	float width;
	float height;
	float offsetX;
	float offsetY;
	DWORD maxFrame;
};

class cResourceManager : public Singleton<cResourceManager>
{
public:
	cResourceManager();
	~cResourceManager();

	void load();
	void loadMainMenuResource();
	void loadChatWindow();

	void exitMainMenu();
	void releaseGameResource();

	void loadFilePath(const char* szFileName);
	void loadMobSpritePath(const char* szFileName);
	void loadNormalSpritePath(const char* szFileName);

	void loadSpritePlayerData(const char* szFileName, int id);
	void loadSpriteMonsterData(const char* szFileName, int id);

	SpriteAnimationInfo* getPlayerSpriteInfo(int type, int direction);
	SpriteAnimationInfo* getMonsterSpriteInfo(int mobtype,  int action, int direction);
	SpriteAnimationInfo* getMapSpriteInfo(int tiletype, int type);
	SpriteAnimationInfo* getEffectSpriteInfo(int type);

	ID2D1Bitmap* getPlayerBitMap() { return m_Bitmap_Player; }
	ID2D1Bitmap* getTileMapBitMap() { return m_Bitmap_TileMap; }
	ID2D1Bitmap* getMobBitMap(int mobID) { return m_Bitmap_MoB[mobID]; }
	ID2D1Bitmap* getBackGround() { return m_Bitmap_MainBG; }
	D2D_POINT_2F getBackGroundSize() { return m_MainBG_Size; }

	ID2D1Bitmap* getButton(int buttonID) { return m_Bitmap_Button[buttonID]; }
	D2D_POINT_2F getButtonSize(int buttonID) { return m_ButtonSize[buttonID]; }
	
	ID2D1Bitmap* getUIBitMap(int uiID) { return m_Bitmap_UI[uiID]; }
	D2D_POINT_2F getUISize(int uiID) { return m_UI_SIZE[uiID]; }

	ID2D1Bitmap* getConsumeItemBitMap(int itemID) { return m_Bitmap_Item_Consume[itemID]; }
	D2D_POINT_2F getConsumeItemUISize(int itemID) { return m_Size_Item_Consume[itemID]; }

	ID2D1Bitmap* getGEffectBitMap(int EffectID) { return m_Bitmap_Effect[EffectID]; }
	D2D_POINT_2F getGEffectSize(int EffectID) { return m_Size_Effect[EffectID]; }

	ID2D1Bitmap* getMapObjectBitMap(int ObjectID) { return m_Bitmap_Effect[ObjectID]; }
	D2D_POINT_2F getMapObjectSize(int ObjectID) { return m_Size_Effect[ObjectID]; }

	ID2D1Bitmap* getChatWindowBitMap() { return m_Bitmap_ChatWindow; }
	D2D_POINT_2F getChatWindowSize() { return m_ChatWindow_Size; }

private:
	ID2D1Bitmap* m_Bitmap_Player;		// 플레이어(차후 클래스 number vector로 관리)
	ID2D1Bitmap* m_Bitmap_TileMap;		// 타일맵(차후 레벨 vector로 관리)
	ID2D1Bitmap* m_Bitmap_MoB[MOB_ID_MAX];		// 몬스터 포링 주소(차후 몬스터 번호 vector로 관리)

	//
	ID2D1Bitmap* m_Bitmap_ChatWindow;
	D2D_POINT_2F m_ChatWindow_Size;
	
	//
	ID2D1Bitmap* m_Bitmap_MainBG;
	::D2D_POINT_2F m_MainBG_Size;

	ID2D1Bitmap* m_Bitmap_MapObject[MAP_OBJECT_MAX];
	::D2D_POINT_2F m_MapObject_Size[MAP_OBJECT_MAX];

	ID2D1Bitmap* m_Bitmap_UI[UI_ID_MAX];
	::D2D_POINT_2F m_UI_SIZE[UI_ID_MAX];

	ID2D1Bitmap* m_Bitmap_Button[BTN_BUTTONTYPEMAX];
	::D2D_POINT_2F m_ButtonSize[BTN_BUTTONTYPEMAX];

	ID2D1Bitmap* m_Bitmap_Item_Consume[ITEM_CONSUME_MAX];
	::D2D_POINT_2F m_Size_Item_Consume[ITEM_CONSUME_MAX];

	ID2D1Bitmap* m_Bitmap_Effect[GEFFECT_ID_MAX];
	::D2D_POINT_2F m_Size_Effect[GEFFECT_ID_MAX];

	std::vector<TCHAR*> m_vecFilepath;
	std::vector<char*> m_mobSpriteFilePath;
	std::vector<char*> m_vecNormalSpriteFilePath;

	std::vector<POINTFLOAT*> m_vecImageSize;

	std::vector<SpriteAnimationInfo*> m_vecSpriteInfo[SPR_ID_MAX];
	std::vector<SpriteAnimationInfo*> m_vecMobSpriteInfo[SPR_MOB_ID_MAX];
};

