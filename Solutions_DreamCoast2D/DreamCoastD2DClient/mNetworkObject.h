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
	~mNetworkObject();

	void init();
	void render(uCamera* cam);
	void update(float delta);

	movePacket getCurrentPacket(){ return m_CurrentPacket; }
	void setCurrentPacket(movePacket in) { m_CurrentPacket = in; }

	float getDelta(){ return m_fDelta; }
	void setDelta(float in) { m_fDelta = in; }

	void changeState(niState* pnew);
	VECTOR2D vectorMove(float fdeltatime, DIRECTION dir);

	void setPacketPosition(float x, float y);
	uSprite* getSprite(){ return m_spriteAtlas; }
private:
	
	movePacket m_CurrentPacket;
	float m_fDelta = 0.0f;

	uSprite* m_spriteAtlas;			// ��������Ʈ ����
	niState* m_CurrentState;		// ���� ���� �ӽ�
	ID2D1Bitmap* m_ipD2DBitmap;		// ��������Ʈ �޸� �ּ�
};

