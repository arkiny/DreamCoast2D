#include "stdafx.h"
#include "aiState.h"
#include "mMonster.h"

void aiStateIdle::enter(mMonster* pmon){
	// todo:: sprite setter를 object에 추가한후
	// idling sprite를 설정 (보고 있는 방향마다)
}

void aiStateIdle::execute(mMonster* pmon){
	// 이동이 없으므로 nextFrame만 실시	
	// 뭐 나중에 전투 추가되면 체력회복도 넣어보고
}

void aiStateIdle::exit(mMonster* pmon){

}