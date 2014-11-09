#include "stdafx.h"
#include "netWorkCharManager.h"
#include "mNetworkObject.h"

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
	std::map<int, mNetworkObject*>::iterator it = m_mChars.find(id);
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
		mNetworkObject* input = new mNetworkObject(in);
		m_mChars.insert(std::pair<int, mNetworkObject*>(in.id, input));
	}
}

void netWorkCharManager::removeFromList(int id){
	std::map<int, mNetworkObject*>::iterator it = m_mChars.find(id);
	if (it != m_mChars.end()){
		m_mChars.erase(it);
	}
}

void netWorkCharManager::render(uCamera* cam){
	// �ϴ� �簢�� �׷��� �ȿ� �������ͽ� ����
	std::map<int, mNetworkObject*>::iterator itr;
	for (itr = m_mChars.begin(); itr != m_mChars.end(); itr++){
		itr->second->render(cam);
	}
}

void netWorkCharManager::updateState(movePacket in){
	std::map<int, mNetworkObject*>::iterator it = m_mChars.find(in.id);	
	it->second->setCurrentPacket(in);
}

void netWorkCharManager::update(float delta){
	std::map<int, mNetworkObject*>::iterator itr;
	for (itr = m_mChars.begin(); itr != m_mChars.end(); itr++){
		itr->second->update(delta);
	}
}