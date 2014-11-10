#include "stdafx.h"

#include "cResourceManager.h"

#include "nStateIdle.h"
#include "nStateMove.h"
#include "nStateAttack.h"

#include "mNetworkObject.h"
#include "uSprite.h"

//상태 진입
void nStateIdle::enter(mNetworkObject* pobj){
	m_sprite = pobj->getSprite();
	m_sprite->setCurrentFrame(0);

	if (pobj->getCurrentPacket().seedir == RIGHTDOWN){
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 2)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 2)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 2)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 2)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 2)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 2)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 2)->maxFrame);
	}
	else if (pobj->getCurrentPacket().seedir == LEFTUP){
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 1)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 1)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 1)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 1)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 1)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 1)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 1)->maxFrame);
	}
	else if (pobj->getCurrentPacket().seedir == RIGHTUP){
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 3)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 3)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 3)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 3)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 3)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 3)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 3)->maxFrame);
	}
	else if (pobj->getCurrentPacket().seedir == LEFTDOWN){
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 0)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 0)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 0)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 0)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 0)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 0)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 0)->maxFrame);
	}
}

//상태진행
void nStateIdle::execute(mNetworkObject* pobj){
	if (pobj->getCurrentPacket().state == ONMOVE){
		pobj->changeState(new nStateMove);
		return;
	}

	if (pobj->getCurrentPacket().state == ONATTACK){
		pobj->changeState(new nStateAttack);
		return;
	}

	m_sprite->nextFrame(pobj->getDelta());
}

//상태 이탈
void nStateIdle::exit(mNetworkObject* pobj){

}