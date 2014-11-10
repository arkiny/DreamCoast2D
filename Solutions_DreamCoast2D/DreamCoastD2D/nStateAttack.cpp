#include "stdafx.h"
#include "nStateAttack.h"

#include "cResourceManager.h"
#include "cSoundManager.h"

#include "nStateIdle.h"
#include "nStateMove.h"

#include "mNetworkObject.h"
#include "uSprite.h"

//상태 진입
void nStateAttack::enter(mNetworkObject* pobj){
	m_sprite = pobj->getSprite();
	m_sprite->setCurrentFrame(0);

	if (pobj->getCurrentPacket().seedir == LEFTDOWN){
		//m_spriteAtlas->pickSpriteAtlas(0.0f, 600.0f, 121.0f, 98.0f, 19.5f, 0.0f, 7);
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(2, 0)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(2, 0)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(2, 0)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(2, 0)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(2, 0)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(2, 0)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(2, 0)->maxFrame);
	}
	else if (pobj->getCurrentPacket().seedir == LEFTUP){
		//m_spriteAtlas->pickSpriteAtlas(0.0f, 700.0f, 103.0f, 84.0f, 7);
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(2, 1)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(2, 1)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(2, 1)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(2, 1)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(2, 1)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(2, 1)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(2, 1)->maxFrame);
	}
	else if (pobj->getCurrentPacket().seedir == RIGHTDOWN){
		//m_spriteAtlas->pickSpriteAtlas(0.0f, 800.0f, 121.0f, 98.0f, -19.5f, 0.0f, 7);
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(2, 2)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(2, 2)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(2, 2)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(2, 2)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(2, 2)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(2, 2)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(2, 2)->maxFrame);
	}
	else if (pobj->getCurrentPacket().seedir == RIGHTUP){
		//m_spriteAtlas->pickSpriteAtlas(0.0f, 900.0f, 103.0f, 84.0f, 7);
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(2, 3)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(2, 3)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(2, 3)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(2, 3)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(2, 3)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(2, 3)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(2, 3)->maxFrame);
	}

	cSoundManager::GetInstance().executeAttack();
}

//상태진행
void nStateAttack::execute(mNetworkObject* pobj){
	if (pobj->getCurrentPacket().state == ONMOVE){
		pobj->changeState(new nStateMove);
		return;
	}

	if (pobj->getCurrentPacket().state == ONIDLE){
		pobj->changeState(new nStateIdle);
		return;
	}

	m_sprite->nextFrame(pobj->getDelta());
}

//상태 이탈
void nStateAttack::exit(mNetworkObject* pobj){

}