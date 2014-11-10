#include "stdafx.h"
#include "cSoundManager.h"
#include "aiStateDead.h"
#include "aiStateOnHit.h"
#include "aiStateIdle.h"
#include "aiStateDead.h"
#include "uSprite.h"
#include "mMonster.h"


void aiStateDead::enter(mMonster* pmon){
	m_sprite = pmon->getSprite();
	pmon->onDeath();
	m_sprite->setCurrentFrame(0);
	cSoundManager::GetInstance().executeOnDie(0);
}

void aiStateDead::execute(mMonster* pmon){
	accumtime += pmon->getdeltaTime();
	if (accumtime < FRAMERATE * 1.0f){
		m_sprite->nextFrame(pmon->getdeltaTime());
	}

	// 사망시 페이드아웃 효과
	pmon->setAlpha(pmon->getAlpha() - 0.025f);

	// 차후 delete 보다는 setVisible을 이용해서
	// 다시 이용하는 방법도 있을 듯 하뎌이다
	// 일정 시간이 지난 뒤 삭제 trigger on
	if (accumtime > FRAMERATE*8.0f){
		pmon->setState(ONDEAD);		
	}
}

void aiStateDead::exit(mMonster* pmon){

}