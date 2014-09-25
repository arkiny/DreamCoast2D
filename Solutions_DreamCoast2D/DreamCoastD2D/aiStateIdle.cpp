#include "stdafx.h"
#include "aiStateIdle.h"
#include "mMonster.h"
#include "uSprite.h"
#include "aiStateOnHit.h"
#include "aiStateMoveto.h"
#include "aiStateScan.h"
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
	// 1. �ǰ� �ֿ켱
	if (pmon->getState() == ONHIT){
		pmon->changeState(new aiStateOnHit);
	} 

	// ��׷� ���� üũ,
	// ���� ��׷� ������ Ʈ���� �������� ���ٸ�
	// �þ߰Ÿ����� �÷��̾ �ִ��� ��ĵ
	// Todo: ���� Idle���¿��� ���� �ֺ��� ��׷� ������ ���� ���
	// Aggro������ �ø��� �Լ� �߰�
	if (pmon->getCurrentAggroLevel() >= pmon->getMaxAggroLevel()){
		pmon->changeState(new aiStateScan);
	}

	// �̵� ��ǥ üũ
	if (*(pmon->getRealPos()) != *(pmon->getDest())){
		pmon->changeState(new aiStateMoveto);
	}
}

void aiStateIdle::exit(mMonster* pmon){

}