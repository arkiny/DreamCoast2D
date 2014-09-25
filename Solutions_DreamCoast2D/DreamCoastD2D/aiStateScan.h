#pragma once
#include "aiState.h"

class VECTOR2D;

class aiStateScan :
	public aiState
{
private:
	void enter(mMonster* pmon);
	void execute(mMonster* pmon);
	void exit(mMonster* pmon);

	float accumtime = 0.0f;
	bool m_playerInSight = false;
	void scanVision(float, VECTOR2D*);
};