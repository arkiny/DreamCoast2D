#include "stdafx.h"
#include "uiMenu.h"
#include "uiButton.h"
#include "cResourceManager.h"
#include "coControl.h"
#include "VECTOR2D.h"
#include "sGameScreen.h"

uiMenu::uiMenu()
{

}

uiMenu::uiMenu(int type, sIScreen* callback){
	m_type = type;
	m_pCallbackScreen = callback;
}

uiMenu::~uiMenu()
{
	uiInterface * ptr = nullptr;
	while (!m_vButtons.empty()){
		ptr = m_vButtons.back();
		if (ptr != NULL){
			delete ptr;
		}
		m_vButtons.pop_back();
	}
	ptr = nullptr;
}

void uiMenu::OnInit(cD2DRenderer& renderer){
	m_renderer = &renderer;
	RECT winRect;
	GetClientRect(renderer.GetHwnd(), &winRect);
	if (m_type == MN_NORMAL){
		// 여기서 좌표는 박스 안에서의 위치
		// todo:차후 기능 추가시 사용
		//m_vButtons.push_back(new uiButton(36.0f, 82.0f, BTN_SAVE));
		//m_vButtons.push_back(new uiButton(36.0f, 137.0f, BTN_LOAD2));
		m_vButtons.push_back(new uiButton(36.0f, 191.0f, BTN_RESTART));
		m_vButtons.push_back(new uiButton(36.0f, 246.0f, BTN_MAINMENU));
		m_vButtons.push_back(new uiButton(36.0f, 300.0f, BTN_EXITGAME));		
		::D2D1_RECT_F dxArea
			= { (winRect.right / 2.0f) - (::cResourceManager::GetInstance().getUISize(UIID::MN_NORMAL).x / 2.0f),
			(winRect.bottom / 2.0f) - (::cResourceManager::GetInstance().getUISize(UIID::MN_NORMAL).y / 2.0f),
			(winRect.right / 2.0f) + (::cResourceManager::GetInstance().getUISize(UIID::MN_NORMAL).x / 2.0f),
			(winRect.bottom / 2.0f) + (::cResourceManager::GetInstance().getUISize(UIID::MN_NORMAL).y / 2.0f) };
		for (uiInterface* x : m_vButtons){
			x->OnInit(renderer);
			x->setPos(dxArea.left + x->getPos()->x, dxArea.top + x->getPos()->y);
		}
		m_btnSelect = new uiButton(dxArea.left + 5.0f, m_vButtons[0]->getPos()->y, BTN_REDARROW2);
		
	}
	else if (m_type == MN_GAMEOVER){
		// todo: 차후 기능 추가시 사용
		//m_vButtons.push_back(new uiButton(36.0f, 82.0f, BTN_LOADLAST));
		//m_vButtons.push_back(new uiButton(36.0f, 136.0f, BTN_VILLAGE));
		m_vButtons.push_back(new uiButton(36.0f, 191.0f, BTN_RESTART));
		m_vButtons.push_back(new uiButton(36.0f, 246.0f, BTN_MAINMENU));
		m_vButtons.push_back(new uiButton(36.0f, 300.0f, BTN_EXITGAME));
		::D2D1_RECT_F dxArea
			= { (winRect.right / 2.0f) - (::cResourceManager::GetInstance().getUISize(UIID::MN_GAMEOVER).x / 2.0f),
			(winRect.bottom / 2.0f) - (::cResourceManager::GetInstance().getUISize(UIID::MN_GAMEOVER).y / 2.0f),
			(winRect.right / 2.0f) + (::cResourceManager::GetInstance().getUISize(UIID::MN_GAMEOVER).x / 2.0f),
			(winRect.bottom / 2.0f) + (::cResourceManager::GetInstance().getUISize(UIID::MN_GAMEOVER).y / 2.0f) };
		for (uiInterface* x : m_vButtons){
			x->OnInit(renderer);
			x->setPos(dxArea.left + x->getPos()->x, dxArea.top + x->getPos()->y);
		}
		m_btnSelect = new uiButton(dxArea.left + 5.0f, m_vButtons[0]->getPos()->y, BTN_REDARROW2);
	}
	m_btnSelect->OnInit(renderer);
}

void uiMenu::changeMenuType(){
	uiInterface * ptr = nullptr;
	while (!m_vButtons.empty()){
		ptr = m_vButtons.back();
		if (ptr != NULL){
			delete ptr;
		}
		m_vButtons.pop_back();
	}

	if (m_btnSelect != NULL){
		delete m_btnSelect;
	}

	ptr = nullptr;
	if (m_type == MN_NORMAL){
		m_type = MN_GAMEOVER;
		OnInit(*m_renderer);
	}
	else if (m_type == MN_GAMEOVER){
		m_type = MN_NORMAL;
		OnInit(*m_renderer);
	}
}

