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

	// 공격중이라도 읃어 맞으면 경직
	if (pmon->getState() == ONHIT){
		pmon->changeState(new aiStateOnHit);
	}

	// 데미지는 3프레임 이후에, 공격 안했을 경우
	if (attacktimer >= FRAMERATE * 3 && !attacked){
		pmon->getTileMap()->playerGetHit(pmon->getAttackPower()*5.0f);
		attacked = true;
	}

	// 프레임 종료뒤 아이들로 돌아가서 어그로체크부터 다시
	if (nextIdle >= FRAMERATE * 8){
		pmon->changeState(new aiStateIdle);
	}
}

void aiStateSkillEffect::exit(mMonster* pmon){

}