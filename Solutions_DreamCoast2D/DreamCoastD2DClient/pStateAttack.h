#pragma once
#include "piState.h"
class pStateAttack :
	public piState
{
private:
	//��������
	virtual void enter(mPlayer* pmon);
	//��������
	virtual void execute(mPlayer* pmon);
	//���� ��Ż
	virtual void exit(mPlayer* pmon);
};

