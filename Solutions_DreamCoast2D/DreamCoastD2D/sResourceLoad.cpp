#include "stdafx.h"
#include "sResourceLoad.h"
#include "cD2DRenderer.h"
#include "cResourceManager.h"
#include "cGameManager.h"
#include "sGameScreen.h"
#include "sMainMenuScreen.h"


sResourceLoad::sResourceLoad()
{
}

sResourceLoad::sResourceLoad(cGameManager* cg, int type){
	/*m_pNextScreen = nextScreen;*/
	m_nNextScreenType = type;
	m_pGameManager = cg;
}


sResourceLoad::~sResourceLoad()
{
}

void sResourceLoad::OnInit(){
}

void sResourceLoad::Update(float){
	// ���� �ε�ȭ�� ��� ���Ŀ� �ε� �ǽ�
	// ���� �ɰ��� �ε� �ۼ�Ƽ�� ǥ���� ��
	if (m_bLoadingRendered){ 
		if (m_nNextScreenType == BUTTONID::BTN_NEWGAME){
			cResourceManager::GetInstance().load();
			sGameScreen* input = new sGameScreen(m_pGameManager);
			m_pGameManager->changeScreen(input);
		}
		else if (m_nNextScreenType == BUTTONID::BTN_MAINMENU){
			cResourceManager::GetInstance().loadMainMenuResource();
			sMainMenuScreen* input = new sMainMenuScreen(m_pGameManager);
			m_pGameManager->changeScreen(input);
		}
	}
	
}

void sResourceLoad::Render(){	
	// �ε��� ���� â�� ����(���� ȭ�鿡 �ε�)
	HWND hwnd = ::cD2DRenderer::GetInstance().GetHwnd();
	RECT winRect;
	GetClientRect(hwnd, &winRect);
	D2D1_RECT_F target;
	target.top = static_cast<float>(winRect.top);
	target.bottom = static_cast<float>(winRect.bottom);
	target.left = static_cast<float>(winRect.left);
	target.right = static_cast<float>(winRect.right);

	::cD2DRenderer::GetInstance().GetRenderTarget()->FillRectangle(target, ::cD2DRenderer::GetInstance().GetBlackBrush());
	// �ؽ�Ʈ ���
	wchar_t* wszText_;

	// ���� �ε� ������ �ݹ����� ����
	if (m_nLoadingphase == 0){
		wszText_ = L"Loading...";
	}
	
	UINT32 cTextLength_ = (UINT32)wcslen(wszText_);
	::cD2DRenderer::GetInstance().GetRenderTarget()->DrawTextW(
		wszText_,
		cTextLength_,
		::cD2DRenderer::GetInstance().GetTextFormat(),
		target,
		::cD2DRenderer::GetInstance().GetWhiteBrush());

	m_bLoadingRendered = true;
}

void sResourceLoad::OnExit(){
}