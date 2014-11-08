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
		mTestObject* input = new mTestObject;
		m_mChars.insert(std::pair<int, mTestObject*>(in.id, input));
	}
}

void netWorkCharManager::removeFromList(int id){
	std::map<int, mTestObject*>::iterator it = m_mChars.find(id);
	if (it != m_mChars.end()){
		m_mChars.erase(it);
	}
}