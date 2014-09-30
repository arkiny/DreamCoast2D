#pragma once
#include "sIScreen.h"

class wWorld;
class InGameUI;

class sGameScreen : public sIScreen
{	
public:
	sGameScreen();
	sGameScreen(cGameManager*);
	~sGameScreen();
private:
	void Render(cD2DRenderer&);
	void Update(float deltaTime);
	void OnInit(cD2DRenderer&);
	void OnExit();

	void setWorld(wWorld* in){ m_pWorld = in; }
	wWorld* getWorld(){ return m_pWorld; }

private:
	wWorld* m_pWorld;	
	InGameUI* m_pGameUI;
	//차후 UI렌더가 될때, world가 렌더 된 이후, 그 위에 UI레이어를 뿌린다
};

