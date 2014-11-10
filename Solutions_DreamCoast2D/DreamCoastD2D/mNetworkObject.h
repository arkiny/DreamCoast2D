#pragma once
#include "movePacket.h"
#include "IGObject.h"
class uCamera;
class uSprite;
class niState;

class mNetworkObject
{
public:
	mNetworkObject();
	mNetworkObject(movePacket in);
	virtual ~mNetworkObject();

	virtual void init();
	virtual void render(uCamera* cam);
	virtual void update(float delta);

	virtual movePacket getCurrentPacket(){ return m_CurrentPacket; }
	virtual void setCurrentPacket(movePacket in) { m_CurrentPacket = in; }

	virtual float getDelta(){ return m_fDelta; }
	virtual void setDelta(float in) { m_fDelta = in; }

	virtual void changeState(niState* pnew);
	virtual VECTOR2D vectorMove(float fdeltatime, DIRECTION dir);

	virtual void setPacketPosition(float x, float y);
	virtual uSprite* getSprite(){ return m_spriteAtlas; }
private:
	
	movePacket m_CurrentPacket;
	float m_fDelta = 0.0f;

	uSprite* m_spriteAtlas;			// 스프라이트 정보
	niState* m_CurrentState;		// 현재 상태 머신
	ID2D1Bitmap* m_ipD2DBitmap;		// 스프라이트 메모리 주소
};

