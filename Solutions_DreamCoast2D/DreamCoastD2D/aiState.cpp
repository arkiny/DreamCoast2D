#include "stdafx.h"
#include "aiState.h"
#include "mMonster.h"

void aiStateIdle::enter(mMonster* pmon){
	// todo:: sprite setter�� object�� �߰�����
	// idling sprite�� ���� (���� �ִ� ���⸶��)
}

void aiStateIdle::execute(mMonster* pmon){
	pmon->onIdle(pmon->getdeltaTime());
	// �̵��� �����Ƿ� nextFrame�� �ǽ�	
	// �� ���߿� ���� �߰��Ǹ� ü��ȸ���� �־��
}

void aiStateIdle::exit(mMonster* pmon){

}