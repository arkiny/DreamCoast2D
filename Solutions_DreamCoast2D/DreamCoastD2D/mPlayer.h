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
	
	// Sprite Atlas 클래스로 나중에 분리(?)
	//float m_frameWidth;
	//float m_frameHeight;
	//float m_frameX;
	//float m_frameY;
	//void pickSpriteAtlas(float x, float y, float width, float height);

	uSprite* m_spriteAtlas;

	// 차후 위의 Sprite Atlas를 인수로 받아서 피봇화한 좌표를 리턴
	//D2D1_RECT_F getCoordinateFromPivot(VECTOR2D& pos);

	// 키보드 입력에 따른 움직임
	void onMove(float deltaTime);

	ID2D1Bitmap* m_ipD2DBitmap;
	float m_accumtime;
	int m_nframe;	

	// pivot 연구용
	RECT playerCollisionBox;
	float m_playerPivotX;
	float m_playerPivotY;

	coControl *m_pControl;
};

