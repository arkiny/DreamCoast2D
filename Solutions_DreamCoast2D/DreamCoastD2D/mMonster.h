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
	void onIdle(float);
	void onAttack(float);
	void onHit(float);
	void onDeath(float);
	//	

	float getdeltaTime(){ return m_fdeltatime; }
private:
	DIRECTION m_SeeDir; // ���� �ִ� ����
	OBJECTSTATE m_State;
	
	aiState* m_pState;
	float m_fdeltatime = 0.0f;

	// �⺻ ����
	float m_health = 100.0f;
	bool m_aggro = false;
};

