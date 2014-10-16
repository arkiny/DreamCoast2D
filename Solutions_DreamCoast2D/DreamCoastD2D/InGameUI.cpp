#include "stdafx.h"
#include "InGameUI.h"
#include "uiInterface.h"
#include "uiPlayerStatBar.h"
#include "uiGameMiniMap.h"
#include "uiMenu.h"
#include "uiBelt.h"
#include "uiInventory.h"
#include "uiStat.h"
#include "uiInGameMenu.h"
#include "coControl.h"

InGameUI::InGameUI()
{
}

InGameUI::InGameUI(ICharacter* player, wTileMap* tileMap){
	m_pInterface.push_back(new uiPlayerStatBar(player));
	m_pInterface.push_back(new uiGameMiniMap(tileMap));		
	m_pInterface.push_back(new uiBelt(player));	
	m_pInterface.push_back(new uiInGameMenu());

	m_pInterfaceCanMove.push_back(new uiStat(player));
	m_pInterfaceCanMove.push_back(new uiInventory(player, m_pInterface[2]));
}

InGameUI::~InGameUI()
{
}

void InGameUI::Render(){
	if (m_bGameUIActivate){
		for (uiInterface* x : m_pInterface){
			x->Render();
		}
		for (uiInterface* x : m_pInterfaceCanMove){
			x->Render();
		}		
	}
} 

void InGameUI::Update(float delta){
	if (m_bGameUIActivate){
		// 비트맵 이용시 컨트롤
		for (uiInterface* x : m_pInterface){
			x->Update(delta);
		}
		// 인터페이스 이동 업데이트는 여기서 관리, 해당 인터페이스의 영역을 누르면
		// 팝해서 제일 마지막 위치로 푸쉬
		
		int movingIndex = 999;
		POINTFLOAT mousepoint = ::coControl::GetInstance().getMousePosition();
		
		// 업데이트는 역순으로
		for (int i = m_pInterfaceCanMove.size() - 1; i >= 0; i--){
			uiInterface* x = m_pInterfaceCanMove[i];
			x->Update(delta);

			if (x->isActivated()){
				POINTFLOAT mousepoint = ::coControl::GetInstance().getMousePosition();
				if (x->isInsideMovingRect(mousepoint.x, mousepoint.y)){
					if (::coControl::GetInstance().getKeyControlInfo()[VK_LBUTTON] && x->isMoving() == false
						&& x->isInsideMovingRect(::coControl::GetInstance().getClickPosition().x, ::coControl::GetInstance().getClickPosition().y)){
						POINTFLOAT clickpoint = ::coControl::GetInstance().getClickPosition();
						x->saveOldPos(clickpoint.x, clickpoint.y);
						// setclicked
						x->setMoving(true);
					}
				}
				else
				{
					x->setSelected(false);
				}
			}

			if (x->isMoving()){	
				// setclicked is true
				// put the window to back
				movingIndex = i;
				break;
			}
			else{

			}
		}

		// resorting
		if (movingIndex != 999 && movingIndex != m_pInterfaceCanMove.size()-1){
			uiInterface* temp = m_pInterfaceCanMove[movingIndex];
			temp->setLast(true);
			m_pInterfaceCanMove.back()->setLast(false);
			m_pInterfaceCanMove.erase(m_pInterfaceCanMove.begin() + movingIndex);
			m_pInterfaceCanMove.shrink_to_fit();
			m_pInterfaceCanMove.push_back(temp);			
		}

		if (m_pInterfaceCanMove.back()->isMoving()){
			m_pInterfaceCanMove.back()->moveTo(mousepoint.x, mousepoint.y);
			if (!::coControl::GetInstance().getKeyControlInfo()[VK_LBUTTON]){
				m_pInterfaceCanMove.back()->moveTo(mousepoint.x, mousepoint.y);
				m_pInterfaceCanMove.back()->setMoving(false);
			}
		}
	}

	// 일정 키(~)를 누르면 화면 UI를 전체다 off
	if (::coControl::GetInstance().getKeyControlInfo()[0xC0]){
		::coControl::GetInstance().onKeyUp(0xC0);
		if (m_bGameUIActivate == true) {
			m_bGameUIActivate = false;
		}
		else {
			m_bGameUIActivate = true;
		}
	}
}

void InGameUI::OnInit(sIScreen* in){
	// 비트맵 이용시 이니셜 라이징	
	m_callbackScreen = in;
	m_pInterface.push_back(new uiMenu(5, m_callbackScreen));
	for (uiInterface* x : m_pInterfaceCanMove){
		x->OnInit();		
	}
	for (uiInterface* x : m_pInterface){
		x->OnInit();
	}
}

//bool InGameUI::RectCheck(uiInterface* input, POINTFLOAT& mousePoint){
//	return (mousePoint.x >= input->getMoveWindowRect().left &&
//		mousePoint.y >= input->getMoveWindowRect().top&&
//		mousePoint.x <= input->getMoveWindowRect().right &&
//		mousePoint.y <= input->getMoveWindowRect().bottom);
//}