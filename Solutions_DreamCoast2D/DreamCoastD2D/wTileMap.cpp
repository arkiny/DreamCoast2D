#include "stdafx.h"
#include <math.h>
#include "cD2DRenderer.h"
#include "VECTOR2D.h"
#include "uSprite.h"
#include "wTileMap.h"
#include "mIObject.h"
#include "uCamera.h"
#include "mMonster.h"
#include "uTile.h"

wTileMap::wTileMap()
{	
	m_player = nullptr;
	m_ipD2DBitmap = nullptr;
	m_Cam = nullptr;

	//임시로 타일맵 중앙에 배치
	m_spriteAtlas = new uSprite();

	//_vertical = 14.0f;
	//_horizontal = 14.0f;
	_RectTileWidth = 45.0f;
	_RectTileHeight = 45.0f;
	
	// offset 설정
	//_offsetX = 514.0f;
	//_offsetY = _RectTileHeight;
	
	_offsetX = 514.0f;
	_offsetY = _RectTileHeight;
}

wTileMap::~wTileMap()
{
	SafeRelease(m_ipD2DBitmap);
	if (m_spriteAtlas != NULL){
		delete m_spriteAtlas;
	}
	if (m_Cam != NULL){
		delete m_Cam;
	}
}

void wTileMap::onInit(cD2DRenderer& renderer){
	HWND hWnd = renderer.GetHwnd();
	m_ipD2DBitmap = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/maptile.png", NULL);
	m_Cam = new uCamera(1028.0, 768.0f, m_player->getRealPos());
	
	// Debug---------------------------------------------------
	VECTOR2D in(6.0f*_RectTileWidth, 8.0f*_RectTileHeight);
	VECTOR2D pt = twoDtoISO(in);
	mIObject* ptr = new mMonster(pt.x, pt.y);
	mMonster* ptr2 = (mMonster*)ptr;
	ptr2->setDir(LEFTDOWN);
	m_mobs.push_back(ptr);

	in.x = 7.0f*_RectTileWidth;
	in.y = 8.0f*_RectTileHeight;
	pt = twoDtoISO(in);
	ptr = new mMonster(pt.x, pt.y);
	ptr2 = (mMonster*)ptr;
	ptr2->setDir(RIGHTDOWN);
	m_mobs.push_back(ptr);
	
	in.x = 6.0f*_RectTileWidth;
	in.y = 7.0f*_RectTileHeight;
	pt = twoDtoISO(in);
	ptr = new mMonster(pt.x, pt.y);
	
	ptr2 = (mMonster*)ptr;
	ptr2->setDir(LEFTUP);	
	m_mobs.push_back(ptr);
	
	in.x = 7.0f*_RectTileWidth;
	in.y = 7.0f*_RectTileHeight;
	pt = twoDtoISO(in);
	pt = twoDtoISO(in);
	ptr = new mMonster(pt.x, pt.y);
	ptr2 = (mMonster*)ptr;
	ptr2->setDir(RIGHTUP);
	m_mobs.push_back(ptr);
	// Debug---------------------------------------------------
	
	ptr2 = nullptr;
	ptr = nullptr;
	for (unsigned int i = 0; i < m_mobs.size(); i++){
		m_mobs[i]->onInit(renderer);
		m_mobs[i]->setCam(m_Cam);
	}
}

void wTileMap::onUpdate(float fdeltatime){	
	mMonster* ptr;
	for (unsigned int i = 0; i < m_mobs.size(); i++){
		m_mobs[i]->onUpdate(fdeltatime);			
		//ptr = (mMonster*)m_mobs[i];

		//if (ptr->getState() == ONDEAD){
		//	delete ptr;
		//	m_mobs.erase(m_mobs.begin() + i);
		//	m_mobs.shrink_to_fit();
		//}

		// 업데이트와 동시에 포지션별로 각 타일랜더핸들러 자기 좌표에 포인터를 먹여준다.
		VECTOR2D pos = getTileCoordinates(*m_mobs[i]->getRealPos());
		::wTileMap::addObjectToTile(pos.x, pos.y, m_mobs[i]);
	}
	
	// player는 고정되어 있는 메모리이므로
	// 일단 mob들이 타일에 뿌려진 뒤에 처리를 해야한다.
	// 킄... 선공은 몬스터가 먼저인가 킄....
	m_player->onUpdate(fdeltatime);
}

void wTileMap::onRender(cD2DRenderer& renderer){
	// debug
	//renderer.GetRenderTarget()->DrawRectangle(mapSize, renderer.GetBrush());
	//
	::wTileMap::renderMap(renderer);
	// Todo: 차후 healthbar option 넣을 것
	::wTileMap::drawHealthBar(renderer, m_player);
	for (unsigned int i = 0; i < m_mobs.size(); i++){
		::wTileMap::drawHealthBar(renderer, m_mobs[i]);
	}
}

