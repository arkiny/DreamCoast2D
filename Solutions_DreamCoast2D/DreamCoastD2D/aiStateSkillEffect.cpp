#include "stdafx.h"
#include "mMonster.h"
#include "aiStateDead.h"
#include "aiStateOnHit.h"
#include "aiStateIdle.h"
#include "VECTOR2D.h"
#include "aiStateSkillEffect.h"
#include "uSprite.h"
#include "wTileMap.h"

void aiStateSkillEffect::enter(mMonster* pmon){
	m_sprite = pmon->getSprite();
	if (pmon->getMonsterType() == 2){
		pmon->onAttack();
		m_sprite->setCurrentFrame(0);
	}
	else {

	}
}

void aiStateSkillEffect::execute(mMonster* pmon){
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
	if (attacktimer >= FRAMERATE * 3 && !attacked){
		pmon->getTileMap()->playerGetHit(pmon->getAttackPower()*5.0f);
		attacked = true;
	}

	// ������ ����� ���̵�� ���ư��� ��׷�üũ���� �ٽ�
	if (nextIdle >= FRAMERATE * 8){
		pmon->changeState(new aiStateIdle);
	}
}

void aiStateSkillEffect::exit(mMonster* pmon){

}