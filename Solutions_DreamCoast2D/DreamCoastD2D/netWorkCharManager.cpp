#include "stdafx.h"
#include "netWorkCharManager.h"
#include "mTestObject.h"

template<> netWorkCharManager* Singleton<netWorkCharManager>::_instance = 0;

netWorkCharManager::netWorkCharManager()
{
}


netWorkCharManager::~netWorkCharManager()
{
}

void netWorkCharManager::setMyId(int i){
	m_nMyId = i;
}

bool netWorkCharManager::hasCharacter(int id){
	std::map<int, mTestObject*>::iterator it = m_mChars.find(id);
	if (it != m_mChars.end()){
		return true;
	}
	else {
		return false;
	}
}

void netWorkCharManager::addToCharList(movePacket in){
	// double check
	if (!hasCharacter(in.id)){
		mTestObject* input = new mTestObject(in);
		m_mChars.insert(std::pair<int, mTestObject*>(in.id, input));
	}
}

void netWorkCharManager::removeFromList(int id){
	std::map<int, mTestObject*>::iterator it = m_mChars.find(id);
	if (it != m_mChars.end()){
		m_mChars.erase(it);
	}
}

void netWorkCharManager::render(uCamera* cam){
	// 일단 사각형 그려서 안에 스테이터스 쓰기
	std::map<int, mTestObject*>::iterator itr;
	for (itr = m_mChars.begin(); itr != m_mChars.end(); itr++){
		itr->second->render(cam);
	}
}

void netWorkCharManager::updateState(movePacket in){
	std::map<int, mTestObject*>::iterator it = m_mChars.find(in.id);	
	it->second->setCurrentPacket(in);
}

void netWorkCharManager::update(float delta){
	std::map<int, mTestObject*>::iterator itr;
	for (itr = m_mChars.begin(); itr != m_mChars.end(); itr++){
		itr->second->update(delta);
	}
}