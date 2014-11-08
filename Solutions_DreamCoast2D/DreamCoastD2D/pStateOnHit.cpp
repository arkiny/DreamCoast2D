#include "stdafx.h"
#include "pStateOnHit.h"

#include "mPlayer.h"
#include "cResourceManager.h"
#include "uSprite.h"

#include "pStateOnDead.h"
#include "pStateIdle.h"

//상태진입
void pStateOnHit::enter(mPlayer* pplayer){
	m_sprite = pplayer->getSprite();
	pplayer->setState(ONHIT);
	m_sprite->setCurrentFrame(0);

	if (pplayer->getSeeDir() == LEFTDOWN){
		//m_spriteAtlas->pickSpriteAtlas(700.0f, 0.0f, 49.0f, 73.0f, 1);
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(4, 0)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(4, 0)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(4, 0)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(4, 0)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(4, 0)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(4, 0)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(4, 0)->maxFrame);
	}
	else if (pplayer->getSeeDir() == LEFTUP){
		//m_spriteAtlas->pickSpriteAtlas(850.0f, 0.0f, 48.0f, 74.0f, 1);
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(4, 1)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(4, 1)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(4, 1)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(4, 1)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(4, 1)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(4, 1)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(4, 1)->maxFrame);
	}
	else if (pplayer->getSeeDir() == RIGHTDOWN){
		//m_spriteAtlas->pickSpriteAtlas(700.0f, 100.0f, 49.0f, 73.0f, 1);
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(4, 2)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(4, 2)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(4, 2)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(4, 2)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(4, 2)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(4, 2)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(4, 2)->maxFrame);
	}
	else if (pplayer->getSeeDir() == RIGHTUP){
		//m_spriteAtlas->pickSpriteAtlas(850.0f, 100.0f, 48.0f, 74.0f, 1);
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(4, 3)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(4, 3)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(4, 3)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(4, 3)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(4, 3)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(4, 3)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(4, 3)->maxFrame);
	}

}
//상태진행
void pStateOnHit::execute(mPlayer* pplayer){

	m_sprite->nextFrame(pplayer->getDeltaTime());

	if (pplayer->getHealth() <= 0.0f || pplayer->getState() == ONDEAD){
		pplayer->setState(ONDEAD);
		pplayer->changeStatus(new pStateOnDead);
		return;
	}

	if (pplayer->getOnhitAccumTime() < FRAMERATE * 2.0f){
		pplayer->setOnhitAccumTime(pplayer->getOnhitAccumTime() + pplayer->getDeltaTime());
	}
	else {
		// 맞은 이후 일정 시간이 지났을 경우
		// Idle상태로 돌아감
		pplayer->setOnhitAccumTime(0.0f);
		pplayer->setDmg(0.0f);
		pplayer->changeStatus(new pStateIdle);
		return;		
	}
}
//상태 이탈
void pStateOnHit::exit(mPlayer* pplayer){

}