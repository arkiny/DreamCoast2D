#pragma once
#include "sIScreen.h"

//todo: 체크포인트부터 시작, 메인메뉴로 돌아가기 추가
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
private:
	float m_accumtime = 0.0f;
};

