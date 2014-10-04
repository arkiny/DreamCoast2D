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

	for (unsigned int i = 0; i < m_pInterface.size(); i++){
		m_pInterface[i]->Update(delta);

		ptr = (uiButton*)m_pInterface[i];

		if (ptr->isSelected()){			
			m_nSelectedMenu = i;
			if (ptr->isActivated()){
				dynamic_cast<sMainMenuScreen*>(m_callbackScreen)
					->setActivate(ptr->getButtonType(), true);
			} 
		}
	}

	// keyboard execute
	if (coControl::GetInstance().getKeyControlInfo()[VK_RETURN] ||
		coControl::GetInstance().getKeyControlInfo()[VK_SPACE] ||
		coControl::GetInstance().getKeyControlInfo()[0x5A]){
		ptr = (uiButton*)m_pInterface[m_nSelectedMenu];
		dynamic_cast<sMainMenuScreen*>(m_callbackScreen)
			->setActivate(ptr->getButtonType(), true);
	}
	
	// keyboard move
	if (coControl::GetInstance().getKeyControlInfo()[VK_DOWN]){		
		if (m_fdelaytime >= m_fKeydelay){
			m_nSelectedMenu++;
			if (m_nSelectedMenu >= static_cast<int>(m_pInterface.size())){
				m_nSelectedMenu = 0;
			}
		}
		m_fdelaytime -= delta;
		if (m_fdelaytime <= 0){
			m_fdelaytime = m_fKeydelay;
		}
	}
	else if (coControl::GetInstance().getKeyControlInfo()[VK_UP]){
		if (m_fdelaytime >= m_fKeydelay){
			m_nSelectedMenu--;
			if (m_nSelectedMenu < 0 ){
				m_nSelectedMenu = m_pInterface.size()-1;
			}
		}
		m_fdelaytime -= delta;
		if (m_fdelaytime <= 0){
			m_fdelaytime = m_fKeydelay;
		}
	}
	else {
		m_fdelaytime = m_fKeydelay;
	}
	//

	m_btnSelect->setPos(m_btnSelect->getPos()->x, m_pInterface[m_nSelectedMenu]->getPos()->y);
	ptr = nullptr;
}

void InMainUI::OnInit(cD2DRenderer& renderer, sIScreen* in){
	for (uiInterface* x : m_pInterface){
		x->OnInit(renderer);
	}
	m_btnSelect->OnInit(renderer);
	m_callbackScreen = in;
}