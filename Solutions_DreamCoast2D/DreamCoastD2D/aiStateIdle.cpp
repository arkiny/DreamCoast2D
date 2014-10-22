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

void aiStateIdle::enter(mMonster* pmon){
	// todo:: sprite setter를 object에 추가한후
	// idling sprite를 설정 (보고 있는 방향마다)
	// pointer initial 할때 써야하나?
	m_sprite = pmon->getSprite();
	pmon->onIdle();
}

void aiStateIdle::execute(mMonster* pmon){
	// state안에 특정한 영역 지정해주는 게 있으면, 범용으로 쓸수 없어짐
	//
	accumtime += pmon->getdeltaTime();
	// 이동이 없으므로 nextFrame만 실시	
	m_sprite->nextFrame(pmon->getdeltaTime());
	
	if (pmon->getHealth() <= 0.0f){
		pmon->changeState(new aiStateDead);
		return;
	}

	// 대략 6초마다 랜덤 방향으로 이동
	if (accumtime > 6.0f){
		pmon->moveRandom();
	}
		
	// 뭐 나중에 전투 추가되면 체력회복도 넣어보고
	// 1. 피격 최우선
	if (pmon->getState() == ONHIT){
		pmon->changeState(new aiStateOnHit);
		return;
	} 

	// 어그로 레벨 체크,
	// 현재 어그로 레벨이 트리거 레벨보다 높다면
	// 시야거리내에 플레이어가 있는지 스캔
	// Todo: 차후 Idle상태에서 차후 주변에 어그로 레벨이 쌓일 경우
	// Aggro레벨을 올리는 함수 추가

	// 패시브형 몬스터가 아닐 경우 시야내에 적이 들어오면 어그로 맥스
	bool inSight = pmon->getTileMap()->sightScan(pmon->getSight(), *(pmon->getDrawPos()));
	if (pmon->getMonsterType() != 0 && inSight){
		pmon->setCurrentAggroLevel(pmon->getMaxAggroLevel());
	}

	if (pmon->getCurrentAggroLevel() >= pmon->getMaxAggroLevel()){
		pmon->changeState(new aiStateScan);
		return;
	}

	// 이동 목표 체크
	if (*(pmon->getRealPos()) != *(pmon->getDest())){
		pmon->changeState(new aiStateMoveto);
		return;
	}
}

void aiStateIdle::exit(mMonster* pmon){

}