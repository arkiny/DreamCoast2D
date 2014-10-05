#include "stdafx.h"
#include "sGameScreen.h"
#include "cGameManager.h"
#include "wWorld.h"
#include "InGameUI.h"
#include "cResourceManager.h"
#include "coControl.h"
#include "sMainMenuScreen.h"

sGameScreen::sGameScreen(){
	m_pWorld = nullptr;
	m_pGameUI = nullptr;
	memset(m_bNextScreenBtn, false, sizeof(m_bNextScreenBtn));
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
	memset(m_bNextScreenBtn, false, sizeof(m_bNextScreenBtn));
}

void sGameScreen::OnInit(cD2DRenderer& renderer){
	m_pWorld = new wWorld();

	::cResourceManager::GetInstance().load(renderer);

	m_pWorld->OnInit(renderer);
	m_pGameUI = new InGameUI((mIObject*)m_pWorld->getPlayer(), m_pWorld->getMap());
	m_pGameUI->OnInit(renderer, this);
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
		// todo ���߿� �÷��̾�����ӿ� �����ϵ���
		::D2D1_RECT_F srcArea
			= { 0, 0, 
			::cResourceManager::GetInstance().getBackGroundSize().x,
			::cResourceManager::GetInstance().getBackGroundSize().y };

		renderer.GetRenderTarget()
			->DrawBitmap(::cResourceManager::GetInstance().getBackGround(),
			dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}

	m_pWorld->Render(renderer);
	// UI�� ���� ȭ�麸�� ���� �򸮰�
	m_pGameUI->Render(renderer);
}

void sGameScreen::Update(float deltaTime){

	if (m_bNextScreenBtn[BTN_MAINMENU]){
		sMainMenuScreen* input = new sMainMenuScreen(m_pGameManager);
		m_pGameManager->changeScreen(input);
		return;
	}
	else if (m_bNextScreenBtn[BTN_EXITGAME]){
		::PostQuitMessage(NULL);
		return;
	}
	else if (m_bNextScreenBtn[BTN_RESTART]){
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

}

void sGameScreen::OnExit(){	
	::cResourceManager::GetInstance().releaseGameResource();
	this->~sGameScreen();
}