#include "stdafx.h"
#include "niMobStateIdle.h"
#include "mNetworkMob.h"

#include "uSprite.h"

#include "niMobStateMove.h"
#include "niMobStateOnHit.h"
#include "niMobStateOnCasting.h"
#include "niMobStateDead.h"

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

	if (pobj->getCurrentPacket().state == ONHIT){
		pobj->changeState(new niMobStateOnHit);
		return;
	}

	if (pobj->getCurrentPacket().state == ONCASTING){
		pobj->changeState(new niMobStateOnCasting);
		return;
	}

	if (pobj->getCurrentPacket().state == ONDEAD){
		pobj->changeState(new niMobStateDead);
		return;
	}


	m_sprite->nextFrame(pobj->getDelta());
}

void niMobStateIdle::exit(mNetworkMob* pobj){

}