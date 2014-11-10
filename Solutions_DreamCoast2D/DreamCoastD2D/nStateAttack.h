#pragma once
#include "niState.h"
class nStateAttack :
	public niState
{
private:
	virtual void enter(mNetworkObject* pobj);
	//상태진행
	virtual void execute(mNetworkObject* pobj);
	//상태 이탈
	virtual void exit(mNetworkObject* pobj);
};

