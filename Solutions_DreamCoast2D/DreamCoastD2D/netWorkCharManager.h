#pragma once
#include <map>
#include "Singleton.h"
#include "movePacket.h"


class mTestObject;

class netWorkCharManager : public Singleton<netWorkCharManager>
{
public:
	netWorkCharManager();
	~netWorkCharManager();
	void addToCharList(mTestObject* character){}
	

	void update(){}
	void render(){}

	void setMyId(int i);
	int getMyId(){ return m_nMyId; }

	bool hasCharacter(int id);
	void addToCharList(movePacket in);
	void removeFromList(int id);

private:
	int m_nMyId;
	std::map<int, mTestObject*> m_mChars;
};

