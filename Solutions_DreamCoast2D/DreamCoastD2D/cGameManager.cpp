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

	// ������ �� �����̿�
	// ���ҽ��� �̱������� ����ȭ�߱⶧���� ����� ū�ϳ� �Ѥ�
	// if (m_pResourceMng != NULL)
	//	delete m_pResourceMng;
}

void cGameManager::OnInit(cD2DRenderer& renderer)
{
	m_rRenderer = &renderer;

	// singleton Ŭ���� ����
	// �Ʒ� �ΰ��� �� 1������ �ʿ��� Ŭ������.
	m_pControl = new coControl;
	m_pResourceMng = new cResourceManager;

	// screen
	// �ϴ��� sGameScreen���� ������ �����Ѵ�.
	m_pCurrentScreen = new sMainMenuScreen(this);
	m_pCurrentScreen->OnInit(*m_rRenderer);
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

	// ����ó��
	m_pCurrentScreen->OnExit();
	if (m_pCurrentScreen!= NULL)
		delete m_pCurrentScreen;	// Ȥ�� �𸣴� ���� ��ũ�� �����ͳ��� ���뵵 ����
								// ��ũ�� ���� �����͸� ������ �����Ƿ�!
	m_pCurrentScreen = pnew;	// �Ű�
	// render�� ���� ���� �ʱ�ȭ�� �ƴ�, ���ҽ� �Ŵ����� �̿��� 
	// ���ҽ� �ʱ�ȭ�� �̴ϼȶ���¡ ����
	// renderer�� �ʿ��ϸ� �����ؼ� �ű�� ���� �Ѥ�
	m_pCurrentScreen->OnInit(*m_rRenderer);
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