#pragma once
#include "movePacket.h"
#include "IGObject.h"
class uCamera;
class uSprite;
class niState;
class wTileMap;

class mNetworkObject
{
public:
	mNetworkObject();
	mNetworkObject(movePacket in);
	~mNetworkObject();

	void init();
	void render(uCamera* cam);
	void update(float delta);
	void setTileMapPointer(wTileMap* in){ m_pTileMap = in; }

	movePacket getCurrentPacket(){ return m_CurrentPacket; }
	void setCurrentPacket(movePacket in) { m_CurrentPacket = in; }

	float getDelta(){ return m_fDelta; }
	void setDelta(float in) { m_fDelta = in; }

	void changeState(niState* pnew);
	VECTOR2D vectorMove(float fdeltatime, DIRECTION dir);

	void setPacketPosition(float x, float y);
	uSprite* getSprite(){ return m_spriteAtlas; }

	void dmgToTile(float delta, float dmg);
	void setAttackAccumTime(float in){ m_attackaccumtime = in; }

private:
	float m_attackaccumtime = 0.0f;

	movePacket m_CurrentPacket;
	float m_fDelta = 0.0f;
	wTileMap *m_pTileMap;

	uSprite* m_spriteAtlas;			// ��������Ʈ ����
	niState* m_CurrentState;		// ���� ���� �ӽ�
	ID2D1Bitmap* m_ipD2DBitmap;		// ��������Ʈ �޸� �ּ�
};

