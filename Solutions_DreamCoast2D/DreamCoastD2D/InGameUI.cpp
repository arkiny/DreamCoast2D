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
		for (uiInterface* x : m_pInterfaceCanMove){
			x->Render();
		}
		for (uiInterface* x : m_pInterface){
			x->Render();
		}
	}
} 

void InGameUI::Update(float delta){
	if (m_bGameUIActivate){
		// ��Ʈ�� �̿�� ��Ʈ��
		for (uiInterface* x : m_pInterface){
			x->Update(delta);
		}
		// �������̽� �̵� ������Ʈ�� ���⼭ ����, �ش� �������̽��� ������ ������
		// ���ؼ� ���� ������ ��ġ�� Ǫ��
		
		int movingIndex = 999;
		POINTFLOAT mousepoint = ::coControl::GetInstance().getMousePosition();
		
		// ������Ʈ�� ��������
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

	// ���� Ű(~)�� ������ ȭ�� UI�� ��ü�� off
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
	// ��Ʈ�� �̿�� �̴ϼ� ����¡	
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