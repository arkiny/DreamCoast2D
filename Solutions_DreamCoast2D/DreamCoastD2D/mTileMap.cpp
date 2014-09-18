#include "stdafx.h"
#include "cD2DRenderer.h"
#include "VECTOR2D.h"
#include "uSprite.h"
#include "mTileMap.h"

mTileMap::mTileMap()
{	
	m_ipD2DBitmap = nullptr;
	//임시로 중앙에 대기
	_posVector = new VECTOR2D(514.0f, 384.0f);
	m_spriteAtlas = new uSprite();

	_vertical = 15.0f;
	_horizontal = 15.0f;
	_RectTileWidth = 45.0f;
	_RectTileHeight = 45.0f;

	_cameraX = _RectTileWidth * _vertical;
	_cameraY = _RectTileHeight;	
}



mTileMap::~mTileMap()
{
	SafeRelease(m_ipD2DBitmap);
	if (_posVector != NULL){
		delete _posVector;
	}
	if (m_spriteAtlas != NULL){
		delete m_spriteAtlas;
	}
}

void mTileMap::onInit(cD2DRenderer& renderer){
	HWND hWnd = renderer.GetHwnd();
	m_ipD2DBitmap = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/maptile.png", NULL);
}
void mTileMap::onUpdate(float fdeltatime){	
}

void mTileMap::onRender(cD2DRenderer& renderer){
	renderMap(renderer);
}

void mTileMap::renderTile(float x, float y, int type, cD2DRenderer& renderer){
	float drawWidth = _RectTileWidth;
	float drawHeight = _RectTileHeight / 2;
	VECTOR2D tilePos(x, y);

	switch (type){
	case 0:
		m_spriteAtlas->pickSpriteAtlas(0.0f, 0.0f, 90.0f, 45.0f, 0);

		if (m_ipD2DBitmap != nullptr){

			// Pivot 이미지의 한가운데 바닥 -> dxArea에서 지정
			::D2D1_RECT_F dxArea
				= m_spriteAtlas->getCoordinateFromPivot(tilePos);

			//	
			::D2D1_RECT_F srcArea
				= m_spriteAtlas->getSrcFrameFromSprite();

			renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);

			//회전등에 필요한 부분
			//renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
		}

		break;
	default:
		m_spriteAtlas->pickSpriteAtlas(0.0f, 0.0f, 90.0f, 45.0f, 0);

		if (m_ipD2DBitmap != nullptr){

			// Pivot 이미지의 한가운데 바닥 -> dxArea에서 지정
			::D2D1_RECT_F dxArea
				= m_spriteAtlas->getCoordinateFromPivot(tilePos);

			//	
			::D2D1_RECT_F srcArea
				= m_spriteAtlas->getSrcFrameFromSprite();

			renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);

			//회전등에 필요한 부분
			//renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
		}
		break;
	}
}

void mTileMap::renderMap(cD2DRenderer& renderer){
	VECTOR2D pt;
	float x, y;

	for (int j = 0; j < _vertical; j++){
		for (int i = 0; i < _horizontal; i++){
			x = j*_RectTileWidth;
			y = i*_RectTileHeight;
			VECTOR2D in(x, y);

			pt = twoDtoISO(in);

			renderTile(pt.x, pt.y, 0, renderer);
			//drawTile(x, y, 1, hdc);
		}
	}
}

VECTOR2D mTileMap::twoDtoISO(VECTOR2D in){
	VECTOR2D ret = VECTOR2D(
		(in.x - in.y + _cameraX), ((in.x + in.y)/2) + _cameraY);
	return ret;
}