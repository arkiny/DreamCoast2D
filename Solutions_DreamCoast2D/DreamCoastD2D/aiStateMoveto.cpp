#include "stdafx.h"
#include "aiStateMoveto.h"
#include "aiStateDead.h"
#include "aiStateOnHit.h"
#include "aiStateIdle.h"
#include "aiStateDead.h"
#include "uSprite.h"
#include "mMonster.h"
#include "VECTOR2D.h"

void aiStateMoveto::enter(mMonster* pmon)
{
	m_sprite = pmon->getSprite();
	pmon->onMove();
}


void aiStateMoveto::execute(mMonster* pmon)
{
	// if (target == currentpos){ setState(new Idle()) }
	// else move to target
	m_sprite->nextFrame(pmon->getdeltaTime());
	pmon->moveToDest(pmon->getdeltaTime());

	if (*(pmon->getRealPos()) == *(pmon->getDest())){
		pmon->changeState(new aiStateIdle);
		pmon->setState(ONIDLE);
	}
	if (pmon->getState() == ONHIT){
		pmon->changeState(new aiStateOnHit);
	}
}

void aiStateMoveto::exit(mMonster* pmon)
{
}
