#include "stdafx.h"
#include "aiState.h"
#include "mMonster.h"
#include "uSprite.h"

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
}

void aiStateIdle::exit(mMonster* pmon){

}