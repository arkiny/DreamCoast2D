#include "stdafx.h"
#include "niMobStateOnCasting.h"

#include "mNetworkMob.h"
#include "VECTOR2D.h"
#include "uSprite.h"
#include "niMobStateIdle.h"
#include "niMobStateMove.h"
#include "niMobStateOnHit.h"
#include "niMobStateDead.h"

void niMobStateOnCasting::enter(mNetworkMob* pobj){
	m_sprite = pobj->getSprite();
	m_sprite->setCurrentFrame(0);
	pobj->onCasting();
}

void niMobStateOnCasting::execute(mNetworkMob* pobj){
	// 이동방향 갱신
	if (pobj->getCurrentPacket().state == ONIDLE){
		pobj->changeState(new niMobStateIdle);
		return;
	}

	if (pobj->getCurrentPacket().state == ONMOVE){
		pobj->changeState(new niMobStateMove);
		return;
	}

	if (pobj->getCurrentPacket().state == ONHIT){
		pobj->changeState(new niMobStateOnHit);
		return;
	}

	if (pobj->getCurrentPacket().state == ONDEAD){
		pobj->changeState(new niMobStateDead);
		return;
	}

	m_sprite->nextFrame(pobj->getDelta());
}

void niMobStateOnCasting::exit(mNetworkMob* pobj){

}