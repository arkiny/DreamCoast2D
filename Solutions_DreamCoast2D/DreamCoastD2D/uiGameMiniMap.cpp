#include "stdafx.h"
#include "uiGameMiniMap.h"
#include "cD2DRenderer.h"
#include "wTileMap.h"
#include "VECTOR2D.h"
#include "uTile.h"
#include "mIObject.h"

uiGameMiniMap::uiGameMiniMap()
{
	m_pTileMap = nullptr;
}


uiGameMiniMap::~uiGameMiniMap()
{
}

uiGameMiniMap::uiGameMiniMap(wTileMap* ptileMap){
	m_pTileMap = ptileMap;
}

void uiGameMiniMap::OnInit(cD2DRenderer& renderer){

}

void uiGameMiniMap::Update(float delta){

}

void uiGameMiniMap::Render(cD2DRenderer& renderer){

	// todo: �Լ�ȭ �ؼ� �����°� ���߿�... ��Ʈ������ �׸��� �ɶ�...
	// todo: option�� ���� ũ�� ����ȭ
	::D2D1_RECT_F MiniMapOutline;
	::RECT winRect;
	GetClientRect(renderer.GetHwnd(), &winRect);
	MiniMapOutline.top = winRect.top + 20.0f;
	MiniMapOutline.bottom = winRect.top + 220.0f;
	MiniMapOutline.left = winRect.right - 220.0f;
	MiniMapOutline.right = winRect.right - 20.0f;

	renderer.GetRenderTarget()->FillRectangle(MiniMapOutline,
		renderer.GetWhiteBrush());
	renderer.GetRenderTarget()->DrawRectangle(MiniMapOutline,
		renderer.GetBrush());
	
	float height = (MiniMapOutline.bottom - MiniMapOutline.top) 
		/ m_pTileMap->getMapLimit().y;

	float width = (MiniMapOutline.right - MiniMapOutline.left)
		/ m_pTileMap->getMapLimit().x;

	::D2D1_RECT_F MiniRectangle;
	for (int j = 0; j < m_pTileMap->getMapLimit().y; j++){
		for (int i = 0; i < m_pTileMap->getMapLimit().x; i++){
			MiniRectangle.left = MiniMapOutline.left + (width* static_cast<float>(i));
			MiniRectangle.right = MiniRectangle.left + width;
			MiniRectangle.top = MiniMapOutline.top + (height* static_cast<float>(j));
			MiniRectangle.bottom = MiniRectangle.top + height;
			
			if (m_pTileMap->getMapinfo(j, i) == 0){
				renderer.GetRenderTarget()->FillRectangle(MiniRectangle,
					renderer.GetWhiteBrush());
			}
			else {
				renderer.GetRenderTarget()->FillRectangle(MiniRectangle,
					renderer.GetBrush());
			}
			renderer.GetRenderTarget()->DrawRectangle(MiniRectangle,
				renderer.GetBrush());
		}
	}

	// player ��ġ ���
	MiniRectangle.left = MiniMapOutline.left + (width* m_pTileMap->getPlayerTilePos().y) + 1.0f;
	MiniRectangle.right = MiniRectangle.left + width - 2.0f;
	MiniRectangle.top = MiniMapOutline.top + (height* m_pTileMap->getPlayerTilePos().x) + 1.0f;
	MiniRectangle.bottom = MiniRectangle.top + height - 2.0f;
	renderer.GetRenderTarget()->FillRectangle(MiniRectangle,
		renderer.GetGreenBrush());

	VECTOR2D pt(0.0f, 0.0f);
	for (mIObject* x : m_pTileMap->getMobList()){
		pt = m_pTileMap->getTileCoordinates(*(x->getDrawPos()));

		MiniRectangle.left = MiniMapOutline.left + (width* pt.y) + 1.0f;
		MiniRectangle.right = MiniRectangle.left + width - 2.0f;
		MiniRectangle.top = MiniMapOutline.top + (height* pt.x) + 1.0f;
		MiniRectangle.bottom = MiniRectangle.top + height - 2.0f;
		renderer.GetRenderTarget()->FillRectangle(MiniRectangle,
			renderer.GetRedBrush());
	}

	/// �ؽ�Ʈ Ÿ��Ʋ ���
	::D2D1_RECT_F MiniMapTitle;	
	MiniMapTitle.bottom = MiniMapOutline.top;
	MiniMapTitle.top = MiniMapTitle.bottom - 20.0f;
	MiniMapTitle.left = MiniMapOutline.left;
	MiniMapTitle.right = MiniMapOutline.right;
	renderer.GetRenderTarget()->FillRectangle(MiniMapTitle,
		renderer.GetWhiteBrush());
	renderer.GetRenderTarget()->DrawRectangle(MiniMapTitle,
		renderer.GetBrush());
	wchar_t* wszText_ = new wchar_t[20];
	swprintf(wszText_, 20, L"Minimap Area");
	UINT32 cTextLength_ = (UINT32)wcslen(wszText_);
	renderer.GetRenderTarget()->DrawTextW(
		wszText_,
		cTextLength_,
		renderer.GetTextFormat(),
		MiniMapTitle,
		renderer.GetBrush());
	
}