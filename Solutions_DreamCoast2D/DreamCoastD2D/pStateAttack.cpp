#include "stdafx.h"
#include "pStateAttack.h"

#include "cResourceManager.h"
#include "cSoundManager.h"
#include "coControl.h"
#include "uSprite.h"

#include "mPlayer.h"
#include "wTileMap.h"
#include "VECTOR2D.h"

#include "pStateMove.h"
#include "pStateAttack.h"
#include "pStateOnCasting.h"
#include "pStateIdle.h"

#include "char_client.h"
#include "netWorkCharManager.h"

//상태진입
void pStateAttack::enter(mPlayer* pplayer){
	pplayer->setState(ONATTACK);
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

	cSoundManager::GetInstance().executeAttack();
	pplayer->setAttackAccumTime(0.0f);

	movePacket toServer;
	toServer.msgtype = ::MESSAGETYPE_ID::PLAYER_ID_UPDATE;
	toServer.id = ::netWorkCharManager::GetInstance().getMyId();
	toServer.mob_type = NMOB_NOT_MOB;
	toServer.state = ONATTACK;
	toServer.px = pplayer->getDrawPos()->x;
	toServer.py = pplayer->getDrawPos()->y;
	toServer.seedir = pplayer->getSeeDir();
	toServer.speed = 0.0;
	toServer.direction = pplayer->getMoveDir();

	::CharCIPMessage::GetInstance().SendMessagePort(toServer);
}

//상태진행
void pStateAttack::execute(mPlayer* pplayer){
	m_sprite->nextFrame(pplayer->getDeltaTime()*pplayer->getAttackSpeed());

	pplayer->dmgToTile(pplayer->getDeltaTime(), pplayer->getAttackPower());

	if (m_sprite->getCurrentFrame() == 7){
		m_sprite->setCurrentFrame(0);
		pplayer->changeStatus(new pStateIdle);
		return;
	}
}
//상태 이탈
void pStateAttack::exit(mPlayer* pplayer){

}