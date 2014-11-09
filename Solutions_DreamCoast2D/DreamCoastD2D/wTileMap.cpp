#include "stdafx.h"
#include <math.h>
#include <queue>
#include <map>
//
#include "cD2DRenderer.h"
#include "VECTOR2D.h"
#include "uSprite.h"
#include "wTileMap.h"
#include "IGObject.h"
#include "uCamera.h"
#include "mMonster.h"
#include "mObjManager.h"
#include "uTile.h"
#include "cResourceManager.h"
//
#include "mBuilding.h"

#include "netWorkCharManager.h"
#include "mNetworkObject.h"

wTileMap::wTileMap()
{	
	m_player = nullptr;
	m_ipD2DBitmap = nullptr;
	m_Cam = nullptr;
	//m_MapObjects = nullptr;

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
	if (m_spriteAtlas != NULL){
		delete m_spriteAtlas;
	}
	if (m_Cam != NULL){
		delete m_Cam;
	}

	uTile* ptr;
	while (m_vMapObjectHandler.empty()){
		ptr = m_vMapObjectHandler.back();
		m_vMapObjectHandler.pop_back();
		delete ptr;
	}
	ptr = nullptr;

	void* mptr;
	while (!m_mobs.empty()){
		mptr = m_mobs.back();
		m_mobs.pop_back();
		delete mptr;
	}
	mptr = nullptr;
}

void wTileMap::onInit(){
	m_ipD2DBitmap = ::cResourceManager::GetInstance().getTileMapBitMap();
	m_Cam = new uCamera(1028.0, 768.0f, m_player->getRealPos());
	//m_MapObjects = new mObjManager;

	//// Debug---------------------------------------------------
	//VECTOR2D in(6.0f*_RectTileWidth, 8.0f*_RectTileHeight);
	//VECTOR2D pt = twoDtoISO(in);
	//ICharacter* ptr = new mMonster(pt.x, pt.y);
	//mMonster* ptr2 = (mMonster*)ptr;
	//ptr2->setDir(LEFTDOWN);
	//ptr2->setTileMap(this);
	//m_mobs.push_back(ptr);
	////

	////
	//in.x = 7.0f*_RectTileWidth;
	//in.y = 8.0f*_RectTileHeight;
	//pt = twoDtoISO(in);
	//ptr = new mMonster(pt.x, pt.y);
	//ptr2 = (mMonster*)ptr;
	//ptr2->setDir(RIGHTDOWN);
	//ptr2->setTileMap(this);
	//// 이동 목표 설정 debug용
	////in.x = 10.0f*_RectTileWidth;
	////in.y = 10.0f*_RectTileHeight;
	////pt = twoDtoISO(in);
	////ptr2->setDest(pt.x, pt.y);
	////ptr2->setCurrentAggroLevel(ptr2->getMaxAggroLevel());
	//m_mobs.push_back(ptr);	

	////
	//in.x = 6.0f*_RectTileWidth;
	//in.y = 7.0f*_RectTileHeight;
	//pt = twoDtoISO(in);
	//ptr = new mMonster(pt.x, pt.y);
	//ptr2 = (mMonster*)ptr;
	//ptr2->setDir(LEFTUP);	
	//ptr2->setTileMap(this);
	//m_mobs.push_back(ptr);
	////
	//
	////
	//in.x = 7.0f*_RectTileWidth;
	//in.y = 7.0f*_RectTileHeight;
	//pt = twoDtoISO(in);
	//pt = twoDtoISO(in);
	//ptr = new mMonster(pt.x, pt.y);
	//ptr2 = (mMonster*)ptr;
	//ptr2->setDir(RIGHTUP);
	//ptr2->setTileMap(this);
	//m_mobs.push_back(ptr);
	//// Debug---------------------------------------------------
	//
	//ptr2 = nullptr;
	//ptr = nullptr;

	for (unsigned int i = 0; i < m_mobs.size(); i++){
		m_mobs[i]->onInit();
		m_mobs[i]->setCam(m_Cam);
	}



	for (unsigned int i = 0; i < m_mapObjects.size(); i++){
		//m_mobs[i]->onInit();
		m_mapObjects[i]->setCam(m_Cam);
	}

	for (int i = 0; i < _horizontal * _vertical; i++){
		m_vMapObjectHandler[i]->setCam(m_Cam);
	}
}

void wTileMap::addMonsterTotile(float x, float y){
	wTileMap::addMonsterTotile(x, y, 0);
}

void wTileMap::addMonsterTotile(float x, float y, int type){
	VECTOR2D in(x*_RectTileWidth, y*_RectTileHeight);
	VECTOR2D pt = twoDtoISO(in);
	ICharacter* ptr = new mMonster(pt.x, pt.y);
	mMonster* ptr2 = (mMonster*)ptr;
	ptr2->setDir(LEFTDOWN);
	ptr2->setTileMap(this);	
	ptr2->setCam(m_Cam);
	ptr2->setMonsterType(type);
	ptr->onInit();
	m_mobs.push_back(ptr);
	ptr2 = nullptr;
	ptr = nullptr;
}

void wTileMap::addMapObjectTotile(float x, float y, int type){
	VECTOR2D in(x*_RectTileWidth, y*_RectTileHeight);
	VECTOR2D pt = twoDtoISO(in);
	m_mapObjects.push_back(new mBuilding(type, new VECTOR2D(pt.x, pt.y), m_Cam));
}

void wTileMap::removeMapObjectFromTile(float x, float y){
	/*VECTOR2D in(x*_RectTileWidth, y*_RectTileHeight);
	VECTOR2D pt = twoDtoISO(in);*/
	std::queue<IMapObject*> m_mapObjectsTemp;
	IMapObject* ptr;
	VECTOR2D pt;
	while (!m_mapObjects.empty()){
		ptr = m_mapObjects.back();
		m_mapObjects.pop_back();

		pt = VECTOR2D(ptr->getPos().x, ptr->getPos().y);
		pt = getTileCoordinates(pt);
		//if (ptr->getType() == 1){
		if (x == pt.x && y == pt.y){
			delete ptr;
			ptr = nullptr;
		}
		else {
			m_mapObjectsTemp.push(ptr);
		}		
	}
	while (!m_mapObjectsTemp.empty()){
		m_mapObjects.push_back(m_mapObjectsTemp.front());
		m_mapObjectsTemp.pop();
	}
}

void wTileMap::onUpdate(float fdeltatime){	
	for (unsigned int i = 0; i < m_mobs.size(); i++){
		m_mobs[i]->onUpdate(fdeltatime);			
		
		// 죽은 상태면 오브젝트 데이터 목록에서 삭제
		// 혹은 차후 재사용 queue를 이용하게 되면 재활용 queue에 추가	
		if (((mMonster*)m_mobs[i])->getState() == ONDEAD){
			delete m_mobs[i];
			m_mobs.erase(m_mobs.begin() + i);
			m_mobs.shrink_to_fit();			
		}
		else {
			// 업데이트와 동시에 포지션별로 각 타일랜더핸들러 자기 좌표에 포인터를 먹여준다.
			VECTOR2D pos = getTileCoordinates(*m_mobs[i]->getDrawPos());
			::wTileMap::addRenderObjectToTile(pos.x, pos.y, m_mobs[i]);
		}
	}

	for (unsigned int i = 0; i < m_mapObjects.size(); i++){
		VECTOR2D objpos(m_mapObjects[i]->getPos().x, m_mapObjects[i]->getPos().y);
		VECTOR2D pos = getTileCoordinates(objpos);
		::wTileMap::addRenderMapObjectToTile(pos.x, pos.y, m_mapObjects[i]);		
	}

	netWorkCharManager::GetInstance().update(fdeltatime);
	std::map<int, mNetworkObject*>::iterator itr;

	for (itr = netWorkCharManager::GetInstance().getNetObjectList()->begin(); 
		itr != netWorkCharManager::GetInstance().getNetObjectList()->end(); itr++){
		VECTOR2D objpos(itr->second->getCurrentPacket().px, itr->second->getCurrentPacket().py);
		VECTOR2D pos = getTileCoordinates(objpos);
		::wTileMap::addRenderNetObjectToTile(pos.x, pos.y, itr->second);
	}

	// player는 고정되어 있는 메모리이므로
	// 일단 mob들이 타일에 뿌려진 뒤에 처리를 해야한다.
	// 킄... 선공은 몬스터가 먼저인가 킄....
	m_player->onUpdate(fdeltatime);

	//
	
}

void wTileMap::onRender(){
	// debug
	//renderer.GetRenderTarget()->DrawRectangle(mapSize, renderer.GetBlackBrush());
	//
	::wTileMap::renderMap();
	
	//::wTileMap::drawHealthBar(renderer, m_player);

	// Todo: 차후 Mob healthbar option 넣을 것, 혹은 UI Screen에서 관리
	for (unsigned int i = 0; i < m_mobs.size(); i++){
		::wTileMap::drawHealthBar(m_mobs[i]);
	}

	//
	//netWorkCharManager::GetInstance().render(m_Cam);
}

void wTileMap::onRenderEdit(){
	// debug
	//renderer.GetRenderTarget()->DrawRectangle(mapSize, renderer.GetBlackBrush());
	//
	::wTileMap::renderMapEdit();

	//::wTileMap::drawHealthBar(renderer, m_player);

	// Todo: 차후 Mob healthbar option 넣을 것, 혹은 UI Screen에서 관리
	for (unsigned int i = 0; i < m_mobs.size(); i++){
		::wTileMap::drawHealthBar(m_mobs[i]);
	}
}

void wTileMap::drawHealthBar(ICharacter* obj){
	VECTOR2D cpos = m_Cam->translasteToScreen(obj->getDrawPos());

	::D2D1_RECT_F healthBar;
	healthBar.top = cpos.y + 2.0f;
	healthBar.bottom = cpos.y + 7.0f;
	healthBar.left = cpos.x - 30.0f;
	healthBar.right = cpos.x + 30.0f;

	::D2D1_RECT_F currentHealthbar;
	currentHealthbar.top = healthBar.top;
	currentHealthbar.bottom = healthBar.bottom;
	currentHealthbar.left = healthBar.left;
	float healthRate = (cpos.x - 30.0f) + (obj->getHealth() / obj->getMAXHealth() * (healthBar.right - healthBar.left));
	if (healthRate <= healthBar.left){
		currentHealthbar.right = currentHealthbar.left;
	}
	else {
		currentHealthbar.right = healthRate;

	}
		
	::cD2DRenderer::GetInstance().GetRenderTarget()->FillRectangle(healthBar, ::cD2DRenderer::GetInstance().GetRedBrush());
	::cD2DRenderer::GetInstance().GetRenderTarget()->FillRectangle(currentHealthbar, ::cD2DRenderer::GetInstance().GetGreenBrush());
	::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(healthBar, ::cD2DRenderer::GetInstance().GetBlackBrush());
}

void wTileMap::setPlayer(ICharacter* p){
	m_player = p;
}

void wTileMap::renderMap(){
	VECTOR2D pt;
	float x, y;
	int type = 0;
	bool onTilecheck = false;

	// get real pos
	VECTOR2D test = getTileCoordinates(*m_player->getRealPos());
	VECTOR2D test2 = getTileCoordinates(*m_player->getDrawPos());

	//VECTOR2D _camtile = m_Cam->translasteToScreen(&tilePos);
	//if (_camtile.x < (0 - 45.0f) || _camtile.y < (0 - 45.0f) ||
	//	_camtile.x >(m_Cam->getScreenW() + 45.0f) ||
	//	_camtile.y >(m_Cam->getScreenH()) + 45.0f){
	//	//do nothing
	//}
	//else {
	//}

	// startx = 카메라가 위치한 cellinext
	// endx = start + cellwidth*(windowwith/cellwith)
	// starty
	// endy

	for (int j = 0; j < _vertical; j++){
		for (int i = 0; i < _horizontal; i++){
			x = j*_RectTileWidth;
			y = i*_RectTileHeight;
			VECTOR2D in(x, y);

			pt = twoDtoISO(in);

			/*if (test2.x == i && test2.y == j){
				onTilecheck = true;
			}*/

			// 타일 렌더 후 동시에 애드된 오브젝트들도 렌더
			// 렌더 이후에 오브젝트 포인터들은 팝되면서 사라진다.
			m_vMapObjectHandler[i + j*static_cast<int>(_vertical)]->
				renderTile(pt.x, pt.y, m_spriteAtlas, m_ipD2DBitmap);

			
			//mObjManager::getInstance().renderObject

			//renderTile(pt.x, pt.y, type, renderer);
			// 오더링 타일 뒤에 플레이어 숨기도록 해당 타일위에 있을때에 렌더하게 한다.
			// Todo: 매번 업데이트 할 필요 없도록 미리 계산해놓도록?
			// 이러면 타일을 넘어가게 될경우 캐릭터 렌더가 다음 타일에 가려버리게 되는데...			
		}
	}

	for (int j = 0; j < _vertical; j++){
		for (int i = 0; i < _horizontal; i++){
			m_vMapObjectHandler[i + j*static_cast<int>(_vertical)]->renderMapObject
				(pt.x, pt.y);		

			m_vMapObjectHandler[i + j*static_cast<int>(_vertical)]->renderObject
				(pt.x, pt.y);

			m_vMapObjectHandler[i + j*static_cast<int>(_vertical)]->renderNetObject
				(pt.x, pt.y);

			if (test.x == i && test.y == j) {
				m_player->onRender();
				//onTilecheck = false;
			}
		}
	}

	//m_MapObjects->render();
	// 반투명처리해서 장애물 뒤에서도 보이게
	m_player->onRender(true);

	
}


void wTileMap::renderMapEdit(){
	VECTOR2D pt;
	float x, y;
	int type = 0;
	bool onTilecheck = false;

	// get real pos
	VECTOR2D test = getTileCoordinates(*m_player->getRealPos());
	VECTOR2D test2 = getTileCoordinates(*m_player->getDrawPos());

	//VECTOR2D _camtile = m_Cam->translasteToScreen(&tilePos);
	//if (_camtile.x < (0 - 45.0f) || _camtile.y < (0 - 45.0f) ||
	//	_camtile.x >(m_Cam->getScreenW() + 45.0f) ||
	//	_camtile.y >(m_Cam->getScreenH()) + 45.0f){
	//	//do nothing
	//}
	//else {
	//}

	// startx = 카메라가 위치한 cellinext
	// endx = start + cellwidth*(windowwith/cellwith)
	// starty
	// endy

	for (int j = 0; j < _vertical; j++){
		for (int i = 0; i < _horizontal; i++){
			x = j*_RectTileWidth;
			y = i*_RectTileHeight;
			VECTOR2D in(x, y);

			pt = twoDtoISO(in);

			// 플레이어가 타일위에 있을때 
			//if (test.x == i && test.y == j){
			//	type = 1;				
			//	onTilecheck = true;				
			//}
			//else {
			//	//type = m_vMapObjectHandler[i + j*static_cast<int>(_vertical)]->getType();
			//	//type = m_vMapinfo[i+j*static_cast<int>(_vertical)];
			//}

			/*if (test2.x == i && test2.y == j){
			onTilecheck = true;
			}*/

			// 타일 렌더 후 동시에 애드된 오브젝트들도 렌더
			// 렌더 이후에 오브젝트 포인터들은 팝되면서 사라진다.
			m_vMapObjectHandler[i + j*static_cast<int>(_vertical)]->
				renderTileEdit(pt.x, pt.y, m_spriteAtlas, m_ipD2DBitmap);


			//mObjManager::getInstance().renderObject

			//renderTile(pt.x, pt.y, type, renderer);
			// 오더링 타일 뒤에 플레이어 숨기도록 해당 타일위에 있을때에 렌더하게 한다.
			// Todo: 매번 업데이트 할 필요 없도록 미리 계산해놓도록?
			// 이러면 타일을 넘어가게 될경우 캐릭터 렌더가 다음 타일에 가려버리게 되는데...			
		}
	}

	for (int j = 0; j < _vertical; j++){
		for (int i = 0; i < _horizontal; i++){
			m_vMapObjectHandler[i + j*static_cast<int>(_vertical)]->renderMapObject
				(pt.x, pt.y);

			m_vMapObjectHandler[i + j*static_cast<int>(_vertical)]->renderObject
				(pt.x, pt.y);

			if (test.x == i && test.y == j) {
				m_player->onRender();
				//onTilecheck = false;
			}
		}
	}

	//m_MapObjects->render();
	// 반투명처리해서 장애물 뒤에서도 보이게
	m_player->onRender(true);
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
	m_vMapObjectHandler[(static_cast<int>(_vertical)*ny) + nx]->setType(type);
}

