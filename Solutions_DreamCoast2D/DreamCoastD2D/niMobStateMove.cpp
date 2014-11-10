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
	if (pobj->getCurrentPacket().state == ONIDLE){
		pobj->changeState(new niMobStateIdle);
		return;
	}

	// 이동방향 갱신
	pobj->onMove();
	//

	VECTOR2D vMover;
	vMover = pobj->vectorMove(pobj->getDelta(), (DIRECTION)pobj->getCurrentPacket().direction);
	VECTOR2D pos(pobj->getCurrentPacket().px, pobj->getCurrentPacket().py);
	pos = pos + vMover;
	pobj->setPacketPosition(pos.x, pos.y);

	m_sprite->nextFrame(pobj->getDelta());
}

void niMobStateMove::exit(mNetworkMob* pobj){

}