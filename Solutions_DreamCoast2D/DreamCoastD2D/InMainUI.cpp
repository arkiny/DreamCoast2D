#include "stdafx.h"
#include "InMainUI.h"
#include "uiButton.h"
#include "VECTOR2D.h"
#include "coControl.h"
#include "sIScreen.h"
#include "sMainMenuScreen.h"

InMainUI::InMainUI()
{	
	//m_pInterface.push_back(new uiButton(135.0f, 530.0f, 0));
	//m_pInterface.push_back(new uiButton(135.0f, 345.0f, 1));

	uiButton* ptr = nullptr;
	ptr = new uiButton(135.0f, 345.0f, 1);
	ptr->setSelected(true);
	m_pInterface.push_back(ptr);
	ptr = nullptr;
	
	m_pInterface.push_back(new uiButton(135.0f, 390.0f, 2));
	m_pInterface.push_back(new uiButton(135.0f, 435.0f, 3));
	
	m_btnSelect = new uiButton(112.0f, 345.0f, 4);
}


InMainUI::~InMainUI()
{
	if (m_btnSelect != NULL){
		delete m_btnSelect;
	}
}

void InMainUI::Render(cD2DRenderer& renderer){
	for (uiInterface* x : m_pInterface){
		x->Render(renderer);
	}
	m_btnSelect->Render(renderer);
}

void InMainUI::Update(float delta){
	uiButton* ptr = nullptr;
	//m_fdelaytime += delta;

	for (uiInterface* x : m_pInterface){
		// 업데이트 먼저하고
		x->Update(delta);
		ptr = (uiButton*)x;

		// 키보드 이동으로 메뉴이동 시키려다가 실패..
		/*if (!m_bisMoved){
			if (!m_bNextSelect
				&& coControl::GetInstance().getKeyControlInfo()[VK_DOWN]){
				m_bNextSelect = true;
			}
			else if (m_bNextSelect){
				if (ptr->isSelected()){
					ptr->setSelected(false);
				}
				else {
					ptr->setSelected(true);
					m_bNextSelect = false;
					m_bisMoved = true;
				}
			}			
		}
		else {
			if (m_fdelaytime >= m_fKeydelay){
				m_bisMoved = false;
				m_fdelaytime = 0;
			}
			else if (!coControl::GetInstance().getKeyControlInfo()[VK_DOWN]) {
				m_bisMoved = false;
				m_fdelaytime = 0;
			}
			else {

			}
		}*/

		// 마우스 위치 확인하여 선택됬는지 안됬는지 확인
		// activate되었을 경우 메인스크린에서 해당변수를
		// 확인해서 update시에 실행되도록
		// down casting
		
		if (ptr->isSelected()){
			m_btnSelect->setPos(m_btnSelect->getPos()->x, ptr->getPos()->y);
			if (ptr->isActivated()){
				dynamic_cast<sMainMenuScreen*>(m_callbackScreen)
					->setActivate(ptr->getButtonType(), true);
			}
			else {
				dynamic_cast<sMainMenuScreen*>(m_callbackScreen)
					->setActivate(ptr->getButtonType(), false);
			}
		}
	}
	ptr = nullptr;
}

void InMainUI::OnInit(cD2DRenderer& renderer, sIScreen* in){
	for (uiInterface* x : m_pInterface){
		x->OnInit(renderer);
	}
	m_btnSelect->OnInit(renderer);
	m_callbackScreen = in;
}