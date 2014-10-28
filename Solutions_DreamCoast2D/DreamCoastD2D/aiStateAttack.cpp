#include "stdafx.h"
#include "aiStateAttack.h"
#include "mMonster.h"
#include "uSprite.h"
#include "wTileMap.h"
//#include "aiStateIdle.h"
#include "aiStateOnHit.h"
#include "aiStateDead.h"
#include "aiStateScan.h"

void aiStateAttack::enter(mMonster* pmon){
	// attack�� move�� ���� ��������Ʈ�� ����.
	m_sprite = pmon->getSprite();
	if (pmon->getMonsterType() == 2){
		pmon->onAttack();
	}
	else {
		
	}
	m_sprite->setCurrentFrame(0);
}

void aiStateAttack::execute(mMonster* pmon){
	nextIdle += pmon->getdeltaTime();
	attacktimer += pmon->getdeltaTime();
	m_sprite->nextFrame(pmon->getdeltaTime());
	
	if (pmon->getHealth() <= 0.0f){
		pmon->changeState(new aiStateDead);
		return;
	}

	// �������̶� ���� ������ ����
	if (pmon->getState() == ONHIT){
		pmon->changeState(new aiStateOnHit);
	}

	// �������� 3������ ���Ŀ�, ���� ������ ���
	if (pmon->getMonsterType() != 2){
		if (attacktimer >= FRAMERATE * 3 && !attacked){
			pmon->getTileMap()->playerGetHit(pmon->getAttackPower());
			attacked = true;
		}
	}
	else {
		if (attacktimer >= FRAMERATE * 4 && !attacked){
			pmon->getTileMap()->playerGetHit(pmon->getAttackPower());
			attacked = true;
		}
	}

	// ������ ����� ���̵�� ���ư��� ��׷�üũ���� �ٽ�
	if (nextIdle >= FRAMERATE * 8){
		pmon->changeState(new aiStateScan);
	}
}

void aiStateAttack::exit(mMonster* pmon){

}
