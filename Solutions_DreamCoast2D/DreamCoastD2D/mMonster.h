#pragma once
#include "mIObject.h"

class aiState;
class mPlayer;

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
	//
	void changeState(aiState* pnew);
	void onIdle();
	void onAttack();
	void onHit();
	void onDeath();
	//	

	float getdeltaTime(){ return m_fdeltatime; }

	void setDir(DIRECTION dir) { m_SeeDir = dir; }
	DIRECTION getDir() { return m_SeeDir; }
private:
	DIRECTION m_SeeDir; // 보고 있는 방향
	OBJECTSTATE m_State;
	
	aiState* m_pState;

	float m_fdeltatime = 0.0f;

	// 기본 스탯
	bool m_aggro = false;
};

