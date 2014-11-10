#pragma once
#include <map>
#include "Singleton.h"
#include "movePacket.h"


class mNetworkObject;
class uCamera;

class netWorkCharManager : public Singleton<netWorkCharManager>
{
public:
	netWorkCharManager();
	~netWorkCharManager();
	void addToCharList(mNetworkObject* character){}
	

	void update(float delta);
	void render(uCamera* cam);

	void setMyId(int i);
	int getMyId(){ return m_nMyId; }

	bool hasCharacter(int id);
	void addToCharList(movePacket in);

	void updateState(movePacket in);

	void removeFromList(int id);
	std::map<int, mNetworkObject*>* getNetObjectList(){ return &m_mChars; }

private:
	int m_nMyId;
	std::map<int, mNetworkObject*> m_mChars;
};

