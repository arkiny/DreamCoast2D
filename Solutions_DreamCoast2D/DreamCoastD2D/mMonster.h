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

	void setHealth(float in); 
	OBJECTSTATE getState() { return m_State; }
	void setState(OBJECTSTATE in) { m_State = in; }

		
private:
	DIRECTION m_SeeDir; // ���� �ִ� ����
	OBJECTSTATE m_State;
	
	aiState* m_pState;

	float m_fdeltatime = 0.0f;

	// �⺻ ����
	bool m_aggro = false;	
};

