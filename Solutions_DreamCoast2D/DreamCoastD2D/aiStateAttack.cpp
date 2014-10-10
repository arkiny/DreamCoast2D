#include "stdafx.h"
#include "aiStateAttack.h"
#include "mMonster.h"
#include "uSprite.h"
#include "wTileMap.h"
#include "aiStateIdle.h"
#include "aiStateOnHit.h"

void aiStateAttack::enter(mMonster* pmon){
	// attack�� move�� ���� ��������Ʈ�� ����.
	m_sprite = pmon->getSprite();
	pmon->onMove();
}

void aiStateAttack::execute(mMonster* pmon){
	nextIdle += pmon->getdeltaTime();
	attacktimer += pmon->getdeltaTime();
	m_sprite->nextFrame(pmon->getdeltaTime());
	
	// �������̶� ���� ������ ����
	if (pmon->getState() == ONHIT){
		pmon->changeState(new aiStateOnHit);
	}

	// �������� 3������ ���Ŀ�, ���� ������ ���
	if (attacktimer >= FRAMERATE * 3 && !attacked){
		pmon->getTileMap()->playerGetHit(pmon->getAttackPower());
		attacked = true;
	}

	// ������ ����� ���̵�� ���ư��� ��׷�üũ���� �ٽ�
	if (nextIdle >= FRAMERATE * 8){
		pmon->changeState(new aiStateIdle);
	}
}

void aiStateAttack::exit(mMonster* pmon){

}
