#pragma once

#include <d2d1.h>

class VECTOR2D;

class uSprite
{
public:
	uSprite();
	uSprite(float x, float y, float width, float height);
	~uSprite();
	void pickSpriteAtlas(float x, float y, float width, float height);
	::D2D1_RECT_F getCoordinateFromPivot(VECTOR2D& pos);
	float getframeWidth(){ return m_frameWidth; }
	float getframeHeight(){ return m_frameHeight; }
	float getframeX(){ return m_frameX; }
	float getframeY(){ return m_frameY; }

private:
	float m_frameWidth;
	float m_frameHeight;
	float m_frameX;
	float m_frameY;
};

