#include "stdafx.h"
#include "uTile.h"
#include "uCamera.h"
#include "VECTOR2D.h"
#include "uSprite.h"
#include "cD2DRenderer.h"
#include "miObject.h"

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
		// offsetY = -((���� - ����Ÿ�ϳ���) / 2)
		m_spriteAtlas->pickSpriteAtlas(0.0f, 80.0f, 90.0f, 162.0f, 0.0f, -58.5f, 0);
		break;
	default:
		m_spriteAtlas->pickSpriteAtlas(0.0f, 0.0f, 90.0f, 45.0f, 0);
		break;
	}

	hRender(renderer, m_Cam->translasteToScreen(&tilePos), m_spriteAtlas, m_ipD2DBitmap);
	mIObject* ptr = nullptr;
	while (!m_vObjects.empty()){
		ptr = m_vObjects.back();
		m_vObjects.pop_back();
		ptr->onRender(renderer);
	}
}

void uTile::hRender(cD2DRenderer& renderer, VECTOR2D tilePos, 
	uSprite* m_spriteAtlas, ID2D1Bitmap* m_ipD2DBitmap){
	if (m_ipD2DBitmap != nullptr){

		// Pivot �̹����� �Ѱ�� �ٴ� -> dxArea���� ����
		::D2D1_RECT_F dxArea
			= m_spriteAtlas->getCoordinateFromPivotCenter(tilePos);

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

void uTile::addObject(mIObject* in){
	m_vObjects.push_back(in);
}

void uTile::onHit(float dmg){
	for (mIObject* obj : m_vObjects){
		obj->getHit(dmg);
	}
}