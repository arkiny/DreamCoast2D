#pragma once
#include <d2d1.h>

class cD2DRenderer;
class VECTOR2D;
class uSprite;
class wTileMap;
class uCamera;

// up to first entering
enum DIRECTION{ LEFT, RIGHT, UP, DOWN, RIGHTDOWN, LEFTUP, LEFTDOWN, RIGHTUP };
enum OBJECTSTATE{ ONMOVE, ONATTACK, ONHIT, ONDEAD };

class mIObject
{
public:
	virtual ~mIObject();

	virtual void onInit(cD2DRenderer& renderer) = 0;
	virtual void onUpdate(float fdeltatime) = 0;

	// object�� �⺻������ �������� �Ұ��� ������ �ֱ� ������
	// ������ ������ �̷������ ���� ��ӹ޾� �������̵� �� �ʿ� ����
	// ���� ���� Ŭ�������� �ǽ� ����
	virtual void onRender(cD2DRenderer& renderer);
	virtual void onRender(cD2DRenderer& renderer, bool alpha);
	
	VECTOR2D* getDrawPos(){ return _drawVector; }
	VECTOR2D* getRealPos(){ return _realVector; }
	void setPos(float x, float y);
	void setTileMap(wTileMap* in);
	void setCam(uCamera* in){ m_Cam = in; }

protected:
	// �⺻������ ����������� ������ ���� ������
	// POINT�� �� ��� LONG ������ ��ȯ�� �Ͼ�� ������ �������꿡 ������ �����.
	VECTOR2D* _drawVector;			// �׸� ��ġ
	VECTOR2D* _realVector;			// ���� ��ġ

	// Communicate Pointer with control and tileMap
	wTileMap *m_pTileMap;
	uCamera *m_Cam;

	// Player�� �������� ������ �ִ� ����
	// ���� uSpriteŬ�������� �ű��� ���
	// �׷��� �Ǹ� ������ ���� ó����
	// ��κ� uSprite�� ó���ϰ� �ǹǷ�
	// playerŬ������ ������Ʈ ���� ��⿡
	// ���߰���
	uSprite* m_spriteAtlas;			// ��������Ʈ ����
	ID2D1Bitmap* m_ipD2DBitmap;		// ��������Ʈ ����

	float m_hp;
};

