#pragma once
#include <map>
#include "Singleton.h"
#include "movePacket.h"


class mNetworkObject;
class mNetworkMob;
class mMonster;
class uCamera;

class netWorkCharManager : public Singleton<netWorkCharManager>
{
public:
	netWorkCharManager();
	~netWorkCharManager();
	void addToCharList(mNetworkObject* character){}
	

	void update(float delta);
	void render(uCamera* cam);

	// self checker
	void setMyId(int i);
	int getMyId(){ return m_nMyId; }

	// player management
	bool hasCharacter(int id);
	void addToCharList(movePacket in);
	void updateState(movePacket in);
	void removeFromList(int id);
	std::map<int, mNetworkObject*>* getNetObjectList(){ return &m_mChars; }

	// netmob management
	bool hasMob(int id);
	void addToMobList(movePacket in);
	void updateMobState(movePacket in);
	void removeFromMobList(int id);
	std::map<int, mNetworkMob*>* getNetMobObjectList(){ return &m_mMobs; }

	// hostmob management
	void addToHostMob();
	int getMyID(mMonster* me);

private:
	int m_nMyId;
	std::map<int, mNetworkObject*> m_mChars;
	std::map<int, mNetworkMob*> m_mMobs;

	std::map<int, mMonster*> m_mHostMobs;
};

