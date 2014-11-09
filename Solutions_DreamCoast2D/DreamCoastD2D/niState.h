#pragma once

class mNetworkObject;
class uSprite;

class niState
{
public:
	niState(){};
	virtual ~niState(){};
public:
	//상태진입
	virtual void enter(mNetworkObject* pobj) = 0;
	//상태진행
	virtual void execute(mNetworkObject* pobj) = 0;
	//상태 이탈
	virtual void exit(mNetworkObject* pobj) = 0;
protected:
	uSprite* m_sprite;
	float accumtime = 0.0f;
};

