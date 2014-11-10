#pragma once
#include "piState.h"
class pStateAttack :
	public piState
{
private:
	//상태진입
	virtual void enter(mPlayer* pmon);
	//상태진행
	virtual void execute(mPlayer* pmon);
	//상태 이탈
	virtual void exit(mPlayer* pmon);
};

