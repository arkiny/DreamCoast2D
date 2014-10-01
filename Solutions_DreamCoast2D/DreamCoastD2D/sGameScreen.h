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
private:
	void Render(cD2DRenderer&);
	void Update(float deltaTime);
	void OnInit(cD2DRenderer&);
	void OnExit();

	void setWorld(wWorld* in){ m_pWorld = in; }
	wWorld* getWorld(){ return m_pWorld; }

private:
	wWorld* m_pWorld;	
	iInScreenUI* m_pGameUI;
	//���� UI������ �ɶ�, world�� ���� �� ����, �� ���� UI���̾ �Ѹ���
};

