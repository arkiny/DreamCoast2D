#pragma once
#include "aiState.h"
class aiStateOnCasting :
	public aiState
{
private:
	void enter(mMonster* pmon);
	void execute(mMonster* pmon);
	void exit(mMonster* pmon);

	float accumcasting = 0.0f;
	// ���� dbȭ
	const float castingtime = 1.0;	
};

