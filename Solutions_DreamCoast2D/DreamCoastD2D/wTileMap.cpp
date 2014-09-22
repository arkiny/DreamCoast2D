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

	//�ӽ÷� Ÿ�ϸ� �߾ӿ� ��ġ
	m_spriteAtlas = new uSprite();

	//_vertical = 14.0f;
	//_horizontal = 14.0f;
	_RectTileWidth = 45.0f;
	_RectTileHeight = 45.0f;
	
	// offset ����
	_offsetX = 514.0f;
	_offsetY = _RectTileHeight;
	
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

	// alpha��, �ɼǿ� ���� Ű�� ���� �ֵ��� ���߿� ����
	//m_player->onRender(renderer, true);
}

void wTileMap::setPlayer(mIObject* p){
	m_player = p;
}

void wTileMap::hRender(cD2DRenderer& renderer, VECTOR2D tilePos){
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
		// offsetY = -((���� - ����Ÿ�ϳ���) / 2)
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

	// get real pos
	VECTOR2D test = getTileCoordinates(*m_player->getRealPos());
	VECTOR2D test2 = getTileCoordinates(*m_player->getPos());


	for (int j = 0; j < _vertical; j++){
		for (int i = 0; i < _horizontal; i++){
			x = j*_RectTileWidth;
			y = i*_RectTileHeight;
			VECTOR2D in(x, y);

			pt = twoDtoISO(in);

			// �÷��̾ Ÿ������ ������ 
			if (test.x == i && test.y == j){
				type = 1;				
				onTilecheck = true;				
			}
			else {
				type = m_vMapinfo[i+j*static_cast<int>(_vertical)];
			}

			if (test2.x == i && test2.y == j){
				onTilecheck = true;
			}

			renderTile(pt.x, pt.y, type, renderer);
			// ������ Ÿ�� �ڿ� �÷��̾� ���⵵�� �ش� Ÿ������ �������� �����ϰ� �Ѵ�.
			// Todo: �Ź� ������Ʈ �� �ʿ� ������ �̸� ����س�����?
			// �̷��� Ÿ���� �Ѿ�� �ɰ�� ĳ���� ������ ���� Ÿ�Ͽ� ���������� �Ǵµ�...
			if (onTilecheck) {
				m_player->onRender(renderer);
				onTilecheck = false;
			}
			//
		}
	}
}

VECTOR2D wTileMap::twoDtoISO(VECTOR2D in){
	VECTOR2D ret = VECTOR2D(
		((in.x - in.y) + _offsetX), ((in.x + in.y) / 2) + _offsetY);
	return ret;
}

VECTOR2D wTileMap::getTileCoordinates(VECTOR2D in){
	VECTOR2D temp(0.0f, 0.0f);
	float x = (((2.0f * in.y) - _offsetY) - (in.x - _offsetX)) / 2.0f; 
	float y = (((2.0f * in.y) - _offsetY) + (in.x - _offsetX)) / 2.0f;

	temp.x = floorf(x / _RectTileWidth);
	temp.y = floorf(y / _RectTileHeight);

	return temp;
}

void wTileMap::setTile(float x, float y, int type){
	int nx = static_cast<int>(x);
	int ny = static_cast<int>(y);
	m_vMapinfo[(static_cast<int>(_vertical)*ny) + nx] = type;
}

void wTileMap::setSize(float horizontal, float vertical){
	_horizontal = horizontal;
	_vertical = vertical;

	for (int i = 0; i < _horizontal * _vertical; i++){
		m_vMapinfo.push_back(0);
	}
	
	//debug�� �׽�Ʈ�� �ڵ�
	for (int i = 0; i < 14; i++){
		setTile(static_cast<float>(i), 0.0f, 2);
	}

	for (int i = 0; i < 14; i++){
		setTile(0.0f, static_cast<float>(i), 2);
	}

	for (int i = 0; i < 14; i++){
		setTile(13.0f, static_cast<float>(i), 2);
	}

	for (int i = 0; i < 14; i++){
		setTile(static_cast<float>(i), 13.0f, 2);
	}

	//
	setTile(3.0f, 5.0f, 2);
	setTile(4.0f, 8.0f, 2);
	setTile(11.0f, 3.0f, 3);
	setTile(12.0f, 12.0f, 3);
	setTile(6.0f, 1.0f, 2);	
	//


	mapSize.left = _offsetX - ((_RectTileWidth * _horizontal));
	mapSize.right = _offsetX + ((_RectTileWidth * _horizontal));
	mapSize.top = _offsetY - (_RectTileHeight / 2.0f);
	mapSize.bottom = _offsetY + ((_RectTileHeight * _vertical) - (_RectTileHeight / 2.0f));
}