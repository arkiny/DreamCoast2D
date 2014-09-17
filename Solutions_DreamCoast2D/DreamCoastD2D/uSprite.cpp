#include "stdafx.h"
#include "uSprite.h"
#include "VECTOR2D.h"
//#include <d2d1.h>



uSprite::uSprite()
{
	m_frameWidth = 0.0f;
	m_frameHeight = 0.0f;
	m_frameX = 0.0f;
	m_frameY = 0.0f;
}


uSprite::~uSprite()
{
}

uSprite::uSprite(float x, float y, float width, float height){
	m_frameWidth = width;
	m_frameHeight = height;
	m_frameX = x;
	m_frameY = y;
}

void uSprite::pickSpriteAtlas(float x, float y, float width, float height){
	m_frameWidth = width;
	m_frameHeight = height;
	m_frameX = x;
	m_frameY = y;
}

::D2D1_RECT_F uSprite::getCoordinateFromPivot(VECTOR2D& pos){
	::D2D1_RECT_F ret
		= ::D2D1::RectF(
		pos.x - (m_frameWidth / 2.0f),
		pos.y - (m_frameHeight),
		(pos.x - (m_frameWidth / 2.0f)) + m_frameWidth,
		(pos.y - (m_frameHeight)) + m_frameHeight);
	return ret;
}