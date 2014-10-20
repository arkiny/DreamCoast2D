#pragma once
#include "sIScreen.h"

class wWorld;

class sEditScreen :
	public sIScreen
{
public:
	sEditScreen();
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
};

