#include "stdafx.h"
#include "aiStateMoveto.h"
#include "aiStateOnHit.h"
#include "aiStateIdle.h"
#include "aiStateScan.h"
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
	accumtime += pmon->getdeltaTime();
	m_sprite->nextFrame(pmon->getdeltaTime());
	pmon->moveToDest(pmon->getdeltaTime());

	// 만약 어그로가 끌려있는 상태(추적중일때는 주기적으로 스캔)
	// 매 이동시 스캔을 하니 연산 속도때문에 느려지는 효과가 생김
	// 그래서 일정 시간마다 스캔하게 트리거 변경
	if (pmon->getCurrentAggroLevel() >= pmon->getMaxAggroLevel() 
		&& accumtime >= 2.0f){
		accumtime = 0;
		pmon->changeState(new aiStateScan);
	}

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
