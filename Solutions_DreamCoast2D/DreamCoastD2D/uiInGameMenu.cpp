#include "stdafx.h"
#include "uiInGameMenu.h"
#include "cResourceManager.h"
#include "VECTOR2D.h"


uiInGameMenu::uiInGameMenu()
{
	this->setPos(new VECTOR2D(722.0f, 743.0f));
}


uiInGameMenu::~uiInGameMenu()
{
}


void uiInGameMenu::OnInit(){

}

void uiInGameMenu::Update(float delta){
	// 일정 부분을 클릭하면, 해당 키 activate
	// 이러면 되는군!
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