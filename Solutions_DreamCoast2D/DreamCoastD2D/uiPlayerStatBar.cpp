#include "stdafx.h"
#include "uiPlayerStatBar.h"
#include "cD2DRenderer.h"
#include "mIObject.h"

uiPlayerStatBar::uiPlayerStatBar()
{
}

uiPlayerStatBar::uiPlayerStatBar(mIObject* player){
	m_pplayer = player;
}

uiPlayerStatBar::~uiPlayerStatBar()
{
}

void uiPlayerStatBar::OnInit(cD2DRenderer& renderer){

}

void uiPlayerStatBar::Update(float delta){
	// �ִϸ��̼� ó���� ���� �ʴ��� ���� ������Ʈ�� �ʿ� ������...
}

void uiPlayerStatBar::Render(cD2DRenderer& renderer){
	uiPlayerStatBar::drawHealthbar(renderer);
}

void uiPlayerStatBar::drawHealthbar(cD2DRenderer& renderer){
	// ���� �̹��� ��ó���� ���� position select
	::D2D1_RECT_F portrait;
	portrait.top = 20.0f;
	portrait.bottom = 80.0f;
	portrait.left = 20.0f;
	portrait.right = 80.0f;

	::D2D1_RECT_F healthBar;
	healthBar.top = portrait.bottom;
	healthBar.bottom = healthBar.top + 20.0f;
	healthBar.left = portrait.left;
	healthBar.right = healthBar.left + 400.0f;

	::D2D1_RECT_F currentHealthbar;
	currentHealthbar.top = healthBar.top;
	currentHealthbar.bottom = healthBar.bottom;
	currentHealthbar.left = healthBar.left;

	float healthRate = (healthBar.left) + 
		(m_pplayer->getHealth() / m_pplayer->getMAXHealth() * 
		(healthBar.right - healthBar.left));

	if (healthRate <= healthBar.left){
		currentHealthbar.right = currentHealthbar.left;
	}
	else {
		currentHealthbar.right = healthRate;
	}

	/// �ؽ�Ʈ ���
	wchar_t* wszText_ = new wchar_t[20];
	swprintf(wszText_, 20,  L"HP: %.0f / %.0f", 
		m_pplayer->getHealth(), 
		m_pplayer->getMAXHealth());
	UINT32 cTextLength_ = (UINT32)wcslen(wszText_);

	D2D1_RECT_F layoutRect = D2D1::RectF(
		healthBar.left,
		healthBar.top,
		healthBar.right,
		healthBar.bottom
		);
	
	wchar_t* wszText2_ = L"Portrait";
	UINT32 cTextLength2_ = (UINT32)wcslen(wszText2_);


	renderer.GetRenderTarget()->FillRectangle(portrait, renderer.GetWhiteBrush());
	renderer.GetRenderTarget()->DrawRectangle(portrait, renderer.GetBrush());
	renderer.GetRenderTarget()->FillRectangle(healthBar, renderer.GetRedBrush());
	renderer.GetRenderTarget()->FillRectangle(currentHealthbar, renderer.GetGreenBrush());
	renderer.GetRenderTarget()->DrawRectangle(healthBar, renderer.GetBrush());

	// draw text
	renderer.GetRenderTarget()->DrawTextW(
		wszText_,
		cTextLength_,
		renderer.GetTextFormat(),
		layoutRect,
		renderer.GetBrush());

	renderer.GetRenderTarget()->DrawTextW(
		wszText2_,
		cTextLength2_,
		renderer.GetTextFormat(),
		portrait,
		renderer.GetBrush());

}