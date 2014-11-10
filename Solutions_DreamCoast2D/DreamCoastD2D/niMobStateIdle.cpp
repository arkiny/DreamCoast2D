#include "stdafx.h"
#include "niMobStateIdle.h"
#include "mNetworkMob.h"

#include "uSprite.h"
#include "niMobStateMove.h"

void niMobStateIdle::enter(mNetworkMob* pobj){
	m_sprite = pobj->getSprite();
	m_sprite->setCurrentFrame(0);
	pobj->onIdle();
}

void niMobStateIdle::execute(mNetworkMob* pobj){
	if (pobj->getCurrentPacket().state == ONMOVE){
		pobj->changeState(new niMobStateMove);
		return;
	}
	m_sprite->nextFrame(pobj->getDelta());
}

void niMobStateIdle::exit(mNetworkMob* pobj){

}