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
	// 먼저 로딩화면 출력 이후에 로딩 실시
	// 차후 쪼개서 로딩 퍼센티지 표시할 것
	if (m_bLoadingRendered){ 
		if (m_nNextScreenType == BUTTONID::BTN_NEWGAME){
			cResourceManager::GetInstance().load();
			sGameScreen* input = new sGameScreen(m_pGameManager);
			m_pGameManager->changeScreen(input);
		}
		else if (m_nNextScreenType == BUTTONID::BTN_MAINMENU){
			cResourceManager::GetInstance().releaseGameResource();
			cResourceManager::GetInstance().loadMainMenuResource();
			sMainMenuScreen* input = new sMainMenuScreen(m_pGameManager);
			m_pGameManager->changeScreen(input);
		}
	}
	
}

void sResourceLoad::Render(){	
	// 로딩시 먼저 창을 띄운뒤(검은 화면에 로딩)
	HWND hwnd = ::cD2DRenderer::GetInstance().GetHwnd();
	RECT winRect;
	GetClientRect(hwnd, &winRect);
	D2D1_RECT_F target;
	target.top = static_cast<float>(winRect.top);
	target.bottom = static_cast<float>(winRect.bottom);
	target.left = static_cast<float>(winRect.left);
	target.right = static_cast<float>(winRect.right);

	::cD2DRenderer::GetInstance().GetRenderTarget()->FillRectangle(target, ::cD2DRenderer::GetInstance().GetBlackBrush());
	
	
	//
	//wchar_t* wszText_ = new wchar_t[20];

	//int length = 0;
	//length += swprintf(wszText_ + length, 20, L"%d", m_nCurrentPage);
	//UINT32 cTextLength_ = (UINT32)wcslen(wszText_);

	//// draw text
	//::cD2DRenderer::GetInstance().GetRenderTarget()->DrawTextW(
	//	wszText_,
	//	cTextLength_,
	//	::cD2DRenderer::GetInstance().GetTextFormat(),
	//	m_RectPageOut,
	//	::cD2DRenderer::GetInstance().GetBlackBrush());

	//delete[] wszText_;
	
	// 텍스트 출력
	wchar_t* wszText_ = new wchar_t[20];
	int length = 0;
	length += swprintf(wszText_ + length, 20, L"");
	UINT32 cTextLength_ = (UINT32)wcslen(wszText_);
	
	// 차후 로딩 페이즈 콜백으로 조절
	if (m_nLoadingphase == 0){
		length += swprintf(wszText_ + length, 20, L"Loading...");
	}
	cTextLength_ = (UINT32)wcslen(wszText_);
		
	::cD2DRenderer::GetInstance().GetRenderTarget()->DrawTextW(
		wszText_,
		cTextLength_,
		::cD2DRenderer::GetInstance().GetTextFormat(),
		target,
		::cD2DRenderer::GetInstance().GetWhiteBrush());

	m_bLoadingRendered = true;
	delete[] wszText_;
}

void sResourceLoad::OnExit(){
}