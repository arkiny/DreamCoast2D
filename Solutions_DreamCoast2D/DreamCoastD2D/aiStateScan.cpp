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

	// 하지만 스캔중에 쳐맞으면 
	// 다시 경직에 들어감 ㅡㅡ
	if (pmon->getState() == ONHIT){
		pmon->changeState(new aiStateOnHit);
	}
	// 어그로 레벨이 떨어졌을시 아이들 상태로 돌아감
	if (pmon->getCurrentAggroLevel() < pmon->getMaxAggroLevel()){
		pmon->changeState(new aiStateIdle);
	}
	// StateAttack으로 이행
	bool inSight = pmon->getTileMap()->sightScan(pmon->getSight(), *(pmon->getDrawPos()));
	if (inSight){
		//if(공격범위내)
		// 1. 스캔시 플레이어가 시야내에 플레이어가 있고, 공격범위내 일경우
		if (pmon->getTileMap()->sightScan(pmon->getAttackRange(), *(pmon->getDrawPos()))){
			//플레이어 공격
			pmon->changeState(new aiStateAttack);
		}
		else {
			// 2. 스캔시 플레이어가 시야내에 플레이어가 있지만
			// 공격범위 밖일 경우, 사정거리내로 이동
			VECTOR2D playerpos = pmon->getTileMap()->getPlayerTilePos();
			pmon->setDestinTile(playerpos.y, playerpos.x);
			pmon->changeState(new aiStateMoveto);
		}
	}	
	// 3. 스캔시 플레이어가 일정 시간동안 시야내에 없다면 
	// 어그로레벨 감소	
	if (!inSight){
		if (accumtime >= 3.0f){
			pmon->setCurrentAggroLevel(pmon->getCurrentAggroLevel() - 10.0f);
			accumtime = 0;			
		}
	}
}

void aiStateScan::exit(mMonster* pmon){

}


