#pragma once
#include "mIObject.h"

class aiState;
class VECTOR2D;

class mMonster :
	public mIObject
{
public:
	mMonster();
	mMonster(float, float);
	~mMonster();
	//
	void onInit(cD2DRenderer& renderer);
	void onUpdate(float fdeltatime);
	void onRender(cD2DRenderer& renderer);
	
	// state control
	OBJECTSTATE getState() { return m_State; }
	void setState(OBJECTSTATE in) { m_State = in; }
	
	// state machine control
	void changeState(aiState* pnew);

	// graphic control
	void setAlpha(float in){ m_alpha = in; }
	float getAlpha(){ return m_alpha; }

	// Sprite initializing
	void onIdle();
	void onAttack();
	void onHit();
	void onDeath();
	void onMove();

	// move control
	void moveRandom();
	void moveToDest(float deltatime);

	// stat control(getter setter)
	void getHit(float in);

	float getdeltaTime(){ return m_fdeltatime; }
	void setDir(DIRECTION dir) { m_SeeDir = dir; }
	DIRECTION getDir() { return m_SeeDir; }
	void setDest(float x, float y);
	void setDestinTile(float x, float y);
	VECTOR2D* getDest(){ return m_dest; }
	float getMaxAggroLevel(){ return m_fMaxAggroLevel; }
	void setMaxAggroLevel(float in){ m_fMaxAggroLevel = in; }
	float getCurrentAggroLevel(){ return m_fcurAggroLevel; }
	void setCurrentAggroLevel(float in) { m_fcurAggroLevel = in; }
	float getVisionRange(){ return m_visionRange; }
	float getAttackRange(){ return m_attackRange; }
	float getSight(){ return m_visionRange; }
	float getAttackPower() { return m_attackPower; }

private:
	DIRECTION m_SeeDir; // 보고 있는 방향
	OBJECTSTATE m_State;
	
	VECTOR2D* m_dest; // 목적지
	aiState* m_pState;	// statemachine

	// deltatime deliverer
	float m_fdeltatime = 0.0f;

	// rendering alphablend
	float m_alpha = 1.0f;

	// 기본 스탯
	float m_fMaxAggroLevel = 100.0f;
	float m_fcurAggroLevel = 0.0f;
	
	float m_visionRange = 3.0f; // 시야 : 주변 3타일 기본 세팅, 차후 몹마다 다르게 설정
	float m_attackRange = 0.0f; // 공격사거리 : 포링의 기본사거리는 딱붙어 공격

	float m_attackPower = 100.0f;
};

