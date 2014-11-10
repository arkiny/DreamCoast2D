#pragma once
#include "piState.h"
class pStateIdle :
	public piState
{
private:
	void enter(mPlayer* pmon);
	void execute(mPlayer* pmon);
	void exit(mPlayer* pmon);
};

