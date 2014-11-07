#pragma once
#include "piState.h"
class pStateOnDead :
	public piState
{
private:
	void enter(mPlayer* pmon);
	void execute(mPlayer* pmon);
	void exit(mPlayer* pmon);
};

