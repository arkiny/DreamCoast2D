#include "stdafx.h"
#include "pStateOnCasting.h"

#include "cResourceManager.h"
#include "cSoundManager.h"
#include "coControl.h"
#include "uSprite.h"

#include "mPlayer.h"
#include "wTileMap.h"
#include "VECTOR2D.h"

#include "pStateMove.h"
#include "pStateAttack.h"
#include "pStateIdle.h"
#include "pStateOnSkillEffect.h"
#include "pStateOnHit.h"

//상태진입
void pStateOnCasting::enter(mPlayer* pplayer){
	pplayer->setState(ONCASTING);
	m_sprite = pplayer->getSprite();
	m_sprite->setCurrentFrame(0);
	if (pplayer->getSeeDir() == LEFTDOWN){
		//m_spriteAtlas->pickSpriteAtlas(880.0f, 300.0f, 50.0f, 89.0f, 10.5f, 0.0f, 0);
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 0)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 0)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 0)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 0)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 0)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 0)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 0)->maxFrame);
	}
	else if (pplayer->getSeeDir() == LEFTUP){
		//m_spriteAtlas->pickSpriteAtlas(950.0f, 300.0f, 46.0f, 85.0f, 0);
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 1)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 1)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 1)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 1)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 1)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 1)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 1)->maxFrame);
	}
	else if (pplayer->getSeeDir() == RIGHTDOWN){
		//m_spriteAtlas->pickSpriteAtlas(880.0f, 400.0f, 50.0f, 89.0f, -10.5f, 0.0f, 0);
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 2)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 2)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 2)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 2)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 2)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 2)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 2)->maxFrame);
	}
	else if (pplayer->getSeeDir() == RIGHTUP){
		//m_spriteAtlas->pickSpriteAtlas(950.0f, 400.0f, 46.0f, 85.0f, 0);
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 3)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 3)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 3)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 3)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 3)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 3)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 3)->maxFrame);
	}

	cSoundManager::GetInstance().executeBeginSpell();
	pplayer->putKeyIntoQueue();
}
//상태진행
void pStateOnCasting::execute(mPlayer* pplayer){
	m_sprite->nextFrame(pplayer->getDeltaTime());
	pplayer->putKeyIntoQueue();

	if (pplayer->getState() == ONHIT){
		while (!pplayer->getKeyInput().empty()){
			pplayer->getKeyInput().pop();
		}
		pplayer->setState(ONHIT);
		pplayer->changeStatus(new pStateOnHit);
		return;
	}

	if (!::coControl::GetInstance().getKeyControlInfo()[0x58]){
		// TODO: 키를 떼었을때 캐스팅 사운드 멈추기
		cSoundManager::GetInstance().stopBeginSpell();

		// 입력 된 키를 기술표와 비교하여 기술표에 존재할 경우 해당 스킬을,
		// 아닐경우에는 패널티를 부여한다. (자기에게 데미지)
		// 스킬 발사시, 공격모션과 동일안 모션을 취하는 대신,
		// 자기주변으로 스킬에 관련된 이펙트를 표현해야한다.

		// 업데이트 시마다 체크하게 되므로 문제가 된다.
		// TODO 업데이트 타임 체크
		if (!pplayer->getKeyInput().empty()){
			for (unsigned int i = 0; i < pplayer->getSkillList().size(); i++){
				std::queue<int> temp = pplayer->getKeyInput();
				if (pplayer->skillCompare(temp, pplayer->getSkillList()[i], 0)){
					pplayer->setCastingSkill(i);
					break;
				}
			}

			if (pplayer->getCastingSkill() == 99) {
				// 아니면 페널티를 주는 걸로
				pplayer->getHit(10.0f);
			}

			while (!pplayer->getKeyInputPointer()->empty()){
				pplayer->getKeyInputPointer()->pop();
			}
		}
		else {
			if (pplayer->getCastingSkill() != 99){
				// skill에따른 스킬 시전
				if (pplayer->getMP() >= 10.0f){
					//
					pplayer->setState(ONSKILLEFFECTING);
					pplayer->changeStatus(new pStateOnSkillEffect);	
				}
				else{
					// 마나 없을때 페널티
					pplayer->getHit(10.0f);
				}
			}
			else {
				pplayer->setState(ONIDLE);
				pplayer->changeStatus(new pStateIdle);
			}
		}
	}
}
//상태 이탈
void pStateOnCasting::exit(mPlayer* pplayer){

}