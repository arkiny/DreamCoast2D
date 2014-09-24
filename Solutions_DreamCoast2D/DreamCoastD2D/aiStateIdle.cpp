#include "stdafx.h"
#include "aiStateIdle.h"
#include "mMonster.h"
#include "uSprite.h"
#include "aiStateOnHit.h"

void aiStateIdle::enter(mMonster* pmon){
	// todo:: sprite setter�� object�� �߰�����
	// idling sprite�� ���� (���� �ִ� ���⸶��)
	// pointer initial �Ҷ� ����ϳ�?
	m_sprite = pmon->getSprite();
	pmon->onIdle();
}

void aiStateIdle::execute(mMonster* pmon){
	// state�ȿ� Ư���� ���� �������ִ� �� ������, �������� ���� ������
	//
	m_sprite->nextFrame(pmon->getdeltaTime());
	// �̵��� �����Ƿ� nextFrame�� �ǽ�	
	// �� ���߿� ���� �߰��Ǹ� ü��ȸ���� �־��
	if (pmon->getState() == ONHIT){
		pmon->changeState(new aiStateOnHit);
	}
}

void aiStateIdle::exit(mMonster* pmon){

}