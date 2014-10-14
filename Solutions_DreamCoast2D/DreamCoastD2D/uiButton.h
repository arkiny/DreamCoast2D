#pragma once
#include "uiInterface.h"

class VECTOR2D;

class uiButton :
	public uiInterface
{
public:
	uiButton();
	uiButton(float x, float y, int type);
	~uiButton();
public:
	void OnInit();
	void Update(float);
	void Render();
	void setSize(float width, float height){
		m_fWidth = width;
		m_fHeight = height;
	}
	float getWidth() { return m_fWidth; }
	float getHeight() { return m_fHeight; }
	bool isSelected() { return m_bSelected; }
	bool isActivated() { return m_bActionButton; }
	void setSelected(bool in){ m_bSelected = in; }
	void setActivated(bool in) { m_bActionButton = in; }
	int getButtonType(){ return m_nButtonType; }
private:
	float m_fWidth = 0.0f;
	float m_fHeight = 0.0f;
	int m_nButtonType = 0;
	bool m_bSelected = false;
	bool m_bActionButton = false;
	float m_fAccumtimeBreath = 0.0f;
	float m_alpha = 1.0f;
	float m_falphaAdd = 0.025f;
};

