#include "StdAfx.h"
#include "cGameManager.h"
#include "coControl.h"
#include "wWorld.h"
#include "sIScreen.h"
#include "sGameScreen.h"
#include "sMainMenuScreen.h"
#include "cResourceManager.h"
#include "cSoundManager.h"
#include "mGFX.h"

cGameManager::cGameManager(void)
{
	m_pControl = nullptr;
	m_pCurrentScreen = nullptr;
	m_pResourceMng = nullptr;
	m_pSoundMng = nullptr;
	m_pGFX = nullptr;
}

cGameManager::~cGameManager(void)
{
	if (m_pControl != NULL)
		delete m_pControl;
	if (m_pCurrentScreen != NULL)
		delete m_pCurrentScreen;

	// TODO : destructor
	/*if (m_pResourceMng != NULL)
		delete m_pResourceMng;*/
	
	// TODO : destructor
	/*if (m_pSoundMng != NULL)
		delete m_pSoundMng;*/

	// ������ �� �����̿�
	// ���ҽ��� �̱������� ����ȭ�߱⶧���� ����� ū�ϳ� �Ѥ�
	// if (m_pResourceMng != NULL)
	//	delete m_pResourceMng;
}

void cGameManager::OnInit()
{

	// singleton Ŭ���� ����
	// �Ʒ� �ΰ��� �� 1������ �ʿ��� Ŭ������.
	m_pControl = new coControl;
	m_pResourceMng = new cResourceManager;
	m_pSoundMng = new cSoundManager;
	m_pSoundMng->init();
	// screen
	// �ϴ��� sGameScreen���� ������ �����Ѵ�.
	m_pCurrentScreen = new sMainMenuScreen(this);
	m_pCurrentScreen->OnInit();

	m_pGFX = new mGFX;
}

void cGameManager::Render()
{
	m_pCurrentScreen->Render();
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
	m_pCurrentScreen->OnInit();
}

void cGameManager::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, HINSTANCE hInstance)
{
	
	// Ű ��Ʈ�� ó��
	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_KEYDOWN:
		//if (wParam == VK_ESCAPE)
		//{
		//	PostQuitMessage(0);
		//	return;
		//}
		m_pControl->onKeyDown(wParam);
		break;

	case WM_KEYUP:
		m_pControl->onKeyUp(wParam);
		break;

	case WM_LBUTTONDOWN:
		m_pControl->onKeyDown(wParam);
		m_pControl->onMouseClick(lParam);
		break;

	case WM_LBUTTONUP: 
		// �̻��ϰ� wParam���� ���콺 ������ ������ ���Ѵ�.
		// 0���� wParam���� ����
		m_pControl->onKeyUp(VK_LBUTTON);
		break;

	case WM_RBUTTONDOWN:
		m_pControl->onKeyDown(wParam);
		break;

	case WM_RBUTTONUP:
		m_pControl->onKeyUp(VK_RBUTTON);
		break;


	//case WM_LBUTTONDBLCLK:
	//	m_pControl->onKeyDown(wParam);
	//	break;

	case WM_MOUSEMOVE:
		m_pControl->onMouseMove(lParam);
		break;
	}
}