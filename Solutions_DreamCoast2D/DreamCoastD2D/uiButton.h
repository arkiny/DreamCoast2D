#pragma once
#include "uiInterface.h"

class VECTOR2D;

class uiButton :
	public uiInterface
{
public:
	uiButton();
	virtual ~uiButton();
public:
	virtual void OnInit(cD2DRenderer&) = 0;
	virtual void Update(float) = 0;
	virtual void Render(cD2DRenderer&) = 0;
	void setSize(float width, float height){
		m_nWidth = width;
		m_nHeight = height;
	}
	float getWidth() { return m_nWidth; }
	float getHeight() { return m_nHeight; }
private:
	float m_nWidth;
	float m_nHeight;
};

