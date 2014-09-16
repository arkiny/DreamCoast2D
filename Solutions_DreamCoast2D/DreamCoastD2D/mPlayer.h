#pragma once
#include "mIObject.h"

class coControl;
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

	void pickSpriteAtlas(float x, float y, float width, float height);

	ID2D1Bitmap* m_ipD2DBitmap;
	float m_accumtime;
	int m_nframe;

	// 기본 노가다용
	float m_frameWidth;
	float m_frameHeight;
	float m_frameX;
	float m_frameY;

	// pivot 연구용
	RECT playerCollisionBox;
	float m_playerPivotX;
	float m_playerPivotY;

	coControl *m_pControl;
};

