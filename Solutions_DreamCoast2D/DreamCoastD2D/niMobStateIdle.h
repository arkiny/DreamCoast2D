#pragma once
#include "niMobState.h"
class niMobStateIdle :
	public niMobState
{
private:
	virtual void enter(mNetworkMob* pobj);
	//��������
	virtual void execute(mNetworkMob* pobj);
	//���� ��Ż
	virtual void exit(mNetworkMob* pobj);
};