void uiMenu::Update(float delta){
	if (m_type == MN_NORMAL && dynamic_cast<sGameScreen*>(m_pCallbackScreen)->isGameOver()){
		// change menu type to MN_GAMEOVER
		changeMenuType();
	}
	else if (m_type == MN_GAMEOVER && !dynamic_cast<sGameScreen*>(m_pCallbackScreen)->isGameOver()){
		// change menu type to MN_NORMAL
		changeMenuType();
	}

	bool isGameover = dynamic_cast<sGameScreen*>(m_pCallbackScreen)->isGameOver();
	if (isGameover){ // 게임오버시 메뉴 고정
		m_bMenuActivated = true;
	}
	else{ //게임오버 아닐때는 esc로 메뉴를 불러올수 있다.
		if (coControl::GetInstance().getKeyControlInfo()[VK_ESCAPE]){
			if (m_fdelaytime >= m_fKeydelay){
				if (m_bMenuActivated == false){
					m_bMenuActivated = true;
					dynamic_cast<sGameScreen*>(m_pCallbackScreen)
						->setWorldActivation(false);
				}
				else{
					m_bMenuActivated = false;
					dynamic_cast<sGameScreen*>(m_pCallbackScreen)
						->setWorldActivation(true);
				}
			}
			m_fdelaytime -= delta;
			if (m_fdelaytime <= 0){
				m_fdelaytime = m_fKeydelay;
			}
		}
		if (!coControl::GetInstance().getKeyControlInfo()[VK_ESCAPE]){
			m_fdelaytime = m_fKeydelay;
		}
	}
	
	// update buttons when it activated
	if (m_bMenuActivated){
		uiButton* ptr = nullptr;
		/// mouse Control
		for (unsigned int i = 0; i < m_vButtons.size(); i++){
			m_vButtons[i]->Update(delta);

			ptr = (uiButton*)m_vButtons[i];

			if (ptr->isSelected()){
				m_nSelectedMenu = i;
				if (ptr->isActivated()){
					dynamic_cast<sGameScreen*>(m_pCallbackScreen)
						->setActivate(ptr->getButtonType(), true);
				}
			}
		}
		
		/// keyboard control
		// 키보드 단축키로 컨트롤
		if (coControl::GetInstance().getKeyControlInfo()[0x52]){
			dynamic_cast<sGameScreen*>(m_pCallbackScreen)
				->setActivate(BTN_RESTART, true);
		}
		else if (coControl::GetInstance().getKeyControlInfo()[0x4D]){
			dynamic_cast<sGameScreen*>(m_pCallbackScreen)
				->setActivate(BTN_MAINMENU, true);
		}
		else if (coControl::GetInstance().getKeyControlInfo()[0x45]){
			dynamic_cast<sGameScreen*>(m_pCallbackScreen)
				->setActivate(BTN_EXITGAME, true);
		}

		// keyboard move
		if (coControl::GetInstance().getKeyControlInfo()[VK_DOWN]){
			if (m_fmovedelaytime >= m_fKeydelay){
				m_nSelectedMenu++;
				if (m_nSelectedMenu >= static_cast<int>(m_vButtons.size())){
					m_nSelectedMenu = 0;
				}
			}
			m_fmovedelaytime -= delta;
			if (m_fmovedelaytime <= 0){
				m_fmovedelaytime = m_fKeydelay;
			}
		}
		else if (coControl::GetInstance().getKeyControlInfo()[VK_UP]){
			if (m_fmovedelaytime >= m_fKeydelay){
				m_nSelectedMenu--;
				if (m_nSelectedMenu < 0){
					m_nSelectedMenu = m_vButtons.size() - 1;
				}
			}
			m_fmovedelaytime -= delta;
			if (m_fmovedelaytime <= 0){
				m_fmovedelaytime = m_fKeydelay;
			}
		}
		else {
			m_fmovedelaytime = m_fKeydelay;
		}

		//
		// keyboard execute
		if (coControl::GetInstance().getKeyControlInfo()[VK_RETURN] ||
			coControl::GetInstance().getKeyControlInfo()[VK_SPACE] ||
			coControl::GetInstance().getKeyControlInfo()[0x5A]){
			ptr = (uiButton*)m_vButtons[m_nSelectedMenu];
			dynamic_cast<sGameScreen*>(m_pCallbackScreen)
				->setActivate(ptr->getButtonType(), true);
			// 다음 화면에서도 연속으로 입력되는 문제가 생기므로
			// 여기서 해제하고 지나가야한다.
			coControl::GetInstance().onKeyUp(VK_RETURN);
			coControl::GetInstance().onKeyUp(VK_SPACE);
			coControl::GetInstance().onKeyUp(0x5A);
		}
		//
		m_btnSelect->setPos(m_btnSelect->getPos()->x, m_vButtons[m_nSelectedMenu]->getPos()->y);
	}// end action when menu activated
}

void uiMenu::Render(cD2DRenderer& renderer){
	if (m_bMenuActivated){
		if (m_type == MN_NORMAL){
			draw(renderer, MN_NORMAL);
		}
		else if (m_type == MN_GAMEOVER){
			draw(renderer, MN_GAMEOVER);
		}
		for (uiInterface* x : m_vButtons){
			x->Render(renderer);
		}
		m_btnSelect->Render(renderer);
	}
}

void uiMenu::draw(cD2DRenderer& renderer, int type){
	RECT winRect;
	GetClientRect(renderer.GetHwnd(), &winRect);
	if (::cResourceManager::GetInstance().getUIBitMap(type) != nullptr){
		::D2D1_RECT_F dxArea
			= { (winRect.right / 2.0f) - (::cResourceManager::GetInstance().getUISize(type).x / 2.0f),
			(winRect.bottom / 2.0f) - (::cResourceManager::GetInstance().getUISize(type).y / 2.0f),
			(winRect.right / 2.0f) + (::cResourceManager::GetInstance().getUISize(type).x / 2.0f),
			(winRect.bottom / 2.0f) + (::cResourceManager::GetInstance().getUISize(type).y / 2.0f) };

		::D2D1_RECT_F srcArea
			= { 0, 0, ::cResourceManager::GetInstance().getUISize(type).x,
			::cResourceManager::GetInstance().getUISize(type).y };

		renderer.GetRenderTarget()->DrawBitmap(::cResourceManager::GetInstance().getUIBitMap(type),
			dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}
}