#include "stdafx.h"
#include "uTile.h"
#include "uCamera.h"
#include "VECTOR2D.h"
#include "uSprite.h"
#include "cD2DRenderer.h"
#include "IMapObject.h"

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
	m_Cam = nullptr;
	m_vObjects.clear();
	m_qMapObject.clear();
}

void uTile::renderTile(float x, float y, 
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
		m_spriteAtlas->pickSpriteAtlas(0.0f, 80.0f, 90.0f, 162.0f, 0.0f, -58.0f, 0);
		break;
	case 4:
		// 일반 타일로 깔아주고 위에 오브젝트 올리기
		m_spriteAtlas->pickSpriteAtlas(100.0f, 80.0f, 275.0f, 287.0f, 2.0f, -119.0f, 0);
		break;
	default:
		m_spriteAtlas->pickSpriteAtlas(0.0f, 0.0f, 90.0f, 45.0f, 0);
		break;
	}
	VECTOR2D _camtile = m_Cam->translasteToScreen(&tilePos);

	// 카메라 안의 만큼 짤라서 출력
	// todo : 현재 타일의 크기는 절대값으로 되어 있지만, 차후 동적으로 치환
	// 문제 : 2칸이상 크기의 타일 일경우 갑자기 출력되는 문제가 있다.
	// 해결책 : 2칸 이상의 타일을 만들경우, 해당 타일에 맞게 자르기를 재수정
	// Idea Contributed by hero
	// thanks to hero
	if (_camtile.x < (0 - 45.0f) || _camtile.y < (0 - 45.0f) ||
		_camtile.x > (m_Cam->getScreenW() + 45.0f) ||
		_camtile.y > (m_Cam->getScreenH())+ 45.0f){
		//do nothing
	}
	else {
		hRender(m_Cam->translasteToScreen(&tilePos), m_spriteAtlas, m_ipD2DBitmap);
	}

	ICharacter* ptr = nullptr;
	while (!m_vObjects.empty()){
		ptr = m_vObjects.back();
		m_vObjects.pop_back();
		_camtile = m_Cam->translasteToScreen(ptr->getDrawPos());
		if (_camtile.x < (0 - 45.0f)|| _camtile.y < (0 - 45.0f) ||
			_camtile.x > (m_Cam->getScreenW() + 45.0f) ||
			_camtile.y > (m_Cam->getScreenH() + 45.0f)){
			// do nothing
		}
		else {
			ptr->onRender();
		}
	}
}

void uTile::hRender(VECTOR2D tilePos, 
	uSprite* m_spriteAtlas, ID2D1Bitmap* m_ipD2DBitmap){
	if (m_ipD2DBitmap != nullptr){

		// Pivot 이미지의 한가운데 바닥 -> dxArea에서 지정
		::D2D1_RECT_F dxArea
			= m_spriteAtlas->getCoordinateFromPivotCenter(tilePos);

		//	
		::D2D1_RECT_F srcArea
			= m_spriteAtlas->getSrcFrameFromSprite();

		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);

		//회전등에 필요한 부분
		//renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());	
	}
}

void uTile::renderMapObject(float x, float y){
	IMapObject* ptr;
	while (!m_qMapObject.empty()){
		ptr = m_qMapObject.back();
		//m_qMapObject.pop_back();
		//_camtile = m_Cam->translasteToScreen(ptr->getDrawPos());
		//if (_camtile.x < (0 - 45.0f) || _camtile.y < (0 - 45.0f) ||
		//	_camtile.x >(m_Cam->getScreenW() + 45.0f) ||
		//	_camtile.y >(m_Cam->getScreenH() + 45.0f)){
		//	// do nothing
		//}
		//else {
		ptr->render();
		//}
		m_qMapObject.pop_back();
	}
}

void uTile::addObject(ICharacter* in){
	m_vObjects.push_back(in);
}

//
void uTile::addMapObject(IMapObject* in){
	m_qMapObject.push_back(in);
}
//

void uTile::onHit(float dmg){
	for (ICharacter* obj : m_vObjects){
		obj->getHit(dmg);
	}
}