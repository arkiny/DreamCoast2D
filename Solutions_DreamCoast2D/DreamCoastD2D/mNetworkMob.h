#pragma once
#include "movePacket.h"
#include "IGObject.h"

class uCamera;
class uSprite;
class niMobState;

class mNetworkMob
{
public:
	mNetworkMob();
	mNetworkMob(movePacket in);
	~mNetworkMob();

	void init();
	void render(uCamera* cam);
	void update(float delta);

	movePacket getCurrentPacket(){ return m_CurrentPacket; }
	void setCurrentPacket(movePacket in) { m_CurrentPacket = in; }

	float getDelta(){ return m_fDelta; }
	void setDelta(float in) { m_fDelta = in; }

	void changeState(niMobState* pnew);
	VECTOR2D vectorMove(float fdeltatime, DIRECTION dir);

	void setPacketPosition(float x, float y);
	uSprite* getSprite(){ return m_spriteAtlas; }


	// Sprite initializing
	void onIdle();
	void onAttack();
	void onHit();
	void onDeath();
	void onMove();
	void onCasting();
	void moveToDest(float deltaTime);
private:
	movePacket m_CurrentPacket;
	float m_fDelta = 0.0f;

	uSprite* m_spriteAtlas;			// 스프라이트 정보
	niMobState* m_CurrentState;		// 현재 상태 머신
};

