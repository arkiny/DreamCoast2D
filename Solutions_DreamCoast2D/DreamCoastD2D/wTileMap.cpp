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

	//�ӽ÷� Ÿ�ϸ� �߾ӿ� ��ġ
	m_spriteAtlas = new uSprite();

	//_vertical = 14.0f;
	//_horizontal = 14.0f;
	_RectTileWidth = 45.0f;
	_RectTileHeight = 45.0f;
	
	// offset ����
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
	ptr2->setTileMap(this);
	m_mobs.push_back(ptr);
	//

	//
	in.x = 7.0f*_RectTileWidth;
	in.y = 8.0f*_RectTileHeight;
	pt = twoDtoISO(in);
	ptr = new mMonster(pt.x, pt.y);
	ptr2 = (mMonster*)ptr;
	ptr2->setDir(RIGHTDOWN);
	ptr2->setTileMap(this);
	// �̵� ��ǥ ���� debug��
	//in.x = 10.0f*_RectTileWidth;
	//in.y = 10.0f*_RectTileHeight;
	//pt = twoDtoISO(in);
	//ptr2->setDest(pt.x, pt.y);
	ptr2->setCurrentAggroLevel(ptr2->getMaxAggroLevel());
	m_mobs.push_back(ptr);	

	//
	in.x = 6.0f*_RectTileWidth;
	in.y = 7.0f*_RectTileHeight;
	pt = twoDtoISO(in);
	ptr = new mMonster(pt.x, pt.y);
	ptr2 = (mMonster*)ptr;
	ptr2->setDir(LEFTUP);	
	ptr2->setTileMap(this);
	m_mobs.push_back(ptr);
	//
	
	//
	in.x = 7.0f*_RectTileWidth;
	in.y = 7.0f*_RectTileHeight;
	pt = twoDtoISO(in);
	pt = twoDtoISO(in);
	ptr = new mMonster(pt.x, pt.y);
	ptr2 = (mMonster*)ptr;
	ptr2->setDir(RIGHTUP);
	ptr2->setTileMap(this);
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
	for (unsigned int i = 0; i < m_mobs.size(); i++){
		m_mobs[i]->onUpdate(fdeltatime);			
		
		// ���� ���¸� ������Ʈ ������ ��Ͽ��� ����
		// Ȥ�� ���� ���� queue�� �̿��ϰ� �Ǹ� ��Ȱ�� queue�� �߰�	
		if (((mMonster*)m_mobs[i])->getState() == ONDEAD){
			delete m_mobs[i];
			m_mobs.erase(m_mobs.begin() + i);
			m_mobs.shrink_to_fit();			
		}
		else {
			// ������Ʈ�� ���ÿ� �����Ǻ��� �� Ÿ�Ϸ����ڵ鷯 �ڱ� ��ǥ�� �����͸� �Կ��ش�.
			VECTOR2D pos = getTileCoordinates(*m_mobs[i]->getDrawPos());
			::wTileMap::addRenderObjectToTile(pos.x, pos.y, m_mobs[i]);
		}
	}
	
	// player�� �����Ǿ� �ִ� �޸��̹Ƿ�
	// �ϴ� mob���� Ÿ�Ͽ� �ѷ��� �ڿ� ó���� �ؾ��Ѵ�.
	// ��... ������ ���Ͱ� �����ΰ� ��....
	m_player->onUpdate(fdeltatime);
}

void wTileMap::onRender(cD2DRenderer& renderer){
	// debug
	//renderer.GetRenderTarget()->DrawRectangle(mapSize, renderer.GetBrush());
	//
	::wTileMap::renderMap(renderer);
	// Todo: ���� healthbar option ���� ��
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

			// �÷��̾ Ÿ������ ������ 
			if (test.x == i && test.y == j){
				type = 1;				
				onTilecheck = true;				
			}
			//else {
			//	//type = m_vMapObjectHandler[i + j*static_cast<int>(_vertical)]->getType();
			//	//type = m_vMapinfo[i+j*static_cast<int>(_vertical)];
			//}

			if (test2.x == i && test2.y == j){
				onTilecheck = true;
			}

			// Ÿ�� ���� �� ���ÿ� �ֵ�� ������Ʈ�鵵 ����
			// ���� ���Ŀ� ������Ʈ �����͵��� �˵Ǹ鼭 �������.
			m_vMapObjectHandler[i + j*static_cast<int>(_vertical)]->
				renderTile(pt.x, pt.y, renderer, m_spriteAtlas, m_ipD2DBitmap);

			//renderTile(pt.x, pt.y, type, renderer);
			// ������ Ÿ�� �ڿ� �÷��̾� ���⵵�� �ش� Ÿ������ �������� �����ϰ� �Ѵ�.
			// Todo: �Ź� ������Ʈ �� �ʿ� ������ �̸� ����س�����?
			// �̷��� Ÿ���� �Ѿ�� �ɰ�� ĳ���� ������ ���� Ÿ�Ͽ� ���������� �Ǵµ�...
			if (onTilecheck) {
				m_player->onRender(renderer);
				onTilecheck = false;
			}
		}
	}
	// ������ó���ؼ� ��ֹ� �ڿ����� ���̰�
	m_player->onRender(renderer, true);
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

	/*for (int i = 0; i < _horizontal * _vertical; i++){
		m_vMapinfo.push_back(0);
	}*/

	uTile* ptr = nullptr;
	for (int i = 0; i < _horizontal * _vertical; i++){
		ptr = new uTile(0, m_Cam);
		m_vMapObjectHandler.push_back(ptr);
		//m_vMapinfo.push_back(0);
	}
	ptr = nullptr;
	
	//debug�� �׽�Ʈ�� �ڵ�
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
	return m_vMapObjectHandler[(static_cast<int>(_vertical)*y) + x]->getType();
}

void wTileMap::addRenderObjectToTile(float x, float y, mIObject* in){
	int nx = static_cast<int>(x);
	int ny = static_cast<int>(y);
	m_vMapObjectHandler[(static_cast<int>(_vertical)*ny) + nx]->addObject(in);
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