#include "stdafx.h"
#include <math.h>
#include "cD2DRenderer.h"
#include "VECTOR2D.h"
#include "uSprite.h"
#include "wTileMap.h"
#include "mIObject.h"

wTileMap::wTileMap()
{	
	m_player = nullptr;
	m_ipD2DBitmap = nullptr;

	//임시로 타일맵 중앙에 배치
	m_spriteAtlas = new uSprite();

	_vertical = 14.0f;
	_horizontal = 14.0f;
	_RectTileWidth = 45.0f;
	_RectTileHeight = 45.0f;
	
	_cameraX = 514.0f;
	_cameraY = _RectTileHeight;

	mapSize.left = _cameraX - ((_RectTileWidth * _horizontal));
	mapSize.right = _cameraX + ((_RectTileWidth * _horizontal));
	mapSize.top = _cameraY - (_RectTileHeight / 2.0f);	
	mapSize.bottom = _cameraY + ((_RectTileHeight * _vertical) - (_RectTileHeight/2.0f));
	
	//debug및 테스트용 코드
	for (int i = 0; i < 14; i++){
		for (int j = 0; j < 14; j++){
			m_mapinfo[i][j] = 0;
		}
	}

	for (int i = 0; i < 14; i++){
		m_mapinfo[i][0] = 2;
	}
	
	for (int i = 0; i < 14; i++){
		m_mapinfo[0][i] = 2;
	}

	for (int i = 0; i < 14; i++){
		m_mapinfo[13][i] = 2;
	}
	
	for (int i = 0; i < 14; i++){
		m_mapinfo[i][13] = 2;
	}
	m_mapinfo[3][5] = 2;
	m_mapinfo[4][8] = 2;
	m_mapinfo[11][3] = 3;
	m_mapinfo[12][12] = 3;
	m_mapinfo[6][1] = 2;
	//
}

wTileMap::~wTileMap()
{
	SafeRelease(m_ipD2DBitmap);
	if (m_spriteAtlas != NULL){
		delete m_spriteAtlas;
	}
}

void wTileMap::onInit(cD2DRenderer& renderer){
	HWND hWnd = renderer.GetHwnd();
	m_ipD2DBitmap = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/maptile.png", NULL);
}

void wTileMap::onUpdate(float fdeltatime){	
	m_player->onUpdate(fdeltatime);
}

void wTileMap::onRender(cD2DRenderer& renderer){
	// debug
	renderer.GetRenderTarget()->DrawRectangle(mapSize, renderer.GetBrush());
	//
	renderMap(renderer);	
	m_player->onRender(renderer);
}

void wTileMap::setPlayer(mIObject* p){
	m_player = p;
}

void wTileMap::hRender(cD2DRenderer& renderer, VECTOR2D tilePos){
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

void wTileMap::renderTile(float x, float y, int type, cD2DRenderer& renderer){
	VECTOR2D tilePos(x, y);
	// debug
	switch (type){
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
	wTileMap::hRender(renderer, tilePos);	
}

void wTileMap::renderMap(cD2DRenderer& renderer){
	VECTOR2D pt;
	float x, y;
	int type = 0;
	bool onTilecheck = false;

	VECTOR2D test = getTileCoordinates(*m_player->getPos());

	for (int j = 0; j < _vertical; j++){
		for (int i = 0; i < _horizontal; i++){
			x = j*_RectTileWidth;
			y = i*_RectTileHeight;
			VECTOR2D in(x, y);

			pt = twoDtoISO(in);

			// 플레이어가 타일위에 있을때 
			if (test.x == i && test.y == j){
				type = 1;
				//
				//onTilecheck = true;
				//
			}
			else {
				type = m_mapinfo[i][j];
			}

			renderTile(pt.x, pt.y, type, renderer);
			// 오더링 타일 뒤에 플레이어 숨기도록 해당 타일위에 있을때에 렌더하게 한다.
			// Todo: 매번 업데이트 할 필요 없도록 미리 계산해놓도록?
			// 이러면 타일을 넘어가게 될경우 캐릭터 렌더가 다음 타일에 가려버리게 되는데...
			//if (onTilecheck) {
			//	m_player->onRender(renderer);
			//	onTilecheck = false;
			//}
			//
		}
	}
}

VECTOR2D wTileMap::twoDtoISO(VECTOR2D in){
	VECTOR2D ret = VECTOR2D(
		((in.x - in.y) + _cameraX), ((in.x + in.y) / 2) + _cameraY);
	return ret;
}

VECTOR2D wTileMap::getTileCoordinates(VECTOR2D in){
	VECTOR2D temp(0.0f, 0.0f);
	float x = (((2.0f * in.y) - _cameraY) - (in.x - _cameraX)) / 2.0f; 
	float y = (((2.0f * in.y) - _cameraY) + (in.x - _cameraX)) / 2.0f;

	temp.x = floorf(x / _RectTileWidth);
	temp.y = floorf(y / _RectTileHeight);

	return temp;
}