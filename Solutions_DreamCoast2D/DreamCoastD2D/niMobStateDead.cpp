#include "stdafx.h"
#include "niMobStateDead.h"

#include "IGObject.h"
#include "netWorkCharManager.h"
#include "cSoundManager.h"

#include "uSprite.h"
#include "mNetworkMob.h"
#include "niMobStateDead.h"

void niMobStateDead::enter(mNetworkMob* pobj){
	m_sprite = pobj->getSprite();
	m_sprite->setCurrentFrame(0);
	pobj->onDeath();

	/*m_sprite = pmon->getSprite();
	pmon->onDeath();
	m_sprite->setCurrentFrame(0);*/
	cSoundManager::GetInstance().executeOnDie(0);
}

void niMobStateDead::execute(mNetworkMob* pobj){
	accumtime += pobj->getDelta();
	if (accumtime < FRAMERATE * 1.0f){
		m_sprite->nextFrame(pobj->getDelta());
	}

	pobj->setAlpha(pobj->getAlpha() - 0.025f);

	if (accumtime > FRAMERATE*8.0f){
		netWorkCharManager::GetInstance().removeFromMobList(pobj->getCurrentPacket().mob_uniq_id);
		return;
	}
}

void niMobStateDead::exit(mNetworkMob* pobj){

}