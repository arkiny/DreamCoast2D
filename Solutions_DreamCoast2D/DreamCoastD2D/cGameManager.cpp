#include "StdAfx.h"
#include "cGameManager.h"
#include "coControl.h"
#include "wWorld.h"
#include "sIScreen.h"
#include "sGameScreen.h"
#include "sMainMenuScreen.h"
#include "cResourceManager.h"

cGameManager::cGameManager(void)
{
	m_rRenderer = nullptr;
	m_pControl = nullptr;
	m_pCurrentScreen = nullptr;
	m_pResourceMng = nullptr;
}

cGameManager::~cGameManager(void)
{
	if (m_pControl != NULL)
		delete m_pControl;
	if (m_pCurrentScreen != NULL)
		delete m_pCurrentScreen;
	if (m_pResourceMng != NULL)
		delete m_pResourceMng;
}

void cGameManager::OnInit(cD2DRenderer& renderer)
{
	m_pControl = new coControl;
	m_rRenderer = &renderer;
	m_pResourceMng = new cResourceManager;

	// screen
	// 일단은 sGameScreen으로 게임을 시작한다.
	m_pCurrentScreen = new sMainMenuScreen(this);
	m_pCurrentScreen->setControl(m_pControl);
	m_pCurrentScreen->OnInit(*m_rRenderer, m_pResourceMng);
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

	// 삭제처리
	m_pCurrentScreen->OnExit();
	delete m_pCurrentScreen;	// 혹시 모르니 현재 스크린 포인터내의 내용도 삭제
								// 스크린 역시 포인터를 가지고 있으므로!
	m_pCurrentScreen = pnew;	// 옮경
	// render를 통한 시작 초기화가 아닌, 리소스 매니저를 이용한 
	// 리소스 초기화로 이니셜라이징 시작
	// renderer가 필요하면 저장해서 옮기면 되지 ㅡㅡ
	m_pCurrentScreen->OnInit(*m_rRenderer, m_pResourceMng);
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