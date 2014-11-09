#include "stdafx.h"
#include "nStateMove.h"

#include "cResourceManager.h"

#include "nStateIdle.h"
#include "mNetworkObject.h"
#include "uSprite.h"
#include "VECTOR2D.h"

//상태 진입
void nStateMove::enter(mNetworkObject* pobj){
	
	m_sprite = pobj->getSprite();
	m_sprite->setCurrentFrame(0);

	if (pobj->getCurrentPacket().direction == LEFTDOWN){
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 0)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 0)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 0)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 0)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 0)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 0)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 0)->maxFrame);
	}
	else if (pobj->getCurrentPacket().direction == LEFTUP){
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 1)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 1)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 1)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 1)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 1)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 1)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 1)->maxFrame);
	}
	else if (pobj->getCurrentPacket().direction == RIGHTDOWN){
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 2)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 2)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 2)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 2)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 2)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 2)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 2)->maxFrame);
	}
	else if (pobj->getCurrentPacket().direction == RIGHTUP){
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 3)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 3)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 3)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 3)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 3)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 3)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 3)->maxFrame);
	}
	else if (pobj->getCurrentPacket().direction == RIGHT){
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 5)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 5)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 5)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 5)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 5)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 5)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 5)->maxFrame);
	}
	else if (pobj->getCurrentPacket().direction == LEFT){
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 4)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 4)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 4)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 4)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 4)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 4)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 4)->maxFrame);
	}
	else if (pobj->getCurrentPacket().direction == DOWN){
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 7)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 7)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 7)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 7)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 7)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 7)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 7)->maxFrame);
	}
	else if (pobj->getCurrentPacket().direction == UP){
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 6)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 6)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 6)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 6)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 6)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 6)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 6)->maxFrame);
	}
}

//상태진행
void nStateMove::execute(mNetworkObject* pobj){
	if (pobj->getCurrentPacket().state == ONIDLE){
		pobj->changeState(new nStateIdle);
		return;
	}

	// 이동방향 갱신
	if (pobj->getCurrentPacket().direction == LEFTDOWN){
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 0)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 0)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 0)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 0)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 0)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 0)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 0)->maxFrame);
	}
	else if (pobj->getCurrentPacket().direction == LEFTUP){
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 1)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 1)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 1)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 1)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 1)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 1)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 1)->maxFrame);
	}
	else if (pobj->getCurrentPacket().direction == RIGHTDOWN){
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 2)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 2)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 2)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 2)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 2)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 2)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 2)->maxFrame);
	}
	else if (pobj->getCurrentPacket().direction == RIGHTUP){
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 3)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 3)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 3)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 3)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 3)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 3)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 3)->maxFrame);
	}
	else if (pobj->getCurrentPacket().direction == RIGHT){
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 5)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 5)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 5)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 5)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 5)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 5)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 5)->maxFrame);
	}
	else if (pobj->getCurrentPacket().direction == LEFT){
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 4)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 4)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 4)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 4)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 4)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 4)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 4)->maxFrame);
	}
	else if (pobj->getCurrentPacket().direction == DOWN){
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 7)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 7)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 7)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 7)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 7)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 7)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 7)->maxFrame);
	}
	else if (pobj->getCurrentPacket().direction == UP){
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 6)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 6)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 6)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 6)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 6)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 6)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 6)->maxFrame);
	}
	//

	VECTOR2D vMover;
	vMover = pobj->vectorMove(pobj->getDelta(), (DIRECTION)pobj->getCurrentPacket().direction);
	VECTOR2D pos(pobj->getCurrentPacket().px, pobj->getCurrentPacket().py);
	pos = pos + vMover;
	pobj->setPacketPosition(pos.x, pos.y);

	m_sprite->nextFrame(pobj->getDelta());
}

//상태 이탈
void nStateMove::exit(mNetworkObject* pobj){

}