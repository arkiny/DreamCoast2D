#include "stdafx.h"
#include "uiInGameMenu.h"
#include "cResourceManager.h"
#include "VECTOR2D.h"
#include "coControl.h"

uiInGameMenu::uiInGameMenu()
{
	this->setPos(new VECTOR2D(722.0f, 743.0f));
}


uiInGameMenu::~uiInGameMenu()
{
}


void uiInGameMenu::OnInit(){
	m_HUDRect = {
		this->getPos()->x + 4.0f,
		this->getPos()->y + 4.0f,
		this->getPos()->x + 64.0f,
		this->getPos()->y + 25.0f };
	m_StatRect = {
		this->getPos()->x + 76.0f,
		this->getPos()->y + 4.0f,
		this->getPos()->x + 134.0f,
		this->getPos()->y + 25.0f
	};
	m_InvenRect = {
		this->getPos()->x + 147.0f,
		this->getPos()->y + 4.0f,
		this->getPos()->x + 206.0f,
		this->getPos()->y + 25.0f
	};
	m_MenuRect = {
		this->getPos()->x + 218.0f,
		this->getPos()->y + 4.0f,
		this->getPos()->x + 278.0f,
		this->getPos()->y + 25.0f
	};
}

void uiInGameMenu::Update(float delta){
	// 일정 부분을 클릭하면, 해당 키 activate
	// 이러면 되는군!
	POINTFLOAT mousepoint = ::coControl::GetInstance().getMousePosition();
	if (mousepoint.x >= m_HUDRect.left&&
		mousepoint.y >= m_HUDRect.top &&
		mousepoint.x <= m_HUDRect.right &&
		mousepoint.y <= m_HUDRect.bottom){
		if (::coControl::GetInstance().getKeyControlInfo()[VK_LBUTTON]){
			//
		}
	}

	if (mousepoint.x >= m_StatRect.left&&
		mousepoint.y >= m_StatRect.top &&
		mousepoint.x <= m_StatRect.right &&
		mousepoint.y <= m_StatRect.bottom){
		if (::coControl::GetInstance().getKeyControlInfo()[VK_LBUTTON]){
			::coControl::GetInstance().onKeyDown(0x43);
			coControl::GetInstance().onKeyUp(VK_LBUTTON);
		}
	}

	if (mousepoint.x >= m_InvenRect.left&&
		mousepoint.y >= m_InvenRect.top &&
		mousepoint.x <= m_InvenRect.right &&
		mousepoint.y <= m_InvenRect.bottom){
		if (::coControl::GetInstance().getKeyControlInfo()[VK_LBUTTON]){
			::coControl::GetInstance().onKeyDown(0x49);
			coControl::GetInstance().onKeyUp(VK_LBUTTON);
		}
	}

	if (mousepoint.x >= m_MenuRect.left&&
		mousepoint.y >= m_MenuRect.top &&
		mousepoint.x <= m_MenuRect.right &&
		mousepoint.y <= m_MenuRect.bottom){
		if (::coControl::GetInstance().getKeyControlInfo()[VK_LBUTTON]){
			::coControl::GetInstance().onKeyDown(VK_ESCAPE);
			coControl::GetInstance().onKeyUp(VK_LBUTTON);
		}
	}
}

void uiInGameMenu::Render(){
	if (::cResourceManager::GetInstance().getUIBitMap(UIID::UI_HUD_MENU) != nullptr){
		::D2D1_RECT_F dxArea
			= { this->getPos()->x,
			this->getPos()->y,
			this->getPos()->x + ::cResourceManager::GetInstance().getUISize(UIID::UI_HUD_MENU).x,
			this->getPos()->y + ::cResourceManager::GetInstance().getUISize(UIID::UI_HUD_MENU).y };
		::D2D1_RECT_F srcArea
			= { 0, 0,
			::cResourceManager::GetInstance().getUISize(UIID::UI_HUD_MENU).x,
			::cResourceManager::GetInstance().getUISize(UIID::UI_HUD_MENU).y };

		::cD2DRenderer::GetInstance().GetRenderTarget()
			->DrawBitmap(::cResourceManager::GetInstance().getUIBitMap(UIID::UI_HUD_MENU), dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}
}