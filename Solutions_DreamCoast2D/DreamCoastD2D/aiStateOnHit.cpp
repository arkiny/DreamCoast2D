#include "stdafx.h"
#include "aiStateOnHit.h"
#include "aiStateIdle.h"
#include "aiStateDead.h"
#include "cSoundManager.h"
#include "uSprite.h"
#include "mMonster.h"


void aiStateOnHit::enter(mMonster* pmon){	
	m_sprite = pmon->getSprite();
	pmon->onHit();
	// 맞은 즉시 어그로레벨 최대화
	pmon->setCurrentAggroLevel(pmon->getMaxAggroLevel());
	cSoundManager::GetInstance().executeOnHit();

}

void aiStateOnHit::execute(mMonster* pmon){
	// frame이 다 출력되면 대기모드로 들어감
	m_sprite->nextFrame(pmon->getdeltaTime());	
	accumtime += pmon->getdeltaTime();
	
	if (pmon->getHealth() <= 0.0f){
		pmon->changeState(new aiStateDead);
		return;
	} 
	else if (accumtime > FRAMERATE*2.0f){
		pmon->setState(ONIDLE);
		pmon->changeState(new aiStateIdle);
	}
}

void aiStateOnHit::exit(mMonster* pmon){
	pmon->setDmg(0.0f);
}