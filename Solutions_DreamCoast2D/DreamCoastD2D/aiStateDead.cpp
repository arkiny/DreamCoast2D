#include "stdafx.h"
#include "aiStateDead.h"
#include "aiStateOnHit.h"
#include "aiStateIdle.h"
#include "aiStateDead.h"
#include "uSprite.h"
#include "mMonster.h"


void aiStateDead::enter(mMonster* pmon){
	m_sprite = pmon->getSprite();
	pmon->onDeath();
}

void aiStateDead::execute(mMonster* pmon){
	m_sprite->nextFrame(pmon->getdeltaTime());
	accumtime += pmon->getdeltaTime();

	if (accumtime > FRAMERATE*2.0f){
		pmon->setState(ONDEAD);		
	}
}

void aiStateDead::exit(mMonster* pmon){

}