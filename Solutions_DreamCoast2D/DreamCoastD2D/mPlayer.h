#pragma once
#include "mIObject.h"

class coControl;
class uSprite;

enum OBJECTSTATE{Idle, Move, Attack, GetHitted};

class mPlayer : public mIObject
{
public:
	mPlayer();
	~mPlayer();
	void onInit(cD2DRenderer& renderer);
	void onUpdate(float fdeltatime);
	void onRender(cD2DRenderer& renderer);

	void setKeyControl(coControl* in);

private:
	
	// Sprite Atlas Ŭ������ ���߿� �и�(?)
	//float m_frameWidth;
	//float m_frameHeight;
	//float m_frameX;
	//float m_frameY;
	//void pickSpriteAtlas(float x, float y, float width, float height);

	uSprite* m_spriteAtlas;

	// ���� ���� Sprite Atlas�� �μ��� �޾Ƽ� �Ǻ�ȭ�� ��ǥ�� ����
	//D2D1_RECT_F getCoordinateFromPivot(VECTOR2D& pos);

	// Ű���� �Է¿� ���� ������
	void onMove(float deltaTime);

	ID2D1Bitmap* m_ipD2DBitmap;
	float m_accumtime;
	int m_nframe;	

	// pivot ������
	RECT playerCollisionBox;
	float m_playerPivotX;
	float m_playerPivotY;

	coControl *m_pControl;
};

