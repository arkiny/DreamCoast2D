#include "StdAfx.h"
#include "cGameManager.h"
#include "coControl.h"
#include "wWorld.h"

cGameManager::cGameManager(void)
{
	m_pControl = nullptr;
	m_pWorld = nullptr;
}


cGameManager::~cGameManager(void)
{
	if (m_pControl != NULL)
		delete m_pControl;
	if (m_pWorld != NULL)
		delete m_pWorld;
}


void cGameManager::OnInit(cD2DRenderer& renderer)
{
	m_pControl = new coControl;
	m_pWorld = new wWorld();
	m_pWorld->OnInit(renderer, m_pControl);
}

void cGameManager::Render(cD2DRenderer& renderer)
{
	m_pWorld->Render(renderer);
}

void cGameManager::Update(float deltaTime)
{
	m_pWorld->Update(deltaTime);
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