#include "stdafx.h"
#include "aiStateIdle.h"
#include "mMonster.h"
#include "uSprite.h"
#include "aiStateOnHit.h"
#include "aiStateMoveto.h"
#include "VECTOR2D.h"

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
	accumtime += pmon->getdeltaTime();
	m_sprite->nextFrame(pmon->getdeltaTime());
	
	// �뷫 6�ʸ��� ���� �������� �̵�
	if (accumtime > 6.0f){
		pmon->moveRandom();
	}

	// �̵��� �����Ƿ� nextFrame�� �ǽ�	
	// �� ���߿� ���� �߰��Ǹ� ü��ȸ���� �־��
	if (pmon->getState() == ONHIT){
		pmon->changeState(new aiStateOnHit);
	} 
	if (*(pmon->getRealPos()) != *(pmon->getDest())){
		pmon->changeState(new aiStateMoveto);
	}
}

void aiStateIdle::exit(mMonster* pmon){

}