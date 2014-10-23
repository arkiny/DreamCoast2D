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

	// if keydown 's' save map as a binary file
	if (coControl::GetInstance().getKeyControlInfo()[0x53]){
		coControl::GetInstance().onKeyUp(0x53);
		uFileControl save = uFileControl(m_pWorld);
		save.SaveToFile(1);
		return;
	}

	if (::coControl::GetInstance().getKeyControlInfo()[0x30]){
		::coControl::GetInstance().onKeyUp(0x30);
		m_nHook = TILE_EMPTY;
	}
	if (::coControl::GetInstance().getKeyControlInfo()[0x31]){
		::coControl::GetInstance().onKeyUp(0x31);
		m_nHook = TILE_CANNOTMOVE;
	}
	if (::coControl::GetInstance().getKeyControlInfo()[0x32]){
		::coControl::GetInstance().onKeyUp(0x32);
		m_nHook = TILE_HIGH_GROUND;
	}
	if (::coControl::GetInstance().getKeyControlInfo()[0x33]){
		::coControl::GetInstance().onKeyUp(0x33);
		m_nHook = TILE_TREE;
	}
	if (::coControl::GetInstance().getKeyControlInfo()[0x34]){
		::coControl::GetInstance().onKeyUp(0x34);
		m_nHook = TILE_BUILDING;
		// 이동불가로 만들 타일 범위 설정 납작한 2번으로 다 설정해버림 됨
	}
	if (::coControl::GetInstance().getKeyControlInfo()[0x51]){
		::coControl::GetInstance().onKeyUp(0x51);
		// 이동불가로 만들 타일 범위 설정 납작한 2번으로 다 설정해버림 됨
		m_nHook = MOB_PORING;		
	}
	if (::coControl::GetInstance().getKeyControlInfo()[0x57]){
		::coControl::GetInstance().onKeyUp(0x57);
		// 이동불가로 만들 타일 범위 설정 납작한 2번으로 다 설정해버림 됨
		m_nHook = MOB_PORING_A;
	}

	if (::coControl::GetInstance().getKeyControlInfo()[VK_LBUTTON]){		
		::coControl::GetInstance().onKeyUp(VK_LBUTTON);
		VECTOR2D clickpoint(::coControl::GetInstance().getClickPosition().x, ::coControl::GetInstance().getClickPosition().y);
		float x = m_pWorld->getMap()->getCamera()->getX();
		float y = m_pWorld->getMap()->getCamera()->getY();
		clickpoint.x = clickpoint.x + x;
		clickpoint.y = clickpoint.y + y;

		VECTOR2D mousecoord = m_pWorld->getMap()
			->getTileCoordinates(clickpoint);
		if (m_nHook >= 0 && m_nHook <= 3){
			if (mousecoord.x >= 0.0f && mousecoord.y >= 0.0f &&
				mousecoord.x < m_pWorld->getMap()->getMapLimit().x&&
				mousecoord.y < m_pWorld->getMap()->getMapLimit().y){

				// 여기에 고른 타일이나 몬스터에 따라 추가하는 choose 명령어를 넣는다.
				m_pWorld->getMap()->setTile(mousecoord.x, mousecoord.y, m_nHook);
			}
		}
		else if (m_nHook == TILE_BUILDING){
			if (mousecoord.x >= 0.0f && mousecoord.y >= 0.0f &&
				mousecoord.x < m_pWorld->getMap()->getMapLimit().x&&
				mousecoord.y < m_pWorld->getMap()->getMapLimit().y){

				m_pWorld->getMap()->addMapObjectTotile(mousecoord.y, mousecoord.x);
				
				// 여기에 고른 타일이나 몬스터에 따라 추가하는 choose 명령어를 넣는다.
				m_pWorld->getMap()->setTile(mousecoord.x, mousecoord.y, 1);

				if (mousecoord.y - 1.0f >= 0){
					m_pWorld->getMap()->setTile(mousecoord.x, mousecoord.y - 1.0f, 1);
				}
				if (mousecoord.y - 2.0f >= 0){
					m_pWorld->getMap()->setTile(mousecoord.x, mousecoord.y - 2.0f, 1);
				}
				if (mousecoord.x - 1.0f >= 0){
					m_pWorld->getMap()->setTile(mousecoord.x - 1.0f, mousecoord.y, 1);
				}
				if (mousecoord.x - 1.0f >= 0 && mousecoord.y - 1.0f >= 0){
					m_pWorld->getMap()->setTile(mousecoord.x - 1.0f, mousecoord.y - 1.0f, 1);
				}
				if (mousecoord.x - 1.0f >= 0 && mousecoord.y - 2.0f >= 0){
					m_pWorld->getMap()->setTile(mousecoord.x - 1.0f, mousecoord.y - 2.0f, 1);
				}
				if (mousecoord.x - 2.0f >= 0){
					m_pWorld->getMap()->setTile(mousecoord.x - 2.0f, mousecoord.y, 1);
				}
				if (mousecoord.x - 2.0f >= 0 && mousecoord.y - 1.0f >= 0){
					m_pWorld->getMap()->setTile(mousecoord.x - 2.0f, mousecoord.y - 1.0f, 1);
				}
				if (mousecoord.x - 2.0f >= 0 && mousecoord.y - 2.0f >= 0){
					m_pWorld->getMap()->setTile(mousecoord.x - 2.0f, mousecoord.y - 2.0f, 1);
				}


				/*if (mousecoord.x + 1.0f <= m_pWorld->getMap()->getMapLimit().x && mousecoord.y <= m_pWorld->getMap()->getMapLimit().y){
					m_pWorld->getMap()->setTile(mousecoord.x + 1.0f, mousecoord.y , 1);
				}*/
				//if (mousecoord.x + 1.0f <= m_pWorld->getMap()->getMapLimit().x && mousecoord.y - 1.0f >= 0){
				//	// 차후 알맞은 타일로 교체
				//	m_pWorld->getMap()->setTile(mousecoord.x + 1.0f, mousecoord.y - 1.0f, 1);
				//}
				//if (mousecoord.x + 1.0f <= m_pWorld->getMap()->getMapLimit().x && mousecoord.y - 2.0f >= 0){
				//	// 차후 알맞은 타일료 교체
				//	m_pWorld->getMap()->setTile(mousecoord.x + 1.0f, mousecoord.y - 2.0f, 1);
				//}
				//if (mousecoord.x + 2.0f <= m_pWorld->getMap()->getMapLimit().x && mousecoord.y - 1.0f >= 0){
				//	// 차후 알맞은 타일로 교체
				//	m_pWorld->getMap()->setTile(mousecoord.x + 2.0f, mousecoord.y-1.0f, 1);
				//}
			}
		}
		else if (m_nHook == MOB_PORING){
			m_pWorld->getMap()->addMonsterTotile(mousecoord.y, mousecoord.x);
		}
		else if (m_nHook == MOB_PORING_A){
			m_pWorld->getMap()->addMonsterTotile(mousecoord.y, mousecoord.x, 1);
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