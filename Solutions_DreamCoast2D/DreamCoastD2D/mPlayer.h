#pragma once
#include "mIObject.h"

class coControl;
class uSprite;


class mPlayer : public mIObject
{
public:
	mPlayer();
	~mPlayer();
	void onInit(cD2DRenderer& renderer);
	void onUpdate(float fdeltatime);
	void onRender(cD2DRenderer& renderer);

	// set Communication Pointer
	void setKeyControl(coControl* in);	
	
private:
	// 키보드 입력에 따른 움직임
	// Helper methods -> 몬스터에게도 필요할경우 object로 이동
	void onMove(float deltaTime);
	void onAttack(float deltaTime);
	VECTOR2D vectorMove(float fdeltatime, DIRECTION dir);

	DIRECTION m_SeeDir; // 보고 있는 방향
	OBJECTSTATE m_State;	

	// Communicate Pointer with control and tileMap
	coControl *m_pControl;		
	
	// 공속 변수, 차후 아이템 추가, 캐릭터 추가시 동적 변화
	float m_attackSpeed = 2.0f;
	float m_attackaccumtime = 0.0f;
};

