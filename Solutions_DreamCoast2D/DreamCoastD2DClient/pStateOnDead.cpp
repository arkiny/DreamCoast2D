#include "stdafx.h"
#include "pStateOnDead.h"

#include "uSprite.h"
#include "mPlayer.h"

#include "cResourceManager.h"

//상태진입
void pStateOnDead::enter(mPlayer* pplayer){
	pplayer->setState(ONDEAD);
	m_sprite = pplayer->getSprite();
	m_sprite->setCurrentFrame(0);

	if (pplayer->getSeeDir() == RIGHTDOWN){
		//m_spriteAtlas->pickSpriteAtlas(700.0f, 250.0f, 69.0f, 44.0f, -19.5f, 0.0f, 0);
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(5, 2)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(5, 2)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(5, 2)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(5, 2)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(5, 2)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(5, 2)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(5, 2)->maxFrame);
	}
	else if (pplayer->getSeeDir() == LEFTUP){
		//m_spriteAtlas->pickSpriteAtlas(850.0f, 200.0f, 62.0f, 50.0f, 0);
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(5, 1)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(5, 1)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(5, 1)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(5, 1)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(5, 1)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(5, 1)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(5, 1)->maxFrame);
	}
	else if (pplayer->getSeeDir() == RIGHTUP){
		//m_spriteAtlas->pickSpriteAtlas(850.0f, 250.0f, 62.0f, 50.0f, 0);
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(5, 3)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(5, 3)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(5, 3)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(5, 3)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(5, 3)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(5, 3)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(5, 3)->maxFrame);
	}
	else if (pplayer->getSeeDir() == LEFTDOWN){
		//m_spriteAtlas->pickSpriteAtlas(700.0f, 200.0f, 69.0f, 44.0f, 19.5f, 0.0f, 0);
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(5, 0)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(5, 0)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(5, 0)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(5, 0)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(5, 0)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(5, 0)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(5, 0)->maxFrame);
	}
}

//상태진행
void pStateOnDead::execute(mPlayer* pplayer){
	m_sprite->nextFrame(pplayer->getDeltaTime());

	pplayer->setDeadFadeOutTime(pplayer->getDeadFadeOutTime() + pplayer->getDeltaTime());
	//m_deadFadeOutTime += delta;
	//m_alpha -= 0.025f;
	pplayer->setAlpha(pplayer->getAlpha() - 0.025);
	if (pplayer->getAlpha() <= 0.0f){
		//if (m_alpha <= 0.0f){
		// todo: 페이드아웃 종료후 게임 오버 처리
		pplayer->setDead(true);
	}
}

//상태 이탈
void pStateOnDead::exit(mPlayer* pplayer){

}