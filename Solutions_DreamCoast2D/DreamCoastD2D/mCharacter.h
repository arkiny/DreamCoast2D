#pragma once
#include "IGObject.h"

// up to first entering
class mCharacter : public ICharacter
{
public:
	virtual ~mCharacter();

	virtual void onInit() = 0;
	virtual void onUpdate(float fdeltatime) = 0;

	// object�� �⺻������ �������� �Ұ��� ������ �ֱ� ������
	// ������ ������ �̷������ ���� ��ӹ޾� �������̵� �� �ʿ� ����
	// ���� ���� Ŭ�������� �ǽ� ����
	virtual void onRender();
	virtual void onRender(bool alpha);

	// position control
	VECTOR2D* getDrawPos(){ return _drawVector; }
	VECTOR2D* getRealPos(){ return _realVector; }
	void setRealPos(float x, float y);
	void setDrawPos(float x, float y);

	uSprite* getSprite() { return m_spriteAtlas; }
	wTileMap* getTileMap(){ return m_pTileMap; }
	void setBitMap(ID2D1Bitmap* input) { m_ipD2DBitmap = input; }

	// Set point connection with other class
	void setTileMap(wTileMap* in);
	void setCam(uCamera* in){ m_Cam = in; }

	// health control
	float getHealth(){ return m_HP; }
	float getMAXHealth() { return m_MAXHP; }
	void setMAXHealth(float in) { m_MAXHP = in; }

	virtual void setHealth(float in){ m_HP = in; }
	virtual void getHit(float dmg);

	void setMP(float in){ m_MP = in; }
	float getMP(){ return m_MP; }
	void setMaxMp(float in) { m_MAXMP = in;	}
	float getMaxMp(){ return m_MAXMP; }

	void setMoveSpeed(float in){ m_moveSpeed = in; }
	float getMoveSpeed() { return m_moveSpeed; }

	void setDefense(float in){ m_defense = in; }
	float getDefense(){ return m_defense; }
	//
	VECTOR2D vectorMove(float fdeltatime, DIRECTION dir);

protected:
	// �⺻������ ����������� ������ ���� ������
	// POINT�� �� ��� LONG ������ ��ȯ�� �Ͼ�� ������ �������꿡 ������ �����.
	VECTOR2D* _drawVector;			// �׸� ��ġ(pivot)
	VECTOR2D* _realVector;			// ���� ��ġ(position)

	// Communicate Pointer with control and tileMap
	wTileMap *m_pTileMap;
	uCamera *m_Cam;

	// object�� sprites�� ������ �ִ� ����
	// ���� uSpriteŬ�������� �ű��� ���
	// �׷��� �Ǹ� ������ ���� ó����
	// ��κ� uSprite�� ó���ϰ� �ǹǷ�
	// playerŬ������ ������Ʈ ���� ��⿡
	// ���߰���
	uSprite* m_spriteAtlas;			// ��������Ʈ ����
	ID2D1Bitmap* m_ipD2DBitmap;		// ��������Ʈ �޸� �ּ�

	// ü�� ����, ���� ������ �߰�, ĳ���� �߰��� ���� ��ȭ
	float m_MAXHP = 100.0f;
	float m_MAXMP = 100.0f;
	float m_HP = 100.0f;
	float m_MP = 100.0f;
	float m_moveSpeed = 100.0f;
	float m_defense = 0.0f;

	
};

