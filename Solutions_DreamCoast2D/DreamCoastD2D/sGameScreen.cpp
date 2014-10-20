#include "stdafx.h"
#include "sGameScreen.h"
#include "cGameManager.h"
#include "wWorld.h"
#include "InGameUI.h"
#include "cResourceManager.h"
#include "coControl.h"
#include "sMainMenuScreen.h"
#include "sResourceLoad.h"
#include "cSoundManager.h"
#include "mGFX.h"



sGameScreen::sGameScreen(){
	m_pWorld = nullptr;
	m_pGameUI = nullptr;
	memset(m_bNextScreenBtn, false, BTN_BUTTONTYPEMAX);
}

sGameScreen::~sGameScreen(){	
	if (m_pWorld != NULL){
		delete m_pWorld;
	}
	if (m_pGameUI != NULL){
		delete m_pGameUI;
	}
	
}

sGameScreen::sGameScreen(cGameManager* cg){
	m_pGameManager = cg;
	memset(m_bNextScreenBtn, false, BTN_BUTTONTYPEMAX);
}

void sGameScreen::OnInit(){
	m_pWorld = new wWorld();

	::cResourceManager::GetInstance().load();

	m_pWorld->OnInit();
	m_pGameUI = new InGameUI((ICharacter*)m_pWorld->getPlayer(), m_pWorld->getMap());
	m_pGameUI->OnInit(this);

	::cSoundManager::GetInstance().executeBGMinGame();
}

void sGameScreen::Render(){
	// background
	RECT winRect;
	GetClientRect(::cD2DRenderer::GetInstance().GetHwnd(), &winRect);
	if (::cResourceManager::GetInstance().getBackGround()){
		::D2D1_RECT_F dxArea
			= { static_cast<float>(winRect.left), 
			static_cast<float>(winRect.top),
			static_cast<float>(winRect.right),
			static_cast<float>(winRect.bottom) };
		// todo 나중에 플레이어움직임에 반응하도록
		::D2D1_RECT_F srcArea
			= { 0, 0, 
			::cResourceManager::GetInstance().getBackGroundSize().x,
			::cResourceManager::GetInstance().getBackGroundSize().y };

		::cD2DRenderer::GetInstance().GetRenderTarget()
			->DrawBitmap(::cResourceManager::GetInstance().getBackGround(),
			dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}

	m_pWorld->Render();
	// UI는 게임 화면보다 위에 깔리게
	mGFX::GetInstance().render();
	m_pGameUI->Render();
	
}

void sGameScreen::Update(float deltaTime){

	if (m_bNextScreenBtn[BTN_MAINMENU]){
		sResourceLoad* input = new sResourceLoad(m_pGameManager, BTN_MAINMENU);
		m_pGameManager->changeScreen(input);
		return;
	}
	else if (m_bNextScreenBtn[BTN_EXITGAME]){
		::PostQuitMessage(NULL);
		return;
	}
	else if (m_bNextScreenBtn[BTN_RESTART]){
		// 이미지 재로딩 할 필요 없으므로.
		sGameScreen* input = new sGameScreen(m_pGameManager);
		m_pGameManager->changeScreen(input);
		return;
	}

	if (m_pWorld->isGameOver()){
		m_bisGameOver = true;
		/*m_pGameManager->changeScreen(new sGameOverScreen(m_pGameManager));
		return;*/
		m_pGameUI->Update(deltaTime);
	}
	else {
		if (m_bWorldActivated){
			m_pWorld->Update(deltaTime);
		}
		m_pGameUI->Update(deltaTime);
	}

	if (coControl::GetInstance().getKeyControlInfo()[0x50]){
		if (m_fdelaytime >= m_fKeydelay){
			if (m_bWorldActivated == false){
				m_bWorldActivated = true;
			}
			else{
				m_bWorldActivated = false;
			}
		}
		m_fdelaytime -= deltaTime;
		if (m_fdelaytime <= 0){
			m_fdelaytime = m_fKeydelay;
		}
	}
	mGFX::GetInstance().update(deltaTime);
}

void sGameScreen::OnExit(){	
	::cResourceManager::GetInstance().releaseGameResource();
	::cSoundManager::GetInstance().stopBGM();
	this->~sGameScreen();
}