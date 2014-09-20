#pragma once
#include "mIObject.h"

class coControl;
class uSprite;

// up to first entering
enum DIRECTION{LEFT, RIGHT, UP, DOWN, RIGHTDOWN, LEFTUP, LEFTDOWN, RIGHTUP};
enum OBJECTSTATE{ONMOVE, ONATTACK, ONHIT};

class mPlayer : public mIObject
{
public:
	mPlayer();
	~mPlayer();
	void onInit(cD2DRenderer& renderer);
	void onUpdate(float fdeltatime);
	//void onRender(cD2DRenderer& renderer);

	void setKeyControl(coControl* in);

private:
	DIRECTION m_SeeDir; // 보고 있는 방향
	OBJECTSTATE m_State;	
	coControl *m_pControl;

	// 키보드 입력에 따른 움직임
	void onMove(float deltaTime);
	void onAttack(float deltaTime);
	VECTOR2D vectorMove(float fdeltatime, DIRECTION dir);

	// 공속 변수
	float m_attackSpeed = 2.0f;
};

