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
		// ��Ʈ�� �̿�� ��Ʈ��
		for (uiInterface* x : m_pInterface){
			x->Update(delta);
		}
		// �������̽� �̵� ������Ʈ�� ���⼭ ����, �ش� �������̽��� ������ ������
		// ���ؼ� ���� ������ ��ġ�� Ǫ��
		int i = 0;
		int movingIndex = 999;
		for (uiInterface* x : m_pInterfaceCanMove){
			x->Update(delta);
			if (x->isActivated()){
				if (x->isMoving()){
					movingIndex = i;
					POINTFLOAT mousepoint = ::coControl::GetInstance().getMousePosition();
					x->moveTo(mousepoint.x, mousepoint.y);
					if (!::coControl::GetInstance().getKeyControlInfo()[VK_LBUTTON]){
						x->moveTo(mousepoint.x, mousepoint.y);
						x->setMoving(false);
					}
				}
			}
			i++;
		}
		// resorting
		if (movingIndex != 999){
			uiInterface* temp = m_pInterfaceCanMove[movingIndex];
			m_pInterfaceCanMove.erase(m_pInterfaceCanMove.begin() + movingIndex);
			m_pInterfaceCanMove.shrink_to_fit();
			m_pInterfaceCanMove.push_back(temp);
		}
	}
	// ���� Ű�� ������ ȭ�� UI�� ��ü�� off
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
	for (uiInterface* x : m_pInterface){
		x->OnInit();
	}

	for (uiInterface* x : m_pInterfaceCanMove){
		x->OnInit();		
	}
}