#pragma once
#include "sIScreen.h"

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
	void OnInit(cD2DRenderer&);
	void OnExit();

private:
	float m_accumtime = 0.0f;
};

