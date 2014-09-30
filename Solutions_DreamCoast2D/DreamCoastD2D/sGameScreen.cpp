#include "stdafx.h"
#include "sGameScreen.h"
#include "cGameManager.h"
#include "wWorld.h"
#include "InGameUI.h"
#include "sGameOverScreen.h"

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
	m_pWorld->OnInit(renderer, sIScreen::getControl());

	m_pGameUI = new InGameUI((mIObject*)m_pWorld->getPlayer(), m_pWorld->getMap());
}

void sGameScreen::Render(cD2DRenderer& renderer){
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
	sGameScreen::~sGameScreen();
}