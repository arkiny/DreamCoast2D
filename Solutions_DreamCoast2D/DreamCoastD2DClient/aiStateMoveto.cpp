#include "stdafx.h"
#include "aiStateMoveto.h"
#include "aiStateOnHit.h"
#include "aiStateIdle.h"
#include "aiStateScan.h"
#include "aiStateDead.h"
#include "uSprite.h"
#include "mMonster.h"
#include "wTileMap.h"
#include "VECTOR2D.h"

void aiStateMoveto::enter(mMonster* pmon)
{
	m_sprite = pmon->getSprite();
	pmon->onMove();
}


void aiStateMoveto::execute(mMonster* pmon)
{
	accumtime += pmon->getdeltaTime();
	m_sprite->nextFrame(pmon->getdeltaTime());
	pmon->moveToDest(pmon->getdeltaTime());

	// 만약 어그로가 끌려있는 상태(추적중일때는 주기적으로 스캔)
	// 매 이동시 스캔을 하니 연산 속도때문에 느려지는 효과가 생김
	// 그래서 일정 시간마다 스캔하게 트리거 변경
	if (pmon->getHealth() <= 0.0f){
		pmon->changeState(new aiStateDead);
		return;
	}

	/*if (pmon->getCurrentAggroLevel() >= pmon->getMaxAggroLevel()){
		accumtime = 0;
		pmon->changeState(new aiStateScan);
	}*/


	bool inSight = pmon->getTileMap()->sightScan(pmon->getSight(), *(pmon->getDrawPos()));
	if (pmon->getMonsterType() != 0 && inSight){
		pmon->setCurrentAggroLevel(pmon->getMaxAggroLevel());
	}
	
	if (pmon->getCurrentAggroLevel() >= pmon->getMaxAggroLevel()
		&& accumtime >= 1.0f){
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
