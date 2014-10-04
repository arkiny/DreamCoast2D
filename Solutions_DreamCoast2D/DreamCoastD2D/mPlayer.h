#pragma once
#include "mIObject.h"

class uSprite;

// Statemachine을 이용하지 않은 채로 실행하는
// player object
// 차후 상황에 따라서 statemachine형으로 변화
class mPlayer : public mIObject
{
public:
	mPlayer();
	~mPlayer();
	void onInit(ID2D1Bitmap* resource);
	void onUpdate(float fdeltatime);
	void onRender(cD2DRenderer& renderer);
	void onRender(cD2DRenderer&, bool);
	
	// StatController
	void getHit(float dmg);

	// graphic control
	void setAlpha(float in){ m_alpha = in; }
	float getAlpha(){ return m_alpha; }

	// StateInitializer
	// void onIdle();

	bool isDeadComplete() { return m_deadcomp; }
	
private:
	// 키보드 입력에 따른 움직임
	// Helper methods -> 몬스터에게도 필요할경우 object로 이동
	void onMove(float deltaTime);
	void onAttack(float deltaTime);
	void onHit(float fdeltatime);
	void onDead(float);
	// skill 은 스킬 커맨드에 따라서 statemachine으로 처리?
	void onSkill(float);
	//VECTOR2D vectorMove(float fdeltatime, DIRECTION dir);

	DIRECTION m_SeeDir; // 보고 있는 방향
	OBJECTSTATE m_State;	

	// rendering alpha parameter control
	float m_alpha = 1.0f;
	
	// 공속 변수, 차후 아이템 추가, 캐릭터 추가시 동적 변화
	float m_attackSpeed = 2.0f;
	float m_attackaccumtime = 0.0f;

	// onhit delay time
	float m_onhitMaxtime = 0.5f;
	float m_onhitAccumtime = 0.0f;

	// fade out time
	float m_deadFadeOutTime = 0.0f;

	bool m_deadcomp = false;

	// 스킬 캐스팅 변수
	float m_castaccumtime = 0.0f;
};

