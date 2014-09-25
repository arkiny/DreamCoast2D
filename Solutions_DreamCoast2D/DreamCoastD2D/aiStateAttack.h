#pragma once
#include "aiState.h"
class aiStateAttack :
	public aiState
{
private:
	void enter(mMonster* pmon);
	void execute(mMonster* pmon);
	void exit(mMonster* pmon);

	float attacktimer = 0.0f;
	float nextIdle = 0.0f;
	bool attacked = false;
};
