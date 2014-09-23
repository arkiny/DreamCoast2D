#include "stdafx.h"
#include "uTile.h"
#include "uCamera.h"
#include "VECTOR2D.h"
#include "uSprite.h"
#include "cD2DRenderer.h"

uTile::uTile()
{
	m_Cam = nullptr;
	_type = 0;	
}

uTile::uTile(int type, uCamera* const in){	
	_type = type;
	m_Cam = in;
}


uTile::~uTile()
{
}

void uTile::renderTile(float x, float y, cD2DRenderer& renderer, 
	uSprite* m_spriteAtlas, ID2D1Bitmap* m_ipD2DBitmap){
	VECTOR2D tilePos(x, y);
	// debug
	switch (_type){
	case 0:
		m_spriteAtlas->pickSpriteAtlas(0.0f, 0.0f, 90.0f, 45.0f, 0);
		break;
	case 1:
		m_spriteAtlas->pickSpriteAtlas(100.0f, 0.0f, 90.0f, 45.0f, 0);
		break;
	case 2:
		m_spriteAtlas->pickSpriteAtlas(200.0f, 0.0f, 90.0f, 62.0f, 0);
		break;
	case 3:
		// offsetY = -((높이 - 원래타일높이) / 2)
		m_spriteAtlas->pickSpriteAtlas(0.0f, 80.0f, 90.0f, 162.0f, 0.0f, -58.5f, 0);
		break;
	default:
		m_spriteAtlas->pickSpriteAtlas(0.0f, 0.0f, 90.0f, 45.0f, 0);
		break;
	}
	hRender(renderer, m_Cam->translasteToScreen(&tilePos), m_spriteAtlas, m_ipD2DBitmap);
}

void uTile::hRender(cD2DRenderer& renderer, VECTOR2D tilePos, 
	uSprite* m_spriteAtlas, ID2D1Bitmap* m_ipD2DBitmap){
	if (m_ipD2DBitmap != nullptr){

		// Pivot 이미지의 한가운데 바닥 -> dxArea에서 지정
		::D2D1_RECT_F dxArea
			= m_spriteAtlas->getCoordinateFromPivotCenter(tilePos);

		//	
		::D2D1_RECT_F srcArea
			= m_spriteAtlas->getSrcFrameFromSprite();

		renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);

		//회전등에 필요한 부분
		//renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());	
	}
}