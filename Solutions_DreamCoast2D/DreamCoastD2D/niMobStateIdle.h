#pragma once
#include "niMobState.h"
class niMobStateIdle :
	public niMobState
{
private:
	virtual void enter(mNetworkMob* pobj);
	//상태진행
	virtual void execute(mNetworkMob* pobj);
	//상태 이탈
	virtual void exit(mNetworkMob* pobj);
};

