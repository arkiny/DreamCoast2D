#include "stdafx.h"
#include "uiPlayerStatBar.h"
#include "cD2DRenderer.h"
#include "mIObject.h"
#include "VECTOR2D.h"
#include "cResourceManager.h"

uiPlayerStatBar::uiPlayerStatBar()
{
	/// todo: 일단 고정형
	this->setPos(new VECTOR2D(20.0f, 40.0f));
}

uiPlayerStatBar::uiPlayerStatBar(mIObject* player){
	/// todo: 일단 고정형
	this->setPos(new VECTOR2D(20.0f, 40.0f));
	m_pplayer = player;
}

uiPlayerStatBar::~uiPlayerStatBar()
{
}

void uiPlayerStatBar::OnInit(cD2DRenderer& renderer){

}

void uiPlayerStatBar::Update(float delta){
	// 애니메이션 처리를 넣지 않는한 딱히 업데이트는 필요 없을듯...
}

void uiPlayerStatBar::Render(cD2DRenderer& renderer){
	uiPlayerStatBar::drawStatbar(renderer);
}

void uiPlayerStatBar::drawStatbar(cD2DRenderer& renderer){
	// 차후 이미지 재처리를 위한 position select
	
	::D2D1_RECT_F healthBar;
	healthBar.top = this->getPos()->y + 3.0f;
	healthBar.bottom = this->getPos()->y + 22.0f;
	healthBar.left = this->getPos()->x+ 4.0f;
	healthBar.right = this->getPos()->x + 347.0f;

	::D2D1_RECT_F currentHealthbar;
	currentHealthbar.top = healthBar.top;
	currentHealthbar.bottom = healthBar.bottom;
	currentHealthbar.left = healthBar.left;

	::D2D1_RECT_F manaBar;
	manaBar.top = healthBar.bottom + 6.0f;
	manaBar.bottom = manaBar.top + 12.0f;
	manaBar.left = healthBar.left;
	manaBar.right = healthBar.left + 279.0f;

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
	
	/*ID2D1GradientStopCollection *pGradientStops = NULL;
	D2D1_GRADIENT_STOP gradientStops[3];
	gradientStops[0].color = D2D1::ColorF(D2D1::ColorF::DarkRed, 1);
	gradientStops[0].position = 0.0f;
	gradientStops[1].color = D2D1::ColorF(D2D1::ColorF::Red, 1);
	gradientStops[1].position = 0.5f;
	gradientStops[2].color = D2D1::ColorF(D2D1::ColorF::DarkRed, 1);
	gradientStops[2].position = 1.0;
	HRESULT hr;
	hr = renderer.GetRenderTarget()->CreateGradientStopCollection(
		gradientStops,
		3,
		D2D1_GAMMA_2_2,
		D2D1_EXTEND_MODE_CLAMP,
		&pGradientStops
		);

	ID2D1LinearGradientBrush *m_pLinearGradientBrush = NULL;
	if (SUCCEEDED(hr))
	{
		hr = renderer.GetRenderTarget()->CreateLinearGradientBrush(
			D2D1::LinearGradientBrushProperties(
			D2D1::Point2F((healthBar.right - healthBar.left) / 2.0f, healthBar.top),
			D2D1::Point2F((healthBar.right - healthBar.left) / 2.0f, healthBar.bottom)),
			pGradientStops,
			&m_pLinearGradientBrush
			);
	}
*/
	

	renderer.ChangeBrush(D2D1::ColorF::Gray);
	renderer.GetRenderTarget()->FillRectangle(healthBar, renderer.GetBrush());
	
	if (::cResourceManager::GetInstance().getUIBitMap(UIID::REDBAR) != nullptr){
		::D2D1_RECT_F dxArea
			= { currentHealthbar.left, currentHealthbar.top,
			currentHealthbar.right,
			currentHealthbar.bottom };
		::D2D1_RECT_F srcArea
			= { 0, 0, ::cResourceManager::GetInstance().getUISize(UIID::REDBAR).x,
			::cResourceManager::GetInstance().getUISize(UIID::REDBAR).y };

		renderer.GetRenderTarget()->DrawBitmap(::cResourceManager::GetInstance().getUIBitMap(UIID::REDBAR),
			dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}
	
	/// manabar
	/*pGradientStops = NULL;
	D2D1_GRADIENT_STOP gradientStops2[3];
	gradientStops2[0].color = D2D1::ColorF(D2D1::ColorF::DarkBlue, 1);
	gradientStops2[0].position = 0.0f;
	gradientStops2[1].color = D2D1::ColorF(D2D1::ColorF::Blue, 1);
	gradientStops2[1].position = 0.5f;
	gradientStops2[2].color = D2D1::ColorF(D2D1::ColorF::DarkBlue, 1);
	gradientStops2[2].position = 1.0;

	hr = renderer.GetRenderTarget()->CreateGradientStopCollection(
		gradientStops2,
		3,
		D2D1_GAMMA_2_2,
		D2D1_EXTEND_MODE_CLAMP,
		&pGradientStops
		);

	m_pLinearGradientBrush = NULL;
	if (SUCCEEDED(hr))
	{
		hr = renderer.GetRenderTarget()->CreateLinearGradientBrush(
			D2D1::LinearGradientBrushProperties(
			D2D1::Point2F((manaBar.right - manaBar.left) / 2.0f, manaBar.top),
			D2D1::Point2F((manaBar.right - manaBar.left) / 2.0f, manaBar.bottom)),
			pGradientStops,
			&m_pLinearGradientBrush
			);
	}*/
	if (::cResourceManager::GetInstance().getUIBitMap(UIID::BLUEBAR) != nullptr){
		::D2D1_RECT_F dxArea
			= { manaBar.left, manaBar.top,
			manaBar.right,
			manaBar.bottom };
		::D2D1_RECT_F srcArea
			= { 0, 0, ::cResourceManager::GetInstance().getUISize(UIID::BLUEBAR).x,
			::cResourceManager::GetInstance().getUISize(UIID::BLUEBAR).y };

		renderer.GetRenderTarget()->DrawBitmap(::cResourceManager::GetInstance().getUIBitMap(UIID::BLUEBAR),
			dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}
	///
	
	// draw text
	renderer.GetRenderTarget()->DrawTextW(
		wszText_,
		cTextLength_,
		renderer.GetTextFormat(),
		layoutRect,
		renderer.GetWhiteBrush());

	
	if (::cResourceManager::GetInstance().getUIBitMap(UIID::STATBAR) != nullptr){
		::D2D1_RECT_F dxArea
			= { this->getPos()->x, this->getPos()->y, 
			this->getPos()->x + ::cResourceManager::GetInstance().getUISize(UIID::STATBAR).x,
			 this->getPos()->y + ::cResourceManager::GetInstance().getUISize(UIID::STATBAR).y };
		::D2D1_RECT_F srcArea
			= { 0, 0, ::cResourceManager::GetInstance().getUISize(UIID::STATBAR).x, 
			::cResourceManager::GetInstance().getUISize(UIID::STATBAR).y };

		renderer.GetRenderTarget()->DrawBitmap(::cResourceManager::GetInstance().getUIBitMap(UIID::STATBAR), 
			dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}
}