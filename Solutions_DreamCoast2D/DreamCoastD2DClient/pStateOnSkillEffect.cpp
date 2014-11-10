#include "stdafx.h"
#include "pStateOnSkillEffect.h"
#include "cResourceManager.h"
#include "cSoundManager.h"
#include "coControl.h"
#include "uSprite.h"

#include "mPlayer.h"
#include "wTileMap.h"
#include "VECTOR2D.h"

#include "pStateIdle.h"
#include "pStateOnSkillEffect.h"


//상태진입
void pStateOnSkillEffect::enter(mPlayer* pplayer){
	
	pplayer->setState(ONSKILLEFFECTING);
	pplayer->setMP(pplayer->getMP() - 10.0f);
	m_sprite = pplayer->getSprite();
	m_sprite->setCurrentFrame(0);

	if (pplayer->getSeeDir() == LEFTDOWN){
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
	else if (pplayer->getSeeDir() == LEFTUP){
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
	else if (pplayer->getSeeDir() == RIGHTDOWN){
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
	else if (pplayer->getSeeDir() == RIGHTUP){
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
	pplayer->setAttackAccumTime(0.0f);

	// Effect manage
	VECTOR2D currentTile = pplayer->getTileMap()->getTileCoordinates(*pplayer->getRealPos());
	VECTOR2D iso;
	switch (pplayer->getCastingSkill())
	{
	case 0:

		pplayer->effectToArea(pplayer->getDeltaTime(), 0, AREA_TYPE1);
		break;
	case 1:
		pplayer->effectToTile(pplayer->getDeltaTime(), 0);
		break;
	default:
		break;
	}

	//
	cSoundManager::GetInstance().executeSkill(pplayer->getCastingSkill());
}
//상태진행
void pStateOnSkillEffect::execute(mPlayer* pplayer){
	
	//pplayer->dmgToArea(pplayer->getDeltaTime(), pplayer->getAttackPower(), AREA_TYPE1);
	switch (pplayer->getCastingSkill())
	{
	case 0:{
		pplayer->dmgToArea(pplayer->getDeltaTime(), pplayer->getAttackPower(), AREA_TYPE1);
		break;
	}
	case 1:{
		pplayer->dmgToTile(pplayer->getDeltaTime(), pplayer->getAttackPower()*10.0f);
		break;
	}
	default:
		break;
	}


	if (m_sprite->getCurrentFrame() == 7){
		m_sprite->setCurrentFrame(0);
		pplayer->changeStatus(new pStateIdle);
		return;
	}

	m_sprite->nextFrame(pplayer->getDeltaTime()*pplayer->getAttackSpeed());

}
//상태 이탈
void pStateOnSkillEffect::exit(mPlayer* pplayer){

}