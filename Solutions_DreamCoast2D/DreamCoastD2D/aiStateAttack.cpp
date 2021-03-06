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
	// attack과 move는 같은 스프라이트를 쓴다.
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

	// 공격중이라도 읃어 맞으면 경직
	if (pmon->getState() == ONHIT){
		pmon->changeState(new aiStateOnHit);
	}

	// 데미지는 3프레임 이후에, 공격 안했을 경우
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

	// 프레임 종료뒤 아이들로 돌아가서 어그로체크부터 다시
	if (nextIdle >= FRAMERATE * 8){
		pmon->changeState(new aiStateScan);
	}
}

void aiStateAttack::exit(mMonster* pmon){

}
