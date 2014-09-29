#include "stdafx.h"
#include "sGameScreen.h"
#include "wWorld.h"

sGameScreen::sGameScreen(){
	m_pWorld = nullptr;
}

sGameScreen::~sGameScreen(){
	if (m_pWorld != NULL){
		delete m_pWorld;
	}
}

void sGameScreen::OnInit(cD2DRenderer& renderer){
	m_pWorld = new wWorld();
	m_pWorld->OnInit(renderer, sIScreen::getControl());
}

void sGameScreen::Render(cD2DRenderer& renderer){
	m_pWorld->Render(renderer);
}

void sGameScreen::Update(float deltaTime){
	m_pWorld->Update(deltaTime);
}

