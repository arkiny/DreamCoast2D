#pragma once
#include "mIObject.h"

class coControl;
class uSprite;
class wTileMap;

// up to first entering
enum DIRECTION{LEFT, RIGHT, UP, DOWN, RIGHTDOWN, LEFTUP, LEFTDOWN, RIGHTUP};
enum OBJECTSTATE{ONMOVE, ONATTACK, ONHIT};

class mPlayer : public mIObject
{
public:
	mPlayer();
	~mPlayer();
	void onInit(cD2DRenderer& renderer);
	void onUpdate(float fdeltatime);
	//void onRender(cD2DRenderer& renderer);

	void setKeyControl(coControl* in);
	//
	void setTileMap(wTileMap* in);

private:
	DIRECTION m_SeeDir; // ���� �ִ� ����
	OBJECTSTATE m_State;	
	coControl *m_pControl;
	//
	wTileMap *m_pTileMap;

	// Ű���� �Է¿� ���� ������
	void onMove(float deltaTime);
	void onAttack(float deltaTime);
	VECTOR2D vectorMove(float fdeltatime, DIRECTION dir);

	// ���� ����
	float m_attackSpeed = 2.0f;
};

