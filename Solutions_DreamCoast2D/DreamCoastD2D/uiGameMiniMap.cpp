#include "stdafx.h"
#include "uiGameMiniMap.h"
#include "cD2DRenderer.h"
#include "wTileMap.h"
#include "VECTOR2D.h"
#include "uTile.h"
#include "mIObject.h"
#include "cResourceManager.h"

uiGameMiniMap::uiGameMiniMap()
{	
	m_pTileMap = nullptr;
	this->setPos(new VECTOR2D(20.0f, 40.0f));
}


uiGameMiniMap::~uiGameMiniMap()
{
}

uiGameMiniMap::uiGameMiniMap(wTileMap* ptileMap){
	m_pTileMap = ptileMap;
	this->setPos(new VECTOR2D(20.0f, 40.0f));
}

void uiGameMiniMap::OnInit(){

}

void uiGameMiniMap::Update(float delta){

}

void uiGameMiniMap::Render(){

	// todo: 함수화 해서 나누는건 나중에... 비트맵으로 그리게 될때...
	// todo: option에 따라서 크기 세분화
	::D2D1_RECT_F MiniMapOutline;
	::RECT winRect;
	GetClientRect(::cD2DRenderer::GetInstance().GetHwnd(), &winRect);

	MiniMapOutline.top = winRect.top + 30.0f;
	MiniMapOutline.bottom = MiniMapOutline.top + 210.0f;
	MiniMapOutline.right = winRect.right - 20.0f;
	MiniMapOutline.left = MiniMapOutline.right - 210.0f;

	this->setPos(MiniMapOutline.left, MiniMapOutline.top);

	::D2D1_RECT_F MiniMapinline;
	MiniMapinline.top = MiniMapOutline.top + (11.0f/2.0f);
	MiniMapinline.bottom = MiniMapOutline.bottom - (11.0f/2.0f);
	MiniMapinline.left = MiniMapOutline.left + (11.0f/2.0f);
	MiniMapinline.right = MiniMapOutline.right - (11.0f/2.0f);
	
	::cD2DRenderer::GetInstance().GetRenderTarget()->FillRectangle(MiniMapinline,
		::cD2DRenderer::GetInstance().GetWhiteBrush());

	

	
	float height = (MiniMapinline.bottom - MiniMapinline.top)
		/ m_pTileMap->getMapLimit().y;

	float width = (MiniMapinline.right - MiniMapinline.left)
		/ m_pTileMap->getMapLimit().x;

	::D2D1_RECT_F MiniRectangle;
	/// grid
	for (int j = 0; j < m_pTileMap->getMapLimit().y; j++){
		for (int i = 0; i < m_pTileMap->getMapLimit().x; i++){
			MiniRectangle.left = MiniMapinline.left + (width* static_cast<float>(i));
			MiniRectangle.right = MiniRectangle.left + width;
			MiniRectangle.top = MiniMapinline.top + (height* static_cast<float>(j));
			MiniRectangle.bottom = MiniRectangle.top + height;
			
			if (m_pTileMap->getMapinfo(j, i) == 0){
				/*renderer.GetRenderTarget()->FillRectangle(MiniRectangle,
					renderer.GetWhiteBrush());*/
			}
			else {
				::cD2DRenderer::GetInstance().GetRenderTarget()->FillRectangle(MiniRectangle,
					::cD2DRenderer::GetInstance().GetBlackBrush());
			}
			::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(MiniRectangle,
				::cD2DRenderer::GetInstance().GetBlackBrush());
		}
	}

	// player 위치 출력
	MiniRectangle.left = MiniMapinline.left + (width* m_pTileMap->getPlayerTilePos().y) + 1.0f;
	MiniRectangle.right = MiniRectangle.left + width - 2.0f;
	MiniRectangle.top = MiniMapinline.top + (height* m_pTileMap->getPlayerTilePos().x) + 1.0f;
	MiniRectangle.bottom = MiniRectangle.top + height - 2.0f;
	
	::cD2DRenderer::GetInstance().ChangeBrush(D2D1::ColorF::ForestGreen);
	::cD2DRenderer::GetInstance().GetRenderTarget()->FillRectangle(MiniRectangle,
		::cD2DRenderer::GetInstance().GetBrush());

	// 몹들 위치 출력
	VECTOR2D pt(0.0f, 0.0f);
	for (mIObject* x : m_pTileMap->getMobList()){
		pt = m_pTileMap->getTileCoordinates(*(x->getDrawPos()));

		MiniRectangle.left = MiniMapinline.left + (width* pt.y) + 1.0f;
		MiniRectangle.right = MiniRectangle.left + width - 2.0f;
		MiniRectangle.top = MiniMapinline.top + (height* pt.x) + 1.0f;
		MiniRectangle.bottom = MiniRectangle.top + height - 2.0f;
		::cD2DRenderer::GetInstance().GetRenderTarget()->FillRectangle(MiniRectangle,
			::cD2DRenderer::GetInstance().GetRedBrush());
	}

	/// 텍스트 타이틀 출력
	::D2D1_RECT_F MiniMapTitle;	
	MiniMapTitle.bottom = MiniMapOutline.top + 1.0f;
	MiniMapTitle.top = MiniMapTitle.bottom - 20.0f;
	MiniMapTitle.left = MiniMapOutline.left + 10.0f;
	MiniMapTitle.right = MiniMapOutline.right;

	if (::cResourceManager::GetInstance().getUIBitMap(UIID::MAP_TAG) != nullptr){
		::D2D1_RECT_F dxArea
			= { MiniMapTitle.left, MiniMapTitle.top,
			MiniMapTitle.right,
			MiniMapTitle.bottom };
		::D2D1_RECT_F srcArea
			= { 0, 0, ::cResourceManager::GetInstance().getUISize(UIID::MAP_TAG).x - 10.0f,
			::cResourceManager::GetInstance().getUISize(UIID::MAP_TAG).y };

		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawBitmap(::cResourceManager::GetInstance().getUIBitMap(UIID::MAP_TAG),
			dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}

	if (::cResourceManager::GetInstance().getUIBitMap(UIID::MAP_L_BORDER) != nullptr){
		::D2D1_RECT_F dxArea
			= { MiniMapOutline.left, MiniMapOutline.top,
			MiniMapOutline.right,
			MiniMapOutline.bottom };
		::D2D1_RECT_F srcArea
			= { 0, 0, ::cResourceManager::GetInstance().getUISize(UIID::MAP_L_BORDER).x,
			::cResourceManager::GetInstance().getUISize(UIID::MAP_L_BORDER).y };

		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawBitmap(::cResourceManager::GetInstance().getUIBitMap(UIID::MAP_L_BORDER),
			dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}
	
}