#include "StdAfx.h"
#include "cGameManager.h"
//#include "cPlayer.h"

cGameManager::cGameManager(void)
:x(0), y(0), m_fAngle(0.0f), m_fAlpha(1.0f), m_fframe(0.0f), m_nframe(0)
{
	m_ipD2DBitmapBG = nullptr;
	m_ipD2DBitmap = nullptr;
	m_ipD2DBitmapFlip = nullptr;
}


cGameManager::~cGameManager(void)
{
	SafeRelease(m_ipD2DBitmapBG);
	SafeRelease(m_ipD2DBitmap);
	SafeRelease(m_ipD2DBitmapFlip);
}


void cGameManager::OnInit(cD2DRenderer& renderer)
{
	HWND hWnd = renderer.GetHwnd();
	m_ipD2DBitmapBG = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Tulips.jpg", NULL);
	m_ipD2DBitmap = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/ccc.png", NULL);
	m_ipD2DBitmapFlip = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/ccc.png", WICBitmapTransformFlipHorizontal);

	m_ipD2DBitmapAnimation = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/slice43_43_8x1r.png", NULL);
	m_ipD2DBitmapHeadFlipped = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/slice03_03_15x1.png", WICBitmapTransformFlipHorizontal);
}

void cGameManager::Render(cD2DRenderer& renderer)
{

	// background
	if (m_ipD2DBitmapBG != nullptr)
	{
		D2D1_SIZE_U size = renderer.GetRenderTargetSize();
		::D2D1_RECT_F dxArea = ::D2D1::RectF(0.0f, 0.0f, static_cast<float>(size.width), static_cast<float>(size.height));
		::D2D1_RECT_F srcArea = ::D2D1::RectF(0.0f, 0.0f, 1024.0f, 768.0f);

		renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmapBG, dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}
	
	//// rotation... then flip?
	//if (m_ipD2DBitmap != nullptr)
	//{
	//	::D2D1_RECT_F dxArea = ::D2D1::RectF(x, y, x + 100.0f, y + 100.0f);
	//	::D2D1_RECT_F srcArea = ::D2D1::RectF(0.0f, 0.0f, 512.0f, 512.0f);

	//	D2D1::Matrix3x2F rot = D2D1::Matrix3x2F::Rotation(m_fAngle, D2D1::Point2F(x + 50, y + 50));
	//	renderer.GetRenderTarget()->SetTransform(rot);

	//	renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, m_fAlpha,
	//		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
	//		srcArea);

	//	renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	//}

	//// flipped
	//if (m_ipD2DBitmapFlip != nullptr)
	//{
	//	// render 할 구역
	//	::D2D1_RECT_F dxArea = ::D2D1::RectF(x, y + 100.0f, x + 100.0f, y + 200.0f);
	//	// sprite의 구역
	//	::D2D1_RECT_F srcArea = ::D2D1::RectF(0.0f, 0.0f, 512.0f, 512.0f);

	//	renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmapFlip, dxArea, 1.0f,
	//		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
	//		srcArea);

	//	renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	//}

	//// 그냥 이동
	//if (m_ipD2DBitmap != nullptr)
	//{
	//	::D2D1_RECT_F dxArea = ::D2D1::RectF(x, y + 200.0f, x + 100.0f, y + 300.0f);
	//	::D2D1_RECT_F srcArea = ::D2D1::RectF(0.0f, 0.0f, 512.0f, 512.0f);

	//	//D2D1::Matrix3x2F rot = D2D1::Matrix3x2F::Rotation(m_fAngle, D2D1::Point2F(x + 50, y + 50));
	//	//renderer.GetRenderTarget()->SetTransform(rot);

	//	renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, 1.0f,
	//		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
	//		srcArea);

	//	renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	//}

	if (m_ipD2DBitmapAnimation != nullptr){
		//
		::D2D1_RECT_F dxArea = ::D2D1::RectF(x, y + 20.0f, x + 46.0f, y + 65.0f + 20.0f);
		//
		float pickframeX = (7 - m_nframe) * 46.0f;
		::D2D1_RECT_F srcArea = ::D2D1::RectF(0.0f + pickframeX, 0.0f, 46.0f + pickframeX, 65.0f);
		//

		//D2D1::Matrix3x2F rot = D2D1::Matrix3x2F::Rotation(m_fAngle, D2D1::Point2F(x + 50, y + 50));
		//renderer.GetRenderTarget()->SetTransform(rot);

		renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmapAnimation, dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);

		renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	}

	// 여기서 프레임 돌리기만 하면 될득
	if (m_ipD2DBitmapHeadFlipped != nullptr){
		//
		::D2D1_RECT_F dxArea = ::D2D1::RectF(x, y+20.0f, x + 46.0f, y + 65.0f+20.0f);
		//
		float pickframeX = 14 * 28.0f;		
		::D2D1_RECT_F srcArea = ::D2D1::RectF(0.0f + pickframeX, 0.0f, 46.0f + pickframeX, 30.0f);
		//

		//D2D1::Matrix3x2F rot = D2D1::Matrix3x2F::Rotation(m_fAngle, D2D1::Point2F(x + 50, y + 50));
		//renderer.GetRenderTarget()->SetTransform(rot);

		renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmapHeadFlipped, dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);

		renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	}


	wchar_t* wszText_ = L"Hello World using DirectWrite!";
	UINT32 cTextLength_ = (UINT32)wcslen(wszText_);

	D2D1_RECT_F layoutRect = D2D1::RectF(
		100,
		300,
		800,
		400
		);

	renderer.GetRenderTarget()->DrawTextW(
		wszText_,
		cTextLength_,
		renderer.GetTextFormat(),
		layoutRect,
		renderer.GetBrush());
}

void cGameManager::Update(float deltaTime)
{
	// 게임의 업데이트 처리
	x += deltaTime* 50.0f;

	m_fframe += deltaTime;
	if (m_fframe > 0.125f){
		m_nframe++;
		m_fframe = 0.0f;
	}

	if (m_nframe > 7){
		m_nframe = 0;
	}

	m_fAngle += 10.0f;

	m_fAlpha -= 0.1f;
	if (m_fAlpha <= 0.0f)
		m_fAlpha = 1.0f;
}

void cGameManager::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// 키 컨트롤 처리
	switch (message)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
		}
		return;

	}
}