#pragma once
#include "sIScreen.h"

class wWorld;
class iInScreenUI;

class sGameScreen : public sIScreen
{	
public:
	sGameScreen();
	sGameScreen(cGameManager*);
	~sGameScreen();

	void setWorldActivation(bool in){ m_bWorldActivated = in; }
	void setWorld(wWorld* in){ m_pWorld = in; }
	wWorld* getWorld(){ return m_pWorld; }

	void setActivate(int nextScreenID, bool in){
		m_bNextScreenBtn[nextScreenID] = in;
	}

	bool isScreenActivated(int screenNum){
		return m_bNextScreenBtn[screenNum];
	}

	bool isGameOver() const {
		return m_bisGameOver;
	}

private:
	void Render();
	void Update(float deltaTime);
	void OnInit();
	void OnExit();


private:
	wWorld* m_pWorld;	
	iInScreenUI* m_pGameUI;

	// game over시 출력될 UI
	iInScreenUI* m_pMenu;

	bool m_bWorldActivated = true;
	bool m_bNextScreenBtn[BUTTONID::BTN_BUTTONTYPEMAX];
	bool m_bisGameOver = false;

	float m_fKeydelay = 0.2f;
	float m_fdelaytime = 0.0f;
};

