#include "stdafx.h"
#include "cSoundManager.h"
#include "aiStateDead.h"
#include "aiStateOnHit.h"
#include "aiStateIdle.h"
#include "aiStateDead.h"
#include "uSprite.h"
#include "mMonster.h"

#include "movePacket.h"
#include "netWorkCharManager.h"
#include "char_client.h"
#include "VECTOR2D.h"


void aiStateDead::enter(mMonster* pmon){
	m_sprite = pmon->getSprite();
	pmon->onDeath();
	m_sprite->setCurrentFrame(0);
	cSoundManager::GetInstance().executeOnDie(0);

	movePacket toServer;

	toServer.msgtype = ::MESSAGETYPE_ID::MOB_ID_UPDATE;
	toServer.id = ::netWorkCharManager::GetInstance().getMyId();
	toServer.mob_uniq_id = pmon->getMobID();
	toServer.mob_type = pmon->getMonsterType();
	toServer.state = ONDEAD;
	toServer.px = pmon->getDrawPos()->x;
	toServer.py = pmon->getDrawPos()->y;
	toServer.dx = pmon->getDest()->x;
	toServer.dy = pmon->getDest()->y;
	toServer.seedir = pmon->getDir();
	toServer.speed = pmon->getMoveSpeed();
	toServer.direction = pmon->getDir();

	::CharCIPMessage::GetInstance().SendMessagePort(toServer);
}

void aiStateDead::execute(mMonster* pmon){
	accumtime += pmon->getdeltaTime();
	if (accumtime < FRAMERATE * 1.0f){
		m_sprite->nextFrame(pmon->getdeltaTime());
	}

	// ����� ���̵�ƿ� ȿ��
	pmon->setAlpha(pmon->getAlpha() - 0.025f);

	// ���� delete ���ٴ� setVisible�� �̿��ؼ�
	// �ٽ� �̿��ϴ� ����� ���� �� �ϵ��̴�
	// ���� �ð��� ���� �� ���� trigger on
	if (accumtime > FRAMERATE*8.0f){
		pmon->setState(ONDEAD);		
	}
}

void aiStateDead::exit(mMonster* pmon){

}