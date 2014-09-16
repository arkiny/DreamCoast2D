#include "StdAfx.h"
#include "cGameManager.h"
#include "mPlayer.h"
#include "coControl.h"
//#include "cPlayer.h"

cGameManager::cGameManager(void)
{
	//m_ipD2DBitmapBG = nullptr;
	//m_ipD2DBitmap = nullptr;
	//m_ipD2DBitmapFlip = nullptr;
	m_player = nullptr;
	m_pControl = nullptr;
}


cGameManager::~cGameManager(void)
{
	//SafeRelease(m_ipD2DBitmapBG);
	//SafeRelease(m_ipD2DBitmap);
	//SafeRelease(m_ipD2DBitmapFlip);
	//dest
	if (m_player!=NULL)
		delete m_player;
	if (m_pControl != NULL)
		delete m_pControl;
}


void cGameManager::OnInit(cD2DRenderer& renderer)
{
	m_pControl = new coControl;

	HWND hWnd = renderer.GetHwnd();
	/*m_ipD2DBitmapBG = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Tulips.jpg", NULL);
	m_ipD2DBitmap = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/ccc.png", NULL);
	m_ipD2DBitmapFlip = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/ccc.png", WICBitmapTransformFlipHorizontal);*/


	m_player = new mPlayer();
	m_player->setKeyControl(m_pControl);
	m_player->onInit(renderer);
}

void cGameManager::Render(cD2DRenderer& renderer)
{

	// background
	//if (m_ipD2DBitmapBG != nullptr)
	//{
	//	D2D1_SIZE_U size = renderer.GetRenderTargetSize();
	//	::D2D1_RECT_F dxArea = ::D2D1::RectF(0.0f, 0.0f, static_cast<float>(size.width), static_cast<float>(size.height));
	//	::D2D1_RECT_F srcArea = ::D2D1::RectF(0.0f, 0.0f, 1024.0f, 768.0f);

	//	renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmapBG, dxArea, 1.0f,
	//		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
	//		srcArea);
	//}

	m_player->onRender(renderer);
	


	/// 텍스트 출력
	//wchar_t* wszText_ = L"Hello World using DirectWrite!";
	//UINT32 cTextLength_ = (UINT32)wcslen(wszText_);

	//D2D1_RECT_F layoutRect = D2D1::RectF(
	//	100,
	//	300,
	//	800,
	//	400
	//	);

	//renderer.GetRenderTarget()->DrawTextW(
	//	wszText_,
	//	cTextLength_,
	//	renderer.GetTextFormat(),
	//	layoutRect,
	//	renderer.GetBrush());
}

void cGameManager::Update(float deltaTime)
{
	// 게임의 업데이트 처리
	m_player->onUpdate(deltaTime);
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
			return;
		}
		m_pControl->onKeyDown(wParam);
		break;

	case WM_KEYUP:
		m_pControl->onKeyUp(wParam);
		break;
	}
}