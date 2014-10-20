#include "stdafx.h"
#include "sEditScreen.h"
#include "wWorld.h"
#include "cResourceManager.h"


sEditScreen::sEditScreen()
{
	m_pWorld = nullptr;
}


sEditScreen::~sEditScreen()
{
	/*if (m_pWorld != NULL){
		delete m_pWorld;
	}*/
}

void sEditScreen::setWorld(wWorld* in){
	if (m_pWorld != NULL){
		delete m_pWorld;
	}
	m_pWorld = in;
}

void sEditScreen::Render(){
	m_pWorld->Render();
}

void sEditScreen::Update(float deltaTime){
	m_pWorld->Update(deltaTime);
}

void sEditScreen::OnInit(){
	// 새로운 메모리를 만들어서 생성한다.
	::cResourceManager::GetInstance().load();
	//m_pWorld->OnInit();	
}

void sEditScreen::OnExit(){	
	::cResourceManager::GetInstance().releaseGameResource();
	this->~sEditScreen();
}