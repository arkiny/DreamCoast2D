#include "stdafx.h"
#include "aiStateOnCasting.h"
#include "mMonster.h"
#include "aiStateSkillEffect.h"
#include "uSprite.h"

void aiStateOnCasting::enter(mMonster* pmon){
	m_sprite = pmon->getSprite();
	m_sprite->setCurrentFrame(0);
	pmon->onCasting();
}

void aiStateOnCasting::execute(mMonster* pmon){
	accumcasting += pmon->getdeltaTime();
	if (accumcasting >= castingtime){
		pmon->setSkillAccumtime(0.0f);
		pmon->changeState(new aiStateSkillEffect);
		return;
	}
}

void aiStateOnCasting::exit(mMonster* pmon){

}