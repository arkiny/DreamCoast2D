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

	// player sprite처리를 담당하는 class
	// 차후 object위로 승격할지 고민할것
	
	// Player의 움직임을 가지고 있는 빗맵
	// 차후 uSprite클래스내로 옮길지 고민
	// 그렇게 되면 렌더에 관한 처리는
	// 대부분 uSprite가 처리하게 되므로
	// player클래스는 업데이트 관련 모듈에
	// 집중가능
	
	
	
	coControl *m_pControl;

	// 키보드 입력에 따른 움직임
	void onMove(float deltaTime);
	void onAttack(float deltaTime);
	VECTOR2D vectorMove(float fdeltatime, DIRECTION dir);

	// 공속 변수
	float m_attackSpeed = 2.0f;
};

