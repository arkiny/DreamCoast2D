#include "stdafx.h"
#include "niMobStateOnHit.h"

#include "mNetworkMob.h"
#include "VECTOR2D.h"
#include "uSprite.h"
#include "niMobStateIdle.h"
#include "niMobStateMove.h"
#include "niMobStateOnCasting.h"
#include "niMobStateDead.h"



void niMobStateOnHit::enter(mNetworkMob* pobj){
	m_sprite = pobj->getSprite();
	m_sprite->setCurrentFrame(0);
	pobj->onHit();
}

void niMobStateOnHit::execute(mNetworkMob* pobj){
	// 이동방향 갱신
	if (pobj->getCurrentPacket().state == ONIDLE){
		pobj->changeState(new niMobStateIdle);
		return;
	}

	if (pobj->getCurrentPacket().state == ONMOVE){
		pobj->changeState(new niMobStateMove);
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

void niMobStateOnHit::exit(mNetworkMob* pobj){

}