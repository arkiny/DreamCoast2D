#include "stdafx.h"
#include "sEditScreen.h"
#include "sGameScreen.h"
#include "wWorld.h"
#include "wTileMap.h"
#include "uCamera.h"
#include "cResourceManager.h"
#include "cGameManager.h"
#include "coControl.h"
#include "uFileControl.h"
#include "VECTOR2D.h"

sEditScreen::sEditScreen(cGameManager* cg)
{
	m_pWorld = nullptr;
	m_pGameManager = cg;
}


sEditScreen::~sEditScreen()
{
	if (m_pWorld != NULL){
		delete m_pWorld;
	}
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
	if (coControl::GetInstance().getKeyControlInfo()[VK_TAB]){
		coControl::GetInstance().onKeyUp(VK_TAB);
		sGameScreen* input = new sGameScreen(m_pGameManager);
		m_pGameManager->changeScreen(input);
		return;
	}
	if (coControl::GetInstance().getKeyControlInfo()[0x53]){
		coControl::GetInstance().onKeyUp(0x53);
		uFileControl save = uFileControl(m_pWorld);
		save.SaveToFile(1);
		return;
	}
	if (::coControl::GetInstance().getKeyControlInfo()[VK_LBUTTON]){
		VECTOR2D clickpoint(::coControl::GetInstance().getClickPosition().x, ::coControl::GetInstance().getClickPosition().y);
		float x = m_pWorld->getMap()->getCamera()->getX();
		float y = m_pWorld->getMap()->getCamera()->getY();
		clickpoint.x = clickpoint.x + x;
		clickpoint.y = clickpoint.y + y;

		VECTOR2D mousecoord = m_pWorld->getMap()
			->getTileCoordinates(clickpoint);

		if (mousecoord.x >= 0.0f && mousecoord.y >= 0.0f &&
			mousecoord.x < m_pWorld->getMap()->getMapLimit().x&&
			mousecoord.y < m_pWorld->getMap()->getMapLimit().y){

			// 여기에 고른 타일이나 몬스터에 따라 추가하는 choose 명령어를 넣는다.
			m_pWorld->getMap()->setTile(mousecoord.x, mousecoord.y, 3);
		}
	}
}

void sEditScreen::OnInit(){
	m_pWorld = new wWorld();
	//::cResourceManager::GetInstance().load();
	m_pWorld->OnInit(1);
}

void sEditScreen::OnExit(){	
	//::cResourceManager::GetInstance().releaseGameResource();
	this->~sEditScreen();
}