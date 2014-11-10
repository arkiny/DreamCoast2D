#include "stdafx.h"
#include "aiStateIdle.h"
#include "mMonster.h"
#include "uSprite.h"
#include "wTileMap.h"
#include "aiStateOnHit.h"
#include "aiStateMoveto.h"
#include "aiStateScan.h"
#include "aiStateDead.h"
#include "VECTOR2D.h"

#include "movePacket.h"
#include "char_client.h"
#include "netWorkCharManager.h"

void aiStateIdle::enter(mMonster* pmon){
	// todo:: sprite setter�� object�� �߰�����
	// idling sprite�� ���� (���� �ִ� ���⸶��)
	// pointer initial �Ҷ� ����ϳ�?
	m_sprite = pmon->getSprite();
	pmon->onIdle();

	movePacket toServer;

	toServer.msgtype = ::MESSAGETYPE_ID::MOB_ID_UPDATE;
	toServer.id = ::netWorkCharManager::GetInstance().getMyId();
	toServer.mob_uniq_id = pmon->getMobID();
	toServer.mob_type = pmon->getMonsterType();
	toServer.state = ONIDLE;
	toServer.px = pmon->getDrawPos()->x;
	toServer.py = pmon->getDrawPos()->y;
	toServer.seedir = pmon->getDir();
	toServer.speed = 0.0;
	toServer.direction = pmon->getDir();

	::CharCIPMessage::GetInstance().SendMessagePort(toServer);
}

void aiStateIdle::execute(mMonster* pmon){
	// state�ȿ� Ư���� ���� �������ִ� �� ������, �������� ���� ������
	//
	accumtime += pmon->getdeltaTime();
	// �̵��� �����Ƿ� nextFrame�� �ǽ�	
	m_sprite->nextFrame(pmon->getdeltaTime());
	
	if (pmon->getHealth() <= 0.0f){
		pmon->changeState(new aiStateDead);
		return;
	}

	// �뷫 6�ʸ��� ���� �������� �̵�
	if (accumtime > 6.0f){
		pmon->moveRandom();
	}
		
	// �� ���߿� ���� �߰��Ǹ� ü��ȸ���� �־��
	// 1. �ǰ� �ֿ켱
	if (pmon->getState() == ONHIT){
		pmon->changeState(new aiStateOnHit);
		return;
	} 

	// ��׷� ���� üũ,
	// ���� ��׷� ������ Ʈ���� �������� ���ٸ�
	// �þ߰Ÿ����� �÷��̾ �ִ��� ��ĵ
	// Todo: ���� Idle���¿��� ���� �ֺ��� ��׷� ������ ���� ���
	// Aggro������ �ø��� �Լ� �߰�

	// �нú��� ���Ͱ� �ƴ� ��� �þ߳��� ���� ������ ��׷� �ƽ�
	bool inSight = pmon->getTileMap()->sightScan(pmon->getSight(), *(pmon->getDrawPos()));
	if (pmon->getMonsterType() != 0 && inSight){
		pmon->setCurrentAggroLevel(pmon->getMaxAggroLevel());
	}

	if (pmon->getCurrentAggroLevel() >= pmon->getMaxAggroLevel()){
		pmon->changeState(new aiStateScan);
		return;
	}

	// �̵� ��ǥ üũ
	if (*(pmon->getRealPos()) != *(pmon->getDest())){
		pmon->changeState(new aiStateMoveto);
		return;
	}
}

void aiStateIdle::exit(mMonster* pmon){

}