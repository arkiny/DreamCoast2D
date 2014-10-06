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

void sResourceLoad::OnInit(cD2DRenderer& renderer){
	// �ε��� ���� â�� ����(���� ȭ�鿡 �ε�)
	m_pRenderer = &renderer;

	// 1006TODO
	HWND hwnd = renderer.GetHwnd();
	RECT winRect;
	GetClientRect(hwnd, &winRect);
	D2D1_RECT_F target;
	target.top = winRect.top;
	target.bottom = winRect.bottom;
	target.left = winRect.left;
	target.right = winRect.right;

	renderer.GetRenderTarget()->FillRectangle(target, renderer.GetBlackBrush());
	/// �ؽ�Ʈ ���
	wchar_t* wszText_ = L"Loading...";
	UINT32 cTextLength_ = (UINT32)wcslen(wszText_);
	renderer.GetRenderTarget()->DrawTextW(
		wszText_,
		cTextLength_,
		renderer.GetTextFormat(),
		target,
		renderer.GetBrush());
}

void sResourceLoad::Update(float){
	if (m_nNextScreenType == BUTTONID::BTN_NEWGAME){
		cResourceManager::GetInstance().load(*m_pRenderer);
		sGameScreen* input = new sGameScreen(m_pGameManager);
		m_pGameManager->changeScreen(input);
	}
	else if (m_nNextScreenType == BUTTONID::BTN_MAINMENU){
		cResourceManager::GetInstance().loadMainMenuResource(*m_pRenderer);
		sMainMenuScreen* input = new sMainMenuScreen(m_pGameManager);
		m_pGameManager->changeScreen(input);
	}
	
}

void sResourceLoad::Render(cD2DRenderer&){

}

void sResourceLoad::OnExit(){
}