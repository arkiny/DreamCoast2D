#include "stdafx.h"
#include "aiState.h"
#include "mMonster.h"
#include "uSprite.h"

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
	m_sprite->nextFrame(pmon->getdeltaTime());
	// 이동이 없으므로 nextFrame만 실시	
	// 뭐 나중에 전투 추가되면 체력회복도 넣어보고
}

void aiStateIdle::exit(mMonster* pmon){

}