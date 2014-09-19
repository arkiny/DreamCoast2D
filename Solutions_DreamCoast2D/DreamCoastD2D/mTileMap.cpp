#include "stdafx.h"
#include <math.h>
#include "cD2DRenderer.h"
#include "VECTOR2D.h"
#include "uSprite.h"
#include "mTileMap.h"


mTileMap::mTileMap()
{	
	//m_player = nullptr;
	m_ipD2DBitmap = nullptr;
	//임시로 타일맵 중앙에 배치
	_posVector = new VECTOR2D(514.0f, 384.0f);
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
	
	//_cameraY - (_RectTileHeight / 2.0f);
	//_cameraY + ((_RectTileHeight * _vertical) / 2.0f) 
		//+ (_RectTileHeight / 2.0f);
	
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
	
	//
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
	// debug
	renderer.GetRenderTarget()->DrawRectangle(mapSize, renderer.GetBrush());
	//
	renderMap(renderer);	
}

void mTileMap::setPlayer(mIObject* p){
	m_player = p;
}

void mTileMap::hRender(cD2DRenderer& renderer, VECTOR2D tilePos){
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

void mTileMap::renderTile(float x, float y, int type, cD2DRenderer& renderer){
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
	default:
		m_spriteAtlas->pickSpriteAtlas(0.0f, 0.0f, 90.0f, 45.0f, 0);
		break;
	}
	mTileMap::hRender(renderer, tilePos);
	
}

void mTileMap::renderMap(cD2DRenderer& renderer){
	VECTOR2D pt;
	float x, y;
	int type = 0;
	VECTOR2D test = getTileCoordinates(*m_player->getPos());

	for (int j = 0; j < _vertical; j++){
		for (int i = 0; i < _horizontal; i++){
			x = j*_RectTileWidth;
			y = i*_RectTileHeight;
			VECTOR2D in(x, y);

			pt = twoDtoISO(in);

			
			if (test.x == i && test.y == j){
				type = 1;
			}
			else {
				type = m_mapinfo[i][j];
			}

			//if (mTileMap::isInISOTile(*m_player->getPos(), screen)){
			//	type = 1;
			//} else{
			//	type = 0;
			//}

			renderTile(pt.x, pt.y, type, renderer);
			//drawTile(x, y, 1, hdc);
		}
	}
}

VECTOR2D mTileMap::twoDtoISO(VECTOR2D in){
	VECTOR2D ret = VECTOR2D(
		((in.x - in.y) + _cameraX), ((in.x + in.y) / 2) + _cameraY);
	return ret;
}

VECTOR2D mTileMap::getTileCoordinates(VECTOR2D in){
	/*var tileY = ((mouseY * 2) - ((gridSize*tileWidth) / 2) + mouseX) / 2;
	var tileX = mouseX - tileY;
	tileY = Math.round(tileY / tileHeight);
	tileX = Math.round(tileX / tileHeight);*/

	VECTOR2D temp(0.0f, 0.0f);

	/*float tileY = ((in.y * 2.0f) - (_RectTileWidth*_vertical) + in.x) / 2.0f;
	float tileX = in.x - tileY;
	tileY = roundf(tileY / _RectTileHeight);
	tileX = roundf(tileX / _RectTileHeight);
	temp.x = tileX;
	temp.y = tileY;*/
	float x = (((2.0f * in.y) - _cameraY) - (in.x - _cameraX)) / 2.0f; 
	float y = (((2.0f * in.y) - _cameraY) + (in.x - _cameraX)) / 2.0f;

	temp.x = floorf(x / _RectTileWidth);
	temp.y = floorf(y / _RectTileHeight);

	return temp;
}


//BOOL mTileMap::isInISOTile(VECTOR2D cur, VECTOR2D tilepos){
//	float x = tilepos.y * _RectTileWidth;
//	float y = tilepos.x * _RectTileHeight;
//	VECTOR2D pt = twoDtoISO(VECTOR2D(x, y));
//	float m = 0.5f;
//		
//	::D2D1_RECT_F tileArea = {
//		pt.x - _RectTileWidth,
//		pt.y - (_RectTileHeight / 2),
//		pt.x + _RectTileWidth,
//		pt.y + (_RectTileHeight / 2) };
//
//	POINTFLOAT left = { tileArea.left, (tileArea.top + ((tileArea.bottom - tileArea.top) / 2)) };
//	POINTFLOAT top = { (tileArea.left + ((tileArea.right - tileArea.left) / 2)), tileArea.top };
//	POINTFLOAT right = { tileArea.right, (tileArea.top + ((tileArea.bottom - tileArea.top) / 2)) };
//	POINTFLOAT bottom = { (tileArea.left + ((tileArea.right - tileArea.left) / 2)), tileArea.bottom };
//
//	float l1 = left.y + (m*left.x); // 왼쪽 위 구별용
//	float l2 = top.y + (-m*top.x); // 오른쪽 위 구별용
//	float l3 = right.y + (m*right.x); // 왼쪽 아래 구별용
//	float l4 = bottom.y + (-m*bottom.x); // 오른쪽 아래 구별용
//
//	float r1 = -m * cur.x - cur.y + l1;
//	float r2 = m * cur.x - cur.y + l2;
//	float r3 = -m * cur.x - cur.y + l3;
//	float r4 = m * cur.x - cur.y + l4;
//
//	if (r1 <= 0.0f && r2 <= 0.0f && r3 >= 0.0f && r4 >= 0.0f){
//		return true;
//	}
//	else {
//		return false;
//	}
//}