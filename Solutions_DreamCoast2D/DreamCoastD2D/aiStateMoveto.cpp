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

	// ���� ��׷ΰ� �����ִ� ����(�������϶��� �ֱ������� ��ĵ)
	// �� �̵��� ��ĵ�� �ϴ� ���� �ӵ������� �������� ȿ���� ����
	// �׷��� ���� �ð����� ��ĵ�ϰ� Ʈ���� ����
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
