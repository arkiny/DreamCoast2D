#include "stdafx.h"
#include "niMobStateMove.h"
#include "mNetworkMob.h"
#include "VECTOR2D.h"

#include "uSprite.h"
#include "niMobStateIdle.h"


void niMobStateMove::enter(mNetworkMob* pobj){
	m_sprite = pobj->getSprite();
	m_sprite->setCurrentFrame(0);
	pobj->onMove();
}

void niMobStateMove::execute(mNetworkMob* pobj){
	// 이동방향 갱신
	
	pobj->moveToDest(pobj->getDelta());
	pobj->onMove();
	m_sprite->nextFrame(pobj->getDelta());

	if (pobj->getCurrentPacket().state == ONIDLE){
		pobj->changeState(new niMobStateIdle);
		return;
	}
}

void niMobStateMove::exit(mNetworkMob* pobj){

}