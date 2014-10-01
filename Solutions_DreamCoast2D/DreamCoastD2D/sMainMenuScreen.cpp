#include "stdafx.h"
#include "sMainMenuScreen.h"
#include "coControl.h"
#include "cGameManager.h"
#include "sGameScreen.h"
#include "cD2DRenderer.h"
#include "cResourceManager.h"
#include "InMainUI.h"


sMainMenuScreen::sMainMenuScreen()
{
//	m_pUI = nullptr;
}


sMainMenuScreen::~sMainMenuScreen()
{
	if (m_pUI != NULL){
		delete m_pUI;
	}
}

sMainMenuScreen::sMainMenuScreen(cGameManager* cg){
	m_pGameManager = cg;
}

void sMainMenuScreen::OnInit(cD2DRenderer& renderer){
	::cResourceManager::GetInstance().loadMainMenuResource(renderer);
	m_pUI = new InMainUI();
	m_pUI->OnInit(renderer);
}

void sMainMenuScreen::Update(float delta){
	// 일단 스페이스 치면 넘어가는 걸로
	if (::coControl::GetInstance().getKeyControlInfo()[VK_SPACE]){
		sGameScreen* input = new sGameScreen(m_pGameManager);
		m_pGameManager->changeScreen(input);
	}
	else {
		m_pUI->Update(delta);
	}
}

void sMainMenuScreen::Render(cD2DRenderer& renderer){
	// background rendering
	if (::cResourceManager::GetInstance().getBackGround()!= nullptr){
		::RECT winRect;
		GetClientRect(renderer.GetHwnd(), &winRect);
		
		::D2D1_RECT_F dxArea
			= { static_cast<float>(winRect.left), 
			static_cast<float>(winRect.top),
			static_cast<float>(winRect.right),
			static_cast<float>(winRect.bottom) };
		::D2D1_RECT_F srcArea
			= { static_cast<float>(winRect.left),
			static_cast<float>(winRect.top),
			static_cast<float>(winRect.right),
			static_cast<float>(winRect.bottom) };

		renderer.GetRenderTarget()->DrawBitmap(::cResourceManager::GetInstance().getBackGround(), dxArea, 1.0,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);	
	}

	m_pUI->Render(renderer);

	//wchar_t* wszText2_ = L"Press Space to Start This Game";
	//UINT32 cTextLength2_ = (UINT32)wcslen(wszText2_);


	//D2D1_RECT_F layoutRect = D2D1::RectF(
	//	514.0,
	//	384.0,
	//	614.0,
	//	484.0
	//	);

	//renderer.GetRenderTarget()->DrawTextW(
	//	wszText2_,
	//	cTextLength2_,
	//	renderer.GetTextFormat(),
	//	layoutRect,
	//	renderer.GetBrush());
}

void sMainMenuScreen::OnExit(){
	// main menu resource release
	::cResourceManager::GetInstance().exitMainMenu();
}