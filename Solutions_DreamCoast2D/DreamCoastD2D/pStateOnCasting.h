#pragma once
#include "piState.h"
class pStateOnCasting :
	public piState
{
private:
	void enter(mPlayer* pmon);
	void execute(mPlayer* pmon);
	void exit(mPlayer* pmon);
};

