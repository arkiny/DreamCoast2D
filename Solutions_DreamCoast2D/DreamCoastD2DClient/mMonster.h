#pragma once
#include "mCharacter.h"

enum MONSTERTYPE{MON_PASSIVE, MON_ACTIVE, MON_BOSS, MON_TYPE_MAX};

class aiState;
class VECTOR2D;

class mMonster :
	public mCharacter, public IMonster
{
public:
	mMonster();
	mMonster(float, float);
	~mMonster();
	//
	void onInit();
	void onUpdate(float fdeltatime);
	void onRender();
	
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
	void onCasting();

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

	int getMonsterType(){ return m_nMonsterType; }
	void setMonsterType(int in);

	float getSkillCooltime(){ return m_skillCooltime; }
	float getSkillAccumtime() { return m_skillAccumtime; }
	void setSkillAccumtime(float in) { m_skillAccumtime = in; }

private:
	DIRECTION m_SeeDir; // 보고 있는 방향
	OBJECTSTATE m_State;
	
	VECTOR2D* m_dest; // 목적지
	aiState* m_pState;	// statemachine

	// 몬스터 타입, 지금은 스프라이트도 이것에 따라서 조정되지만,
	// 차후 필요에 따라서 몬스터 아이디에 따라서 DB에서 뽑아오는 걸로 변경
	int m_nMonsterType = 0;

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

	// skill cooltime은 차후 스킬 DB에 따라서 유동화
	const float m_skillCooltime = 10.0f;
	float m_skillAccumtime = 0.0f;
};

