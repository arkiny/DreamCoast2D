#pragma once
#include "niMobState.h"
class niMobStateOnHit :
	public niMobState
{
private:
	virtual void enter(mNetworkMob* pobj);
	//��������
	virtual void execute(mNetworkMob* pobj);
	//���� ��Ż
	virtual void exit(mNetworkMob* pobj);
};

