#include "stdafx.h"
#include "mBuilding.h"
#include "uCamera.h"
#include "uSprite.h"
#include "cD2DRenderer.h"
#include "cResourceManager.h"
#include "VECTOR2D.h"

mBuilding::mBuilding()
{
	m_nBuildingType = 0;
	m_cpos = nullptr;
	m_cam = nullptr;
}

mBuilding::mBuilding(int buildingtype, VECTOR2D* cpos, uCamera* cam){
	m_nBuildingType = buildingtype;
	m_cpos = cpos;
	
	if (cam != NULL){
		m_cam = new uCamera(*cam);
	}
	m_sprite = new uSprite;

	/*m_sprite->pickSpriteAtlas(100.0f, 80.0f, 275.0f, 287.0f, -75.0f, -75.0f, 0);*/ // to 남서
	//m_sprite->pickSpriteAtlas(100.0f, 80.0f, 275.0f, 287.0f, 2.0f, -110.0f, 0);//정북	
	//m_sprite->pickSpriteAtlas(100.0f, 80.0f, 275.0f, 287.0f, +2.0f, -30.0f, 0); // 정남
	//m_sprite->pickSpriteAtlas(100.0f, 80.0f, 275.0f, 287.0f, +20.0f, -30.0f, 0);//정남
	/*m_sprite->pickSpriteAtlas(100.0f, 80.0f, 275.0f, 287.0f, 94.0f, 73.0f, 0);*/
	if (buildingtype == 0){
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getMapSpriteInfo(1, 0)->x,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 0)->y,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 0)->width,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 0)->height,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 0)->offsetX,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 0)->offsetY,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 0)->maxFrame);
		//m_sprite->pickSpriteAtlas(100.0f, 80.0f, 275.0f, 287.0f, +60.0f, -100.0f, 0);
	}
	else if (buildingtype == 1){
		//m_sprite->pickSpriteAtlas(0.0f, 80.0f, 90.0f, 162.0f, 0.0f, -58.0f, 0);
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getMapSpriteInfo(1, 1)->x,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 1)->y,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 1)->width,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 1)->height,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 1)->offsetX,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 1)->offsetY,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 1)->maxFrame);
	}
	else if (buildingtype == 2){
		//m_sprite->pickSpriteAtlas(200.0f, 0.0f, 90.0f, 62.0f, 0.0f, -9.0f, 0);
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getMapSpriteInfo(1, 2)->x,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 2)->y,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 2)->width,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 2)->height,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 2)->offsetX,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 2)->offsetY,
			cResourceManager::GetInstance().getMapSpriteInfo(1, 2)->maxFrame);
	}
	
}

mBuilding::~mBuilding()
{
	if (m_cpos != NULL){
		delete m_cpos;
	}	
	if (m_sprite != NULL){
		delete m_sprite;
	}
}

void mBuilding::update(float delta){
	//todo later
}

POINTFLOAT mBuilding::getPos(){
	POINTFLOAT ret = { m_cpos->x, m_cpos->y };
	return ret;
}


void mBuilding::setCam(uCamera* in) { 
	//if (m_cam != NULL){
	//	delete m_cam;
	//}	
	m_cam = new uCamera(*in);
}
void mBuilding::render(){
	if (cResourceManager::GetInstance().getTileMapBitMap() != nullptr){
		VECTOR2D cpos = m_cam->translasteToScreen(m_cpos);
		// Pivot 이미지의 한가운데 바닥 -> dxArea에서 지정
		::D2D1_RECT_F dxArea
			= m_sprite->getCoordinateFromPivotCenter(cpos);

		//	
		::D2D1_RECT_F srcArea
			= m_sprite->getSrcFrameFromSprite();

		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawBitmap(cResourceManager::GetInstance().getTileMapBitMap(), 
			dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);

		//회전등에 필요한 부분
		//renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());	
	}
}
