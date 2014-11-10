#include "stdafx.h"
#include "aiStateScan.h"
#include "aiStateOnHit.h"
#include "aiStateMoveto.h"
#include "aiStateIdle.h"
#include "aiStateOnCasting.h"
#include "mMonster.h"
#include "VECTOR2D.h"
#include "wTileMap.h"
#include "aiStateAttack.h"
#include "uSprite.h"
#include "aiStateDead.h"

void aiStateScan::enter(mMonster* pmon){
	m_sprite = pmon->getSprite();
	pmon->onIdle();
}

void aiStateScan::execute(mMonster* pmon){
	m_sprite->nextFrame(pmon->getdeltaTime());
	accumtime += pmon->getdeltaTime();


	if (pmon->getHealth() <= 0.0f){
		pmon->changeState(new aiStateDead);
		return;
	}
	// ������ ��ĵ�߿� �ĸ����� 
	// �ٽ� ������ �� �Ѥ�
	if (pmon->getState() == ONHIT){
		pmon->changeState(new aiStateOnHit);
		return;
	}
	// ��׷� ������ ���������� ���̵� ���·� ���ư�
	// ������ �̵� ó�� ���
	if (pmon->getCurrentAggroLevel() < pmon->getMaxAggroLevel()){
		pmon->setDest(pmon->getRealPos()->x, pmon->getRealPos()->x);
		pmon->changeState(new aiStateIdle);
		return;
	}
	// StateAttack���� ����
	bool inSight = pmon->getTileMap()->sightScan(pmon->getSight(), *(pmon->getDrawPos()));
	if (inSight){
		//if(���ݹ�����)
		// 2. ��ĵ�� �÷��̾ �þ߳��� �÷��̾ �ְ�, ��ų�� �غ�Ǿ� �ִ� ���
		if (pmon->getTileMap()->sightScan(pmon->getAttackRange(), *(pmon->getDrawPos())) &&
			pmon->getSkillAccumtime() >= pmon->getSkillCooltime() ){
			pmon->changeState(new aiStateOnCasting);
		}
			// 2. ��ĵ�� �÷��̾ �þ߳��� �÷��̾ �ְ�, ���ݹ����� �ϰ��
		else if (pmon->getTileMap()->sightScan(pmon->getAttackRange(), *(pmon->getDrawPos()))){
			//�÷��̾� ����
			pmon->changeState(new aiStateAttack);
			return;
		}
		else {
			// 2. ��ĵ�� �÷��̾ �þ߳��� �÷��̾ ������
			// ���ݹ��� ���� ���, �����Ÿ����� �̵�
			VECTOR2D playerpos = pmon->getTileMap()->getPlayerTilePos();
			pmon->setDestinTile(playerpos.y, playerpos.x);
			pmon->changeState(new aiStateMoveto);
			return;
		}
	}	
	// 3. ��ĵ�� �÷��̾ ���� �ð����� �þ߳��� ���ٸ� 
	// ��׷η��� ����	
	// ������ �̵� ó�� ���
	
	if (!inSight){
		//if (pmon->getMonsterType() == 0){ // �нú��� ��
		if (accumtime >= 3.0f){
			pmon->setDest(pmon->getRealPos()->x, pmon->getRealPos()->y);
			pmon->setCurrentAggroLevel(pmon->getCurrentAggroLevel() - 10.0f);
			accumtime = 0;				
			pmon->changeState(new aiStateIdle);
		}
	}
}

void aiStateScan::exit(mMonster* pmon){

}


