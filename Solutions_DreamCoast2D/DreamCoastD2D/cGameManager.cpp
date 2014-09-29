#include "StdAfx.h"
#include "cGameManager.h"
#include "coControl.h"
#include "wWorld.h"
#include "sIScreen.h"
#include "sGameScreen.h"

cGameManager::cGameManager(void)
{
	m_pControl = nullptr;
	m_pCurrentScreen = nullptr;
}


cGameManager::~cGameManager(void)
{
	if (m_pControl != NULL)
		delete m_pControl;
	if (m_pCurrentScreen != NULL)
		delete m_pCurrentScreen;
}


void cGameManager::OnInit(cD2DRenderer& renderer)
{
	m_pControl = new coControl;

	// screen
	// 일단은 sGameScreen으로 게임을 시작한다.
	m_pCurrentScreen = new sGameScreen(this);
	m_pCurrentScreen->setControl(m_pControl);
	m_pCurrentScreen->OnInit(renderer);
}

void cGameManager::Render(cD2DRenderer& renderer)
{

	m_pCurrentScreen->Render(renderer);
}

void cGameManager::Update(float deltaTime)
{
	m_pCurrentScreen->Update(deltaTime);
}

void cGameManager::changeScreen(sIScreen* pnew){
	// exception
	if (m_pCurrentScreen == nullptr || pnew == nullptr) return;

	//m_pCurrentScreen->exit() 퇴장 과정 실시
	m_pCurrentScreen = pnew;

	//m_pCurrentScreen->OnInit() 시작 처리(rendering 처리)
}

void cGameManager::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// 키 컨트롤 처리
	switch (message)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
			return;
		}
		m_pControl->onKeyDown(wParam);
		break;

	case WM_KEYUP:
		m_pControl->onKeyUp(wParam);
		break;
	}
}