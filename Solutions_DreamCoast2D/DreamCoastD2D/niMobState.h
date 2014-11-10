#pragma once

class mNetworkMob;
class uSprite;

class niMobState
{
public:
	niMobState(){};
	virtual ~niMobState(){};
public:
	//상태진입
	virtual void enter(mNetworkMob* pobj) = 0;
	//상태진행
	virtual void execute(mNetworkMob* pobj) = 0;
	//상태 이탈
	virtual void exit(mNetworkMob* pobj) = 0;
protected:
	uSprite* m_sprite;
	float accumtime = 0.0f;
};

