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

	// ���� ��׷ΰ� �����ִ� ����(�������϶��� �ֱ������� ��ĵ)
	// �� �̵��� ��ĵ�� �ϴ� ���� �ӵ������� �������� ȿ���� ����
	// �׷��� ���� �ð����� ��ĵ�ϰ� Ʈ���� ����
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
