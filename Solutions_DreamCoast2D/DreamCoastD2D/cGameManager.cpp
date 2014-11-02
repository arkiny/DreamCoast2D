#include "StdAfx.h"
#include "cGameManager.h"
#include "coControl.h"
#include "wWorld.h"
#include "sIScreen.h"
#include "sGameScreen.h"
#include "sMainMenuScreen.h"
#include "cResourceManager.h"
#include "cSoundManager.h"
#include "cChatManager.h"
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

	// 문제는 이 두줄이요
	// 리소스는 싱글톤으로 전역화했기때문에 지우면 큰일남 ㅡㅡ
	// if (m_pResourceMng != NULL)
	//	delete m_pResourceMng;
}

void cGameManager::OnInit()
{

	// singleton 클래스 시작
	// 아래 두개는 딱 1개씩만 필요한 클래스다.
	m_pControl = new coControl;
	m_pResourceMng = new cResourceManager;
	m_pSoundMng = new cSoundManager;
	m_pSoundMng->init();
	// screen
	// 일단은 sGameScreen으로 게임을 시작한다.
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

	// 삭제처리
	m_pCurrentScreen->OnExit();
	if (m_pCurrentScreen!= NULL)
		delete m_pCurrentScreen;	// 혹시 모르니 현재 스크린 포인터내의 내용도 삭제
								// 스크린 역시 포인터를 가지고 있으므로!
	m_pCurrentScreen = pnew;	// 옮경
	// render를 통한 시작 초기화가 아닌, 리소스 매니저를 이용한 
	// 리소스 초기화로 이니셜라이징 시작
	// renderer가 필요하면 저장해서 옮기면 되지 ㅡㅡ
	m_pCurrentScreen->OnInit();
}

void cGameManager::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, HINSTANCE hInstance)
{
	
	// 키 컨트롤 처리
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
		if (wParam == VK_TAB){
			if (cChatManager::GetInstance().getVisibleStatus()){
				cChatManager::GetInstance().setVisible(false);
			}
			else{
				cChatManager::GetInstance().setVisible(true);
			}			
		}
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
		// 이상하게 wParam에서 마우스 뗄때는 감지를 못한다.
		// 0으로 wParam값이 나옴
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