#include "stdafx.h"
#include <queue>
#include "mObjManager.h"
#include "wTileMap.h"

mObjManager::mObjManager()
{

}


mObjManager::~mObjManager()
{

}

void mObjManager::update(float delta){

}

void mObjManager::render(){
	//std::queue<IMapObject*> temp;
	for (unsigned int i = 0; i < m_qMapObject.size(); i++){
		m_qMapObject[i]->render();
	}
}

void mObjManager::pushToObjectlist(IMapObject* Object){
	m_qMapObject.push_back(Object);
}

void deletefromObjectlistByTileCoordinate(float x, float y, wTileMap* map) {

}