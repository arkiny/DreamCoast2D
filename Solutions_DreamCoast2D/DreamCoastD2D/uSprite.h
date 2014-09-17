#pragma once

#include <d2d1.h>

#define FRAMERATE 0.125f

class VECTOR2D;

class uSprite
{
public:
	uSprite();
	uSprite(float x, float y, float width, float height, int maxFrame);
	~uSprite();
	void pickSpriteAtlas(float x, float y, float width, float height, int maxFrame);

	//
	::D2D1_RECT_F getCoordinateFromPivot(VECTOR2D& pos);
	::D2D1_RECT_F getSrcFrameFromSprite();

	// frame animation.. onUpdate?
	void nextFrame(float fdeltatime);

	// getter
	float getframeWidth(){ return m_frameWidth; }
	float getframeHeight(){ return m_frameHeight; }
	float getframeX(){ return m_frameX; }
	float getframeY(){ return m_frameY; }
	int getCurrentFrame(){ return m_currentFrame; }
	void setCurrentFrame(int frame){ m_currentFrame = frame; }

private:
	float m_frameWidth;
	float m_frameHeight;
	float m_frameX;
	float m_frameY;

	int m_nmaxFrame;
	int m_currentFrame;
	float m_accumtime;
};