void wTileMap::setSize(float horizontal, float vertical){
	_horizontal = horizontal;
	_vertical = vertical;

	uTile* ptr = nullptr;
	for (int i = 0; i < _horizontal * _vertical; i++){
		ptr = new uTile(0, m_Cam);
		m_vMapObjectHandler.push_back(ptr);
	}
	ptr = nullptr;
}

int wTileMap::getMapinfo(int x, int y) { 	
	return m_vMapObjectHandler[(static_cast<int>(_vertical)*y) + x]->getType();
}

void wTileMap::addRenderObjectToTile(float x, float y, ICharacter* in){
	int nx = static_cast<int>(x);
	int ny = static_cast<int>(y);
	m_vMapObjectHandler[(static_cast<int>(_vertical)*ny) + nx]->addObject(in);
}

void wTileMap::addRenderMapObjectToTile(float x, float y, IMapObject* in){
	int nx = static_cast<int>(x);
	int ny = static_cast<int>(y);
	m_vMapObjectHandler[(static_cast<int>(_vertical)*ny) + nx]->addMapObject(in);
}

void wTileMap::addRenderNetObjectToTile(float x, float y, mNetworkObject* in){
	int nx = static_cast<int>(x);
	int ny = static_cast<int>(y);
	if (nx >= 0 && ny >= 0){
		m_vMapObjectHandler[(static_cast<int>(_vertical)*ny) + nx]->addNetObject(in);
	}
}

VECTOR2D wTileMap::getMapLimit(){ 
	return VECTOR2D(_horizontal, _vertical); 
}

 
uTile* wTileMap::getTile(float x, float y){
	int nx = static_cast<int>(x);
	int ny = static_cast<int>(y);
	return m_vMapObjectHandler[(static_cast<int>(_vertical)*ny) + nx];
}


bool wTileMap::sightScan(float sight, VECTOR2D monsterpos){
	VECTOR2D ppos = getTileCoordinates(*m_player->getRealPos());
	VECTOR2D mpos = getTileCoordinates(monsterpos);
	bool ret = false;
	scanVision(sight, mpos, ppos, &ret);
	return ret;
}

void wTileMap::scanVision(float sight, VECTOR2D monsterpos, VECTOR2D playerPos, bool* ret){
	float x = monsterpos.x;
	float y = monsterpos.y;

	if (x == playerPos.x && y == playerPos.y){
		*ret = true;
		return;
	}

	if (sight <= 0) return;

	VECTOR2D up = VECTOR2D(x, y - 1.0f);
	VECTOR2D down = VECTOR2D(x, y + 1.0f);
	VECTOR2D left = VECTOR2D(x-1.0f, y);
	VECTOR2D right = VECTOR2D(x+1.0f, y);
	
	if (up.y >= 0 && up.y < _vertical)
		scanVision(sight - 1.0f, up, playerPos, ret);
	if (down.y >= 0 && down.y < _vertical)
		scanVision(sight - 1.0f, down, playerPos, ret);
	if (left.x >= 0 && left.x < _horizontal)
		scanVision(sight - 1.0f, left, playerPos, ret);
	if (right.x >= 0 && right.x < _horizontal)
		scanVision(sight - 1.0f, right, playerPos, ret);
}

VECTOR2D wTileMap::getPlayerTilePos(){
	return getTileCoordinates(*m_player->getRealPos());
}

void wTileMap::playerGetHit(float dmg){
	m_player->getHit(dmg);
}