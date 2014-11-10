#pragma once
#include "aiState.h"
class aiStateDead :
	public aiState
{
private:
	void enter(mMonster* pmon);
	void execute(mMonster* pmon);
	void exit(mMonster* pmon);	
};

