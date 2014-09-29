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
	// �ϴ��� sGameScreen���� ������ �����Ѵ�.
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

	//m_pCurrentScreen->exit() ���� ���� �ǽ�
	m_pCurrentScreen = pnew;

	//m_pCurrentScreen->OnInit() ���� ó��(rendering ó��)
}

void cGameManager::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Ű ��Ʈ�� ó��
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