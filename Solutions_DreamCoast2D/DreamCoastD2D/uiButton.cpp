#include "stdafx.h"
#include "uiButton.h"
#include "VECTOR2D.h"
#include "cResourceManager.h"
#include "coControl.h"

uiButton::uiButton()
{
	this->setPos(new VECTOR2D(0.0f, 0.0f));
}

uiButton::uiButton(float x, float y, int type)
{
	this->setPos(new VECTOR2D(x, y));
	m_nButtonType = type;
}

uiButton::~uiButton()
{
}

void uiButton::OnInit(cD2DRenderer& renderer){
	m_fWidth = ::cResourceManager::GetInstance().getButtonSize(m_nButtonType).x;
	m_fHeight = ::cResourceManager::GetInstance().getButtonSize(m_nButtonType).y;
}

void uiButton::Update(float delta){
	m_fAccumtimeBreath += delta;
	//if (m_fAccumtimeBreath >= 0.0125f){
	/*if (m_bSelected){
		m_alpha -= m_falphaAdd;
	}*/
		//m_fAccumtimeBreath = 0.0f;
	//}
	//if (m_alpha >= 1.0f){
	//	m_falphaAdd = -1 * m_falphaAdd;
	//}	
	//else if (m_alpha <= 0.5f){
	//	m_falphaAdd = -1 * m_falphaAdd;
	//}
	POINTFLOAT mousepoint = ::coControl::GetInstance().getMousePosition();
	if (mousepoint.x >= this->getPos()->x &&
		mousepoint.y >= this->getPos()->y &&
		mousepoint.x <= (this->getPos()->x + this->getWidth()) &&
		mousepoint.y <= (this->getPos()->y + this->getHeight())){
		this->setSelected(true);
		if (::coControl::GetInstance().getKeyControlInfo()[VK_LBUTTON]){
			this->setActivated(true);
		}
		else {
			this->setActivated(false);
		}
	}
	else
	{
		this->setSelected(false);
	}
}

void uiButton::Render(cD2DRenderer& renderer){
	if (::cResourceManager::GetInstance().getButton(m_nButtonType) != nullptr){		
		::D2D1_RECT_F dxArea
			= { this->getPos()->x, this->getPos()->y, this->getPos()->x + m_fWidth, this->getPos()->y + m_fHeight };
		::D2D1_RECT_F srcArea
			= { 0, 0, m_fWidth, m_fHeight };

		renderer.GetRenderTarget()->DrawBitmap(::cResourceManager::GetInstance().getButton(m_nButtonType), dxArea, m_alpha,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}
}