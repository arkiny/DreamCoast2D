#pragma once
#include "niState.h"
class nStateMove :
	public niState
{
private:
	virtual void enter(mNetworkObject* pobj);
	//��������
	virtual void execute(mNetworkObject* pobj);
	//���� ��Ż
	virtual void exit(mNetworkObject* pobj);
};

