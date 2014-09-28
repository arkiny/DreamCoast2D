#include "stdafx.h"
#include "aiStateScan.h"
#include "aiStateOnHit.h"
#include "aiStateMoveto.h"
#include "aiStateIdle.h"
#include "mMonster.h"
#include "mIObject.h"
#include "VECTOR2D.h"
#include "wTileMap.h"
#include "aiStateAttack.h"
#include "uSprite.h"

void aiStateScan::enter(mMonster* pmon){
	m_sprite = pmon->getSprite();
}

void aiStateScan::execute(mMonster* pmon){
	m_sprite->nextFrame(pmon->getdeltaTime());
	accumtime += pmon->getdeltaTime();

	// ������ ��ĵ�߿� �ĸ����� 
	// �ٽ� ������ �� �Ѥ�
	if (pmon->getState() == ONHIT){
		pmon->changeState(new aiStateOnHit);
	}
	// ��׷� ������ ���������� ���̵� ���·� ���ư�
	// ������ �̵� ó�� ���
	if (pmon->getCurrentAggroLevel() < pmon->getMaxAggroLevel()){
		pmon->setDest(pmon->getRealPos()->x, pmon->getRealPos()->x);
		pmon->changeState(new aiStateIdle);
	}
	// StateAttack���� ����
	bool inSight = pmon->getTileMap()->sightScan(pmon->getSight(), *(pmon->getDrawPos()));
	if (inSight){
		//if(���ݹ�����)
		// 1. ��ĵ�� �÷��̾ �þ߳��� �÷��̾ �ְ�, ���ݹ����� �ϰ��
		if (pmon->getTileMap()->sightScan(pmon->getAttackRange(), *(pmon->getDrawPos()))){
			//�÷��̾� ����
			pmon->changeState(new aiStateAttack);
		}
		else {
			// 2. ��ĵ�� �÷��̾ �þ߳��� �÷��̾ ������
			// ���ݹ��� ���� ���, �����Ÿ����� �̵�
			VECTOR2D playerpos = pmon->getTileMap()->getPlayerTilePos();
			pmon->setDestinTile(playerpos.y, playerpos.x);
			pmon->changeState(new aiStateMoveto);
		}
	}	
	// 3. ��ĵ�� �÷��̾ ���� �ð����� �þ߳��� ���ٸ� 
	// ��׷η��� ����	
	// ������ �̵� ó�� ���
	if (!inSight){
		if (accumtime >= 3.0f){
			pmon->setDest(pmon->getRealPos()->x, pmon->getRealPos()->x);
			pmon->setCurrentAggroLevel(pmon->getCurrentAggroLevel() - 10.0f);
			accumtime = 0;			
		}
	}
}

void aiStateScan::exit(mMonster* pmon){

}


