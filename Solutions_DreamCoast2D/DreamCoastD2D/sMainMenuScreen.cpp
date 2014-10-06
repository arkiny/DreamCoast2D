#include "stdafx.h"
#include "sMainMenuScreen.h"
#include "coControl.h"
#include "cGameManager.h"
#include "sGameScreen.h"
#include "cD2DRenderer.h"
#include "cResourceManager.h"
#include "InMainUI.h"
#include "sResourceLoad.h"
#include "cSoundManager.h"

sMainMenuScreen::sMainMenuScreen()
{
	memset(m_bNextScreenBtn, false, sizeof(m_bNextScreenBtn));
//	m_pUI = nullptr;
}


sMainMenuScreen::~sMainMenuScreen()
{
	if (m_pUI != NULL){
		delete m_pUI;
	}
}

sMainMenuScreen::sMainMenuScreen(cGameManager* cg){
	memset(m_bNextScreenBtn, false, sizeof(m_bNextScreenBtn));
	m_pGameManager = cg;
}

void sMainMenuScreen::OnInit(){
	::cResourceManager::GetInstance().loadMainMenuResource();
	m_pUI = new InMainUI();
	m_pUI->OnInit(this);
	::cSoundManager::GetInstance().executeBGM();
}

void sMainMenuScreen::Update(float delta){
	// ������ ��ũ�� ��ư�� ������ ���
	if (m_bNextScreenBtn[BTN_NEWGAME]){
		sResourceLoad* input = new sResourceLoad(m_pGameManager, BTN_NEWGAME);
		m_pGameManager->changeScreen(input);
	}
	else {
		m_pUI->Update(delta);
	}
}

void sMainMenuScreen::Render(){
	// background rendering
	if (::cResourceManager::GetInstance().getBackGround()!= nullptr){
		::RECT winRect;
		GetClientRect(::cD2DRenderer::GetInstance().GetHwnd(), &winRect);
		
		::D2D1_RECT_F dxArea
			= { static_cast<float>(winRect.left), 
			static_cast<float>(winRect.top),
			static_cast<float>(winRect.right),
			static_cast<float>(winRect.bottom) };
		::D2D1_RECT_F srcArea
			= { 0,
			0,
			::cResourceManager::GetInstance().getBackGroundSize().x,
			::cResourceManager::GetInstance().getBackGroundSize().y };

		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawBitmap(::cResourceManager::GetInstance().getBackGround(), dxArea, 1.0,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);	
	}

	m_pUI->Render();

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
	//	renderer.GetBlackBrush());
}

void sMainMenuScreen::OnExit(){
	// main menu resource release
	::cResourceManager::GetInstance().exitMainMenu();
	::cSoundManager::GetInstance().stopBGM();
}