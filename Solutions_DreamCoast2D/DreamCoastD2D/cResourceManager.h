#pragma once
#include "cD2DRenderer.h"
#include "Singleton.h"

enum BUTTONID{SPACETOPLAY, NEWGAME, LOAD, CONFIG, NOTHING, BUTTONTYPEMAX};

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

private:
	ID2D1Bitmap* m_Bitmap_Player;		// �÷��̾�(���� Ŭ���� number vector�� ����)
	ID2D1Bitmap* m_Bitmap_TileMap;		// Ÿ�ϸ�(���� ���� vector�� ����)
	ID2D1Bitmap* m_Bitmap_Poring;		// ���� ���� �ּ�(���� ���� ��ȣ vector�� ����)

	//
	ID2D1Bitmap* m_Bitmap_MainBG;
	ID2D1Bitmap* m_Bitmap_Button[20];
	::D2D_POINT_2F m_ButtonSize[20];
};
