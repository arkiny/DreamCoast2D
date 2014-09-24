#pragma once
#include "mIObject.h"

class aiState;
class mPlayer;
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
	
	// stat control
	void setHealth(float in); 
	float getdeltaTime(){ return m_fdeltatime; }
	void setDir(DIRECTION dir) { m_SeeDir = dir; }
	DIRECTION getDir() { return m_SeeDir; }
	void setDest(float x, float y);
	VECTOR2D* getDest(){ return m_dest; }

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

	void moveRandom();

	void moveToDest(float);

private:
	DIRECTION m_SeeDir; // 보고 있는 방향
	OBJECTSTATE m_State;
	VECTOR2D* m_dest;

	aiState* m_pState;

	float m_fdeltatime = 0.0f;
	float m_alpha = 1.0f;

	// 기본 스탯
	bool m_aggro = false;	
};