void wTileMap::drawHealthBar(cD2DRenderer& renderer, mIObject* obj){
	VECTOR2D cpos = m_Cam->translasteToScreen(obj->getDrawPos());

	::D2D1_RECT_F healthBar;
	healthBar.top = cpos.y + 2.0f;
	healthBar.bottom = cpos.y + 7.0f;
	healthBar.left = cpos.x - 30.0f;
	healthBar.right = cpos.x + 30.0f;

	::D2D1_RECT_F currentHealthbar;
	currentHealthbar.top = cpos.y + 2.0f;
	currentHealthbar.bottom = cpos.y + 7.0f;
	currentHealthbar.left = cpos.x - 30.0f;
	currentHealthbar.right = (cpos.x - 30.0f) + (obj->getHealth() / obj->getMAXHealth() * 60.0f);

	renderer.GetRenderTarget()->FillRectangle(healthBar, renderer.GetRedBrush());
	renderer.GetRenderTarget()->FillRectangle(currentHealthbar, renderer.GetGreenBrush());
	renderer.GetRenderTarget()->DrawRectangle(healthBar, renderer.GetBrush());
}

void wTileMap::setPlayer(mIObject* p){
	m_player = p;
}

void wTileMap::renderMap(cD2DRenderer& renderer){
	VECTOR2D pt;
	float x, y;
	int type = 0;
	bool onTilecheck = false;

	// get real pos
	VECTOR2D test = getTileCoordinates(*m_player->getRealPos());
	VECTOR2D test2 = getTileCoordinates(*m_player->getDrawPos());


	for (int j = 0; j < _vertical; j++){
		for (int i = 0; i < _horizontal; i++){
			x = j*_RectTileWidth;
			y = i*_RectTileHeight;
			VECTOR2D in(x, y);

			pt = twoDtoISO(in);

			// 플레이어가 타일위에 있을때 
			if (test.x == i && test.y == j){
				type = 1;				
				onTilecheck = true;				
			}
			//else {
			//	//type = m_vMapRenderHandler[i + j*static_cast<int>(_vertical)]->getType();
			//	//type = m_vMapinfo[i+j*static_cast<int>(_vertical)];
			//}

			if (test2.x == i && test2.y == j){
				onTilecheck = true;
			}

			// 타일 렌더 후 동시에 애드된 오브젝트들도 렌더
			// 렌더 이후에 오브젝트 포인터들은 팝되면서 사라진다.
			m_vMapRenderHandler[i + j*static_cast<int>(_vertical)]->
				renderTile(pt.x, pt.y, renderer, m_spriteAtlas, m_ipD2DBitmap);

			//renderTile(pt.x, pt.y, type, renderer);
			// 오더링 타일 뒤에 플레이어 숨기도록 해당 타일위에 있을때에 렌더하게 한다.
			// Todo: 매번 업데이트 할 필요 없도록 미리 계산해놓도록?
			// 이러면 타일을 넘어가게 될경우 캐릭터 렌더가 다음 타일에 가려버리게 되는데...
			if (onTilecheck) {
				m_player->onRender(renderer);
				onTilecheck = false;
			}
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
	m_vMapRenderHandler[(static_cast<int>(_vertical)*ny) + nx]->setType(type);
}

void wTileMap::setSize(float horizontal, float vertical){
	_horizontal = horizontal;
	_vertical = vertical;

	/*for (int i = 0; i < _horizontal * _vertical; i++){
		m_vMapinfo.push_back(0);
	}*/

	uTile* ptr = nullptr;
	for (int i = 0; i < _horizontal * _vertical; i++){
		ptr = new uTile(0, m_Cam);
		m_vMapRenderHandler.push_back(ptr);
		//m_vMapinfo.push_back(0);
	}
	ptr = nullptr;
	
	//debug및 테스트용 코드
	//for (int i = 0; i < 14; i++){
	//	setTile(static_cast<float>(i), 0.0f, 2);
	//}

	//for (int i = 0; i < 14; i++){
	//	setTile(0.0f, static_cast<float>(i), 2);
	//}

	//for (int i = 0; i < 14; i++){
	//	setTile(13.0f, static_cast<float>(i), 2);
	//}

	//for (int i = 0; i < 14; i++){
	//	setTile(static_cast<float>(i), 13.0f, 2);
	//}

	//
	
	setTile(3.0f, 5.0f, 2);
	setTile(4.0f, 8.0f, 2);
	setTile(11.0f, 3.0f, 3);
	setTile(12.0f, 12.0f, 3);
	setTile(6.0f, 1.0f, 2);	
	//

	
	/*mapSize.left = _offsetX - ((_RectTileWidth * _horizontal));
	mapSize.right = _offsetX + ((_RectTileWidth * _horizontal));
	mapSize.top = _offsetY - (_RectTileHeight / 2.0f);
	mapSize.bottom = _offsetY + ((_RectTileHeight * _vertical) - (_RectTileHeight / 2.0f));*/
}

int wTileMap::getMapinfo(int x, int y) { 	
	return m_vMapRenderHandler[(static_cast<int>(_vertical)*y) + x]->getType();
}

void wTileMap::addObjectToTile(float x, float y, mIObject* in){
	int nx = static_cast<int>(x);
	int ny = static_cast<int>(y);
	m_vMapRenderHandler[(static_cast<int>(_vertical)*ny) + nx]->addObject(in);
}

VECTOR2D wTileMap::getMapLimit(){ 
	return VECTOR2D(_horizontal, _vertical); 
}

 
uTile* wTileMap::getTile(float x, float y){
	int nx = static_cast<int>(x);
	int ny = static_cast<int>(y);
	return m_vMapRenderHandler[(static_cast<int>(_vertical)*ny) + nx];
}