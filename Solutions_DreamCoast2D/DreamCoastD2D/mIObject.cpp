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

		// Pivot �̹����� �Ѱ�� �ٴ� -> dxArea���� ����
		::D2D1_RECT_F dxArea
			= m_spriteAtlas->getCoordinateFromPivot(*_posVector);

		//	
		::D2D1_RECT_F srcArea
			= m_spriteAtlas->getSrcFrameFromSprite();

		renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);

		//ȸ��� �ʿ��� �κ�
		//renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	}
}