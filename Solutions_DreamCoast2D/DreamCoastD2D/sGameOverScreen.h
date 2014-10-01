#pragma once
#include "sIScreen.h"

class cResourceManager;
//todo: üũ����Ʈ���� ����, ���θ޴��� ���ư��� �߰�
class sGameOverScreen :
	public sIScreen
{
public:
	sGameOverScreen();
	sGameOverScreen(cGameManager* cg);
	~sGameOverScreen();

	void Render(cD2DRenderer&);
	void Update(float);
	void OnInit(cD2DRenderer&, cResourceManager*);
	void OnExit();

private:
	float m_accumtime = 0.0f;
};

