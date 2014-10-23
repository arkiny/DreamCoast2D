#pragma once
#include "cD2DRenderer.h"
#include "Singleton.h"
#include "cResourceID.h"

class cResourceManager : public Singleton<cResourceManager>
{
public:
	cResourceManager();
	~cResourceManager();

	void load();
	void loadMainMenuResource();
	void exitMainMenu();
	void releaseGameResource();

	ID2D1Bitmap* getPlayerBitMap() { return m_Bitmap_Player; }
	ID2D1Bitmap* getTileMapBitMap() { return m_Bitmap_TileMap; }
	ID2D1Bitmap* getPoringBitMap() { return m_Bitmap_Poring; }
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

private:
	ID2D1Bitmap* m_Bitmap_Player;		// �÷��̾�(���� Ŭ���� number vector�� ����)
	ID2D1Bitmap* m_Bitmap_TileMap;		// Ÿ�ϸ�(���� ���� vector�� ����)
	ID2D1Bitmap* m_Bitmap_Poring;		// ���� ���� �ּ�(���� ���� ��ȣ vector�� ����)

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
};

