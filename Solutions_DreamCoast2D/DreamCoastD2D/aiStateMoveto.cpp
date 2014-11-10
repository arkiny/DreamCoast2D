#include "stdafx.h"
#include "aiStateMoveto.h"
#include "aiStateOnHit.h"
#include "aiStateIdle.h"
#include "aiStateScan.h"
#include "aiStateDead.h"
#include "uSprite.h"
#include "mMonster.h"
#include "wTileMap.h"
#include "VECTOR2D.h"

#include "movePacket.h"
#include "char_client.h"
#include "netWorkCharManager.h"

void aiStateMoveto::enter(mMonster* pmon)
{
	m_sprite = pmon->getSprite();
	pmon->onMove();

	movePacket toServer;

	toServer.msgtype = ::MESSAGETYPE_ID::MOB_ID_UPDATE;
	toServer.id = ::netWorkCharManager::GetInstance().getMyId();
	toServer.mob_uniq_id = pmon->getMobID();
	toServer.mob_type = pmon->getMonsterType();
	toServer.state = ONMOVE;
	toServer.px = pmon->getDrawPos()->x;
	toServer.py = pmon->getDrawPos()->y;
	toServer.dx = pmon->getDest()->x;
	toServer.dy = pmon->getDest()->y;
	toServer.seedir = pmon->getDir();
	toServer.speed = pmon->getMoveSpeed();
	toServer.direction = pmon->getDir();

	::CharCIPMessage::GetInstance().SendMessagePort(toServer);
}


void aiStateMoveto::execute(mMonster* pmon)
{
	accumtime += pmon->getdeltaTime();
	m_sprite->nextFrame(pmon->getdeltaTime());
	pmon->moveToDest(pmon->getdeltaTime());

	// ���� ��׷ΰ� �����ִ� ����(�������϶��� �ֱ������� ��ĵ)
	// �� �̵��� ��ĵ�� �ϴ� ���� �ӵ������� �������� ȿ���� ����
	// �׷��� ���� �ð����� ��ĵ�ϰ� Ʈ���� ����
	if (pmon->getHealth() <= 0.0f){
		pmon->changeState(new aiStateDead);
		return;
	}

	/*if (pmon->getCurrentAggroLevel() >= pmon->getMaxAggroLevel()){
		accumtime = 0;
		pmon->changeState(new aiStateScan);
	}*/


	bool inSight = pmon->getTileMap()->sightScan(pmon->getSight(), *(pmon->getDrawPos()));
	if (pmon->getMonsterType() != 0 && inSight){
		pmon->setCurrentAggroLevel(pmon->getMaxAggroLevel());
	}
	
	if (pmon->getCurrentAggroLevel() >= pmon->getMaxAggroLevel()
		&& accumtime >= 1.0f){
		accumtime = 0;
		pmon->changeState(new aiStateScan);
	} 


	if (*(pmon->getRealPos()) == *(pmon->getDest())){
		pmon->changeState(new aiStateIdle);
		pmon->setState(ONIDLE);
	}
	
	if (pmon->getState() == ONHIT){
		pmon->changeState(new aiStateOnHit);
	}
}

void aiStateMoveto::exit(mMonster* pmon)
{
}
