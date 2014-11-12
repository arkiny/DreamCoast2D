#include "stdafx.h"
#include "aiStateOnHit.h"
#include "aiStateIdle.h"
#include "aiStateDead.h"
#include "cSoundManager.h"
#include "uSprite.h"
#include "mMonster.h"

#include "movePacket.h"
#include "netWorkCharManager.h"
#include "char_client.h"
#include "VECTOR2D.h"

void aiStateOnHit::enter(mMonster* pmon){	
	m_sprite = pmon->getSprite();
	pmon->onHit();
	m_sprite->setCurrentFrame(0);
	// 맞은 즉시 어그로레벨 최대화
	pmon->setCurrentAggroLevel(pmon->getMaxAggroLevel());
	cSoundManager::GetInstance().executeOnHit(0);

	movePacket toServer;

	toServer.msgtype = ::MESSAGETYPE_ID::MOB_ID_UPDATE;
	toServer.id = ::netWorkCharManager::GetInstance().getMyId();
	toServer.mob_uniq_id = pmon->getMobID();
	toServer.mob_type = pmon->getMonsterType();
	toServer.state = ONHIT;
	toServer.px = pmon->getDrawPos()->x;
	toServer.py = pmon->getDrawPos()->y;
	toServer.dx = pmon->getDest()->x;
	toServer.dy = pmon->getDest()->y;
	toServer.seedir = pmon->getDir();
	toServer.speed = pmon->getMoveSpeed();
	toServer.direction = pmon->getDir();

	::CharCIPMessage::GetInstance().SendMessagePort(toServer);

}

void aiStateOnHit::execute(mMonster* pmon){
	// frame이 다 출력되면 대기모드로 들어감
	m_sprite->nextFrame(pmon->getdeltaTime());	
	accumtime += pmon->getdeltaTime();
	
	if (pmon->getHealth() <= 0.0f){
		pmon->changeState(new aiStateDead);
		return;
	} 
	else if (accumtime > FRAMERATE*2.0f){
		pmon->setState(ONIDLE);
		pmon->changeState(new aiStateIdle);
	}
}

void aiStateOnHit::exit(mMonster* pmon){
	pmon->setDmg(0.0f);
}