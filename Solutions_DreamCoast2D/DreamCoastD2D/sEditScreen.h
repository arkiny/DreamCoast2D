#pragma once
#include "sIScreen.h"

class wWorld;

enum MOUSE_HOOKING_ID{
	TILE_EMPTY, TILE_CANNOTMOVE, TILE_HIGH_GROUND, TILE_TREE, TILE_BUILDING, MOB_PORING, MOB_PORING_A, RESET_TILE, BUTTON_MAX};

class sEditScreen :
	public sIScreen
{
public:
	sEditScreen(cGameManager*);
	~sEditScreen();
	
	// 해당 스크린에서 p누르면 업데이트 멈추게
	void setWorldActivation(bool in){ m_bWorldActivated = in; }

	void setWorld(wWorld* in);
	wWorld* getWorld(){ return m_pWorld; }

private:
	void Render();
	void Update(float deltaTime);
	void OnInit();
	void OnExit();


private:
	wWorld* m_pWorld;
	
	// 차후 맵툴용 UI 추가
	//iInScreenUI* m_pGameUI;
	// game over시 출력될 UI
	// iInScreenUI* m_pMenu;
	//bool m_bNextScreenBtn[BUTTONID::BTN_BUTTONTYPEMAX];

	bool m_bWorldActivated = true;
	bool m_bisGameOver = false;

	float m_fKeydelay = 0.2f;
	float m_fdelaytime = 0.0f;

	int m_nHook = 0;
};

