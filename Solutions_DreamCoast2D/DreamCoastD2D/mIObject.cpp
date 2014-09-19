#include "stdafx.h"
#include "cD2DRenderer.h"
#include "mIObject.h"
#include "VECTOR2D.h"
#include "uSprite.h"

mIObject::~mIObject()
{
}

void mIObject::onRender(cD2DRenderer& renderer){
	if (m_ipD2DBitmap != nullptr){

		// Pivot 이미지의 한가운데 바닥 -> dxArea에서 지정
		::D2D1_RECT_F dxArea
			= m_spriteAtlas->getCoordinateFromPivot(*_posVector);

		//	
		::D2D1_RECT_F srcArea
			= m_spriteAtlas->getSrcFrameFromSprite();

		renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);

		//회전등에 필요한 부분
		//renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());

		//debug 용
		renderer.GetRenderTarget()->DrawRectangle(dxArea, renderer.GetBrush());
		::D2D1_RECT_F pivotArea;
		pivotArea.top = _posVector->y - 2.0f;
		pivotArea.bottom = _posVector->y + 2.0f;
		pivotArea.left = _posVector->x - 2.0f;
		pivotArea.right = _posVector->x + 2.0f;
		renderer.GetRenderTarget()->DrawRectangle(pivotArea, renderer.GetBrush());
	}	
}