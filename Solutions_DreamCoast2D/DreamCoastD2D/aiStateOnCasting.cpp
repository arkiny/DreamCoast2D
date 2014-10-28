#include "stdafx.h"
#include "aiStateOnCasting.h"
#include "mMonster.h"
#include "aiStateSkillEffect.h"
#include "uSprite.h"
#include "cSoundManager.h"

void aiStateOnCasting::enter(mMonster* pmon){
	m_sprite = pmon->getSprite();
	m_sprite->setCurrentFrame(0);
	pmon->onCasting();
	cSoundManager::GetInstance().executeBeginSpell();
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