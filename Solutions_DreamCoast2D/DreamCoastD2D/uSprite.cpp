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

	m_nmaxFrame = 0;
	m_currentFrame = 0;
	m_accumtime = 0.0f;

	m_offsetX = 0.0f;
	m_offsetY = 0.0f;
}

uSprite::~uSprite()
{
}

uSprite::uSprite(float x, float y, float width, float height, int maxFrame){
	m_frameWidth = width;
	m_frameHeight = height;
	m_frameX = x;
	m_frameY = y;
	m_nmaxFrame = maxFrame;
	m_currentFrame = 0;
	m_accumtime = 0.0f;
}

void uSprite::pickSpriteAtlas(float x, float y, float width, float height, int maxFrame){
	m_frameWidth = width;
	m_frameHeight = height;
	m_frameX = x;
	m_frameY = y;
	m_nmaxFrame = maxFrame;
	//m_currentFrame = 0;
	//m_accumtime = 0.0f;
}

void uSprite::pickSpriteAtlas(float x, float y, float width, float height, float offsetX, float offsetY, int maxFrame){
	m_frameWidth = width;
	m_frameHeight = height;
	m_frameX = x;
	m_frameY = y;
	m_nmaxFrame = maxFrame;
	m_offsetX = offsetX;
	m_offsetY = offsetY;
	//m_currentFrame = 0;
	//m_accumtime = 0.0f;
}

::D2D1_RECT_F uSprite::getCoordinateFromPivot(VECTOR2D& pos){
	::D2D1_RECT_F ret
		= ::D2D1::RectF(
		pos.x - (m_frameWidth / 2.0f) + m_offsetX,
		pos.y - (m_frameHeight) + m_offsetY,
		(pos.x - (m_frameWidth / 2.0f)) + m_frameWidth + m_offsetX,
		(pos.y - (m_frameHeight)) + m_frameHeight + m_offsetY);
	return ret;
}

::D2D1_RECT_F uSprite::getCoordinateFromPivotCenter(VECTOR2D& pos){
	::D2D1_RECT_F ret
		= ::D2D1::RectF(
		pos.x - (m_frameWidth / 2.0f),
		pos.y - (m_frameHeight / 2.0f),
		(pos.x - (m_frameWidth / 2.0f)) + m_frameWidth,
		(pos.y - (m_frameHeight / 2.0f)) + m_frameHeight);
	return ret;
}

::D2D1_RECT_F uSprite::getSrcFrameFromSprite(){
	float pickframeX = m_currentFrame * m_frameWidth;
	::D2D1_RECT_F srcArea
		= ::D2D1::RectF(
		m_frameX + pickframeX,
		m_frameY,
		m_frameX + pickframeX + m_frameWidth,
		m_frameY + m_frameHeight);
	return srcArea;
}

void uSprite::nextFrame(float fdeltatime){
	m_accumtime += fdeltatime;
	if (m_accumtime > FRAMERATE){
		m_currentFrame++;
		m_accumtime = 0.0f;
	}
	if (m_currentFrame > m_nmaxFrame){
		m_currentFrame = 0;
	}
}