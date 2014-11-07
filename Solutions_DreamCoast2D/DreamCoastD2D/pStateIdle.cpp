#include "stdafx.h"
#include "pStateIdle.h"
#include "mPlayer.h"

void pStateIdle::enter(mPlayer* pplayer){
	m_sprite = pplayer->getSprite();
	
	//if (m_SeeDir == RIGHTDOWN){
	//	// idle right down
	//	m_spriteAtlas->pickSpriteAtlas(
	//		cResourceManager::GetInstance().getPlayerSpriteInfo(0, 2)->x,
	//		cResourceManager::GetInstance().getPlayerSpriteInfo(0, 2)->y,
	//		cResourceManager::GetInstance().getPlayerSpriteInfo(0, 2)->width,
	//		cResourceManager::GetInstance().getPlayerSpriteInfo(0, 2)->height,
	//		cResourceManager::GetInstance().getPlayerSpriteInfo(0, 2)->offsetX,
	//		cResourceManager::GetInstance().getPlayerSpriteInfo(0, 2)->offsetY,
	//		cResourceManager::GetInstance().getPlayerSpriteInfo(0, 2)->maxFrame);
	//}
	//else if (m_SeeDir == LEFTUP){
	//	m_spriteAtlas->pickSpriteAtlas(
	//		cResourceManager::GetInstance().getPlayerSpriteInfo(0, 1)->x,
	//		cResourceManager::GetInstance().getPlayerSpriteInfo(0, 1)->y,
	//		cResourceManager::GetInstance().getPlayerSpriteInfo(0, 1)->width,
	//		cResourceManager::GetInstance().getPlayerSpriteInfo(0, 1)->height,
	//		cResourceManager::GetInstance().getPlayerSpriteInfo(0, 1)->offsetX,
	//		cResourceManager::GetInstance().getPlayerSpriteInfo(0, 1)->offsetY,
	//		cResourceManager::GetInstance().getPlayerSpriteInfo(0, 1)->maxFrame);
	//}
	//else if (m_SeeDir == RIGHTUP){
	//	//m_spriteAtlas->pickSpriteAtlas(360.0f, 500.0f, 42.0f, 89.0f, 4);
	//	m_spriteAtlas->pickSpriteAtlas(
	//		cResourceManager::GetInstance().getPlayerSpriteInfo(0, 3)->x,
	//		cResourceManager::GetInstance().getPlayerSpriteInfo(0, 3)->y,
	//		cResourceManager::GetInstance().getPlayerSpriteInfo(0, 3)->width,
	//		cResourceManager::GetInstance().getPlayerSpriteInfo(0, 3)->height,
	//		cResourceManager::GetInstance().getPlayerSpriteInfo(0, 3)->offsetX,
	//		cResourceManager::GetInstance().getPlayerSpriteInfo(0, 3)->offsetY,
	//		cResourceManager::GetInstance().getPlayerSpriteInfo(0, 3)->maxFrame);
	//}
	//else if (m_SeeDir == LEFTDOWN){
	//	//SpriteAnimationInfo a = *cResourceManager::GetInstance().getPlayerSpriteInfo(0, 0);
	//	m_spriteAtlas->pickSpriteAtlas(
	//		cResourceManager::GetInstance().getPlayerSpriteInfo(0, 0)->x,
	//		cResourceManager::GetInstance().getPlayerSpriteInfo(0, 0)->y,
	//		cResourceManager::GetInstance().getPlayerSpriteInfo(0, 0)->width,
	//		cResourceManager::GetInstance().getPlayerSpriteInfo(0, 0)->height,
	//		cResourceManager::GetInstance().getPlayerSpriteInfo(0, 0)->offsetX,
	//		cResourceManager::GetInstance().getPlayerSpriteInfo(0, 0)->offsetY,
	//		cResourceManager::GetInstance().getPlayerSpriteInfo(0, 0)->maxFrame);
	//	//m_spriteAtlas->pickSpriteAtlas(0.0f, 500.0f, 64.0f, 92.0f, 19.5f, 0.0f, 4);
	//}
	//m_MoveDir = NOMOVE;	
	//pplayer->onIdle();
}

void pStateIdle::execute(mPlayer* pplayer){

}

void pStateIdle::exit(mPlayer* pplayer){

}