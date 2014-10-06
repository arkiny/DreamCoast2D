#pragma once
#include <d2d1.h>

class VECTOR2D;
class uSprite;
class wTileMap;
class uCamera;

// up to first entering
enum DIRECTION{ LEFT, RIGHT, UP, DOWN, RIGHTDOWN, LEFTUP, LEFTDOWN, RIGHTUP, NOMOVE };
enum OBJECTSTATE{ ONIDLE, ONMOVE, ONATTACK, ONHIT, ONDEAD, ONCASTING };

class mIObject
{
public:
	virtual ~mIObject();

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

	// Set point connection with other class
	void setTileMap(wTileMap* in);
	void setCam(uCamera* in){ m_Cam = in; }

	// health control
	float getHealth(){ return m_HP; }
	float getMAXHealth() { return m_MAXHP; }
	void setMAXHealth(float in) { m_MAXHP = in; }
	
	virtual void setHealth(float in){ m_HP = in; }	
	virtual void getHit(float dmg);

	//
	uSprite* getSprite() { return m_spriteAtlas; }
	wTileMap* getTileMap(){ return m_pTileMap; }
	void setBitMap(ID2D1Bitmap* input) { m_ipD2DBitmap = input; }

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

	VECTOR2D vectorMove(float fdeltatime, DIRECTION dir);
};

