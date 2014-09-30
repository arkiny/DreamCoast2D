#include "stdafx.h"
#include "sMainMenuScreen.h"
#include "coControl.h"
#include "cGameManager.h"
#include "sGameScreen.h"
#include "cD2DRenderer.h"


sMainMenuScreen::sMainMenuScreen()
{
//	m_pUI = nullptr;
}


sMainMenuScreen::~sMainMenuScreen()
{
	//if (m_pUI != NULL){
	//	delete m_pUI;
	//}
}

sMainMenuScreen::sMainMenuScreen(cGameManager* cg){
	m_pGameManager = cg;
}

void sMainMenuScreen::OnInit(cD2DRenderer& renderer){

}

void sMainMenuScreen::Update(float delta){
	if (this->getControl()->getKeyControlInfo()[VK_SPACE]){
		sGameScreen* input = new sGameScreen(m_pGameManager);
		input->setControl(this->getControl());
		m_pGameManager->changeScreen(input);
	}
}

void sMainMenuScreen::Render(cD2DRenderer& renderer){
	wchar_t* wszText2_ = L"Press Space to Start This Game";
	UINT32 cTextLength2_ = (UINT32)wcslen(wszText2_);
	

	D2D1_RECT_F layoutRect = D2D1::RectF(
		514.0,
		384.0,
		614.0,
		484.0
		);

	renderer.GetRenderTarget()->DrawTextW(
		wszText2_,
		cTextLength2_,
		renderer.GetTextFormat(),
		layoutRect,
		renderer.GetBrush());
}

void sMainMenuScreen::OnExit(){

}