#include "stdafx.h"
#include "pStateIdle.h"
#include "uSprite.h"

#include "mPlayer.h"
#include "VECTOR2D.h"

#include "cResourceManager.h"
#include "coControl.h"

#include "pStateOnDead.h"
#include "pStateOnHit.h"
#include "pStateAttack.h"
#include "pStateOnCasting.h"
#include "pStateMove.h"


void pStateIdle::enter(mPlayer* pplayer){
	pplayer->setState(ONIDLE);
	m_sprite = pplayer->getSprite();	

	if (pplayer->getSeeDir() == RIGHTDOWN){
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 2)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 2)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 2)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 2)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 2)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 2)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 2)->maxFrame);
	}
	else if (pplayer->getSeeDir() == LEFTUP){
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 1)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 1)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 1)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 1)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 1)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 1)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 1)->maxFrame);
	}
	else if (pplayer->getSeeDir() == RIGHTUP){
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 3)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 3)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 3)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 3)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 3)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 3)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 3)->maxFrame);
	}
	else if (pplayer->getSeeDir() == LEFTDOWN){
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 0)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 0)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 0)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 0)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 0)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 0)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(0, 0)->maxFrame);
	}
	pplayer->setMoveDir(NOMOVE);
}

void pStateIdle::execute(mPlayer* pplayer){
	//VECTOR2D vMover = VECTOR2D(0.0f, 0.0f);
	

	// 사망시
	if (pplayer->getHealth() <= 0.0f || pplayer->getState() == ONDEAD){
		pplayer->setState(ONDEAD);
		pplayer->changeStatus(new pStateOnDead);
		return;
	}

	// 피격시
	if (pplayer->getState() == ONHIT){
		pplayer->setState(ONHIT);
		pplayer->changeStatus(new pStateOnHit);
		return;
	}

	//

	// 공격키
	if (::coControl::GetInstance().getKeyControlInfo()[0x5A]){
		pplayer->setState(ONATTACK);
		pplayer->changeStatus(new pStateAttack);
		return;
	}

	// 스킬키
	if (::coControl::GetInstance().getKeyControlInfo()[0x58]){
		pplayer->setState(ONCASTING);
		pplayer->changeStatus(new pStateOnCasting);
		return;
	}


	// 이동 키 입력시
	if (::coControl::GetInstance().getKeyControlInfo()[VK_LEFT] &&
		::coControl::GetInstance().getKeyControlInfo()[VK_DOWN]){
		pplayer->setMoveDir(LEFTDOWN);
		pplayer->changeStatus(new pStateMove);
		return;
	}
	else if (::coControl::GetInstance().getKeyControlInfo()[VK_LEFT] &&
		::coControl::GetInstance().getKeyControlInfo()[VK_UP]){
		pplayer->setMoveDir(LEFTUP);	
		pplayer->changeStatus(new pStateMove);
		return;
	}

	else if (::coControl::GetInstance().getKeyControlInfo()[VK_RIGHT] &&
		::coControl::GetInstance().getKeyControlInfo()[VK_DOWN]){
		pplayer->setMoveDir(RIGHTDOWN);	
		pplayer->changeStatus(new pStateMove);
		return;
	}

	else if (::coControl::GetInstance().getKeyControlInfo()[VK_RIGHT] &&
		::coControl::GetInstance().getKeyControlInfo()[VK_UP]){
		pplayer->setMoveDir(RIGHTUP);
		pplayer->changeStatus(new pStateMove);
		return;
	}

	else if (::coControl::GetInstance().getKeyControlInfo()[VK_RIGHT]){
		pplayer->setMoveDir(RIGHT);
		pplayer->changeStatus(new pStateMove);
		return;
	}
	else if (::coControl::GetInstance().getKeyControlInfo()[VK_LEFT]){
		pplayer->setMoveDir(LEFT);
		pplayer->changeStatus(new pStateMove);
		return;
	}
	else if (::coControl::GetInstance().getKeyControlInfo()[VK_DOWN]){
		pplayer->setMoveDir(DOWN);
		pplayer->changeStatus(new pStateMove);
		return;
	}
	else if (::coControl::GetInstance().getKeyControlInfo()[VK_UP]){
		pplayer->setMoveDir(UP);
		pplayer->changeStatus(new pStateMove);
		return;
	}
	//

	// 실행
	m_sprite->nextFrame(pplayer->getDeltaTime());
}

void pStateIdle::exit(mPlayer* pplayer){

}