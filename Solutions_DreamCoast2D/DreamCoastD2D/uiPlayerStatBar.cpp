#include "stdafx.h"
#include "uiPlayerStatBar.h"
#include "cD2DRenderer.h"
#include "VECTOR2D.h"
#include "cResourceManager.h"

uiPlayerStatBar::uiPlayerStatBar()
{
	/// todo: 일단 고정형
	this->setPos(new VECTOR2D(20.0f, 40.0f));
}

uiPlayerStatBar::uiPlayerStatBar(ICharacter* player){
	/// todo: 일단 고정형
	this->setPos(new VECTOR2D(20.0f, 40.0f));
	m_pplayer = player;
}

uiPlayerStatBar::~uiPlayerStatBar()
{
}

void uiPlayerStatBar::OnInit(){
	// 차후 이미지 재처리를 위한 position select
	healthBar.top = this->getPos()->y + 3.0f;
	healthBar.bottom = this->getPos()->y + 22.0f;
	healthBar.left = this->getPos()->x + 4.0f;
	healthBar.right = this->getPos()->x + 347.0f;

	manaBar.top = healthBar.bottom + 6.0f;
	manaBar.bottom = manaBar.top + 12.0f;
	manaBar.left = healthBar.left;
	manaBar.right = healthBar.left + 279.0f;
}

void uiPlayerStatBar::Update(float delta){
	// 애니메이션 처리를 넣지 않는한 딱히 업데이트는 필요 없을듯...
}

void uiPlayerStatBar::Render(){
	uiPlayerStatBar::drawStatbar();
	///	
	if (::cResourceManager::GetInstance().getUIBitMap(UIID::STATBAR) != nullptr){
		::D2D1_RECT_F dxArea
			= { this->getPos()->x, this->getPos()->y,
			this->getPos()->x + ::cResourceManager::GetInstance().getUISize(UIID::STATBAR).x,
			this->getPos()->y + ::cResourceManager::GetInstance().getUISize(UIID::STATBAR).y };
		::D2D1_RECT_F srcArea
			= { 0, 0, ::cResourceManager::GetInstance().getUISize(UIID::STATBAR).x,
			::cResourceManager::GetInstance().getUISize(UIID::STATBAR).y };

		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawBitmap(::cResourceManager::GetInstance().getUIBitMap(UIID::STATBAR),
			dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}
}

void uiPlayerStatBar::drawStatbar(){	
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

	/// 텍스트 출력
	wchar_t* wszText_ = new wchar_t[20];
	swprintf(wszText_, 20,  L" %.0f / %.0f", 
		m_pplayer->getHealth(), 
		m_pplayer->getMAXHealth());
	UINT32 cTextLength_ = (UINT32)wcslen(wszText_);

	D2D1_RECT_F layoutRect = D2D1::RectF(
		healthBar.left,
		healthBar.top,
		healthBar.right,
		healthBar.bottom
		);
	

	::cD2DRenderer::GetInstance().ChangeBrush(D2D1::ColorF::Gray);
	::cD2DRenderer::GetInstance().GetRenderTarget()->FillRectangle(healthBar, ::cD2DRenderer::GetInstance().GetBrush());
	
	if (::cResourceManager::GetInstance().getUIBitMap(UIID::REDBAR) != nullptr){
		::D2D1_RECT_F dxArea
			= { currentHealthbar.left, currentHealthbar.top,
			currentHealthbar.right,
			currentHealthbar.bottom };
		::D2D1_RECT_F srcArea
			= { 0, 0, ::cResourceManager::GetInstance().getUISize(UIID::REDBAR).x,
			::cResourceManager::GetInstance().getUISize(UIID::REDBAR).y };

		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawBitmap(::cResourceManager::GetInstance().getUIBitMap(UIID::REDBAR),
			dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}

	// draw text
	::cD2DRenderer::GetInstance().GetRenderTarget()->DrawTextW(
		wszText_,
		cTextLength_,
		::cD2DRenderer::GetInstance().GetTextFormat(),
		layoutRect,
		::cD2DRenderer::GetInstance().GetWhiteBrush());

	///
	
	::D2D1_RECT_F currentmanaBar;
	currentmanaBar.top = manaBar.top;
	currentmanaBar.bottom = manaBar.bottom;
	currentmanaBar.left = manaBar.left;

	float manaRate = (manaBar.left) +
		(m_pplayer->getMP() / m_pplayer->getMaxMp() *
		(manaBar.right - manaBar.left));

	if (manaRate <= manaBar.left){
		currentmanaBar.right = currentmanaBar.left;
	}
	else {
		currentmanaBar.right = manaRate;
	}

	::cD2DRenderer::GetInstance().ChangeBrush(D2D1::ColorF::Gray);
	::cD2DRenderer::GetInstance().GetRenderTarget()->FillRectangle(manaBar, ::cD2DRenderer::GetInstance().GetBrush());

	/// manabar
	if (::cResourceManager::GetInstance().getUIBitMap(UIID::BLUEBAR) != nullptr){
		::D2D1_RECT_F dxArea
			= { currentmanaBar.left, currentmanaBar.top,
			currentmanaBar.right,
			currentmanaBar.bottom };
		::D2D1_RECT_F srcArea
			= { 0, 0, ::cResourceManager::GetInstance().getUISize(UIID::BLUEBAR).x,
			::cResourceManager::GetInstance().getUISize(UIID::BLUEBAR).y };

		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawBitmap(::cResourceManager::GetInstance().getUIBitMap(UIID::BLUEBAR),
			dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}
}