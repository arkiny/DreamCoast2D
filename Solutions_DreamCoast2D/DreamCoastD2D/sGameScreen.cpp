#include "stdafx.h"
#include "sGameScreen.h"
#include "cGameManager.h"
#include "wWorld.h"
#include "InGameUI.h"
#include "sGameOverScreen.h"
#include "cResourceManager.h"

sGameScreen::sGameScreen(){
	m_pWorld = nullptr;
	m_pGameUI = nullptr;
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
}

void sGameScreen::OnInit(cD2DRenderer& renderer){
	m_pWorld = new wWorld();

	::cResourceManager::GetInstance().load(renderer);

	m_pWorld->OnInit(renderer);
	m_pGameUI = new InGameUI((mIObject*)m_pWorld->getPlayer(), m_pWorld->getMap());
}

void sGameScreen::Render(cD2DRenderer& renderer){
	// background
	RECT winRect;
	GetClientRect(renderer.GetHwnd(), &winRect);
	if (::cResourceManager::GetInstance().getBackGround()){
		::D2D1_RECT_F dxArea
			= { static_cast<float>(winRect.left), 
			static_cast<float>(winRect.top),
			static_cast<float>(winRect.right),
			static_cast<float>(winRect.bottom) };
		// todo 나중에 플레이어움직임에 반응하도록
		::D2D1_RECT_F srcArea
			= { 0, 0, 
			static_cast<float>(winRect.right),
			static_cast<float>(winRect.bottom) };

		renderer.GetRenderTarget()->DrawBitmap(::cResourceManager::GetInstance().getBackGround(),
			dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}

	m_pWorld->Render(renderer);
	// UI는 게임 화면보다 위에 깔리게
	m_pGameUI->Render(renderer);
}

void sGameScreen::Update(float deltaTime){
	if (m_pWorld->isGameOver()){
		m_pGameManager->changeScreen(new sGameOverScreen(m_pGameManager));
	}
	else {
		m_pWorld->Update(deltaTime);
	}
}

void sGameScreen::OnExit(){	
	::cResourceManager::GetInstance().releaseGameResource();
	this->~sGameScreen();
}