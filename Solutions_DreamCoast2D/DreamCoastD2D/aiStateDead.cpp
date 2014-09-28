#include "stdafx.h"
#include "aiStateDead.h"
#include "aiStateOnHit.h"
#include "aiStateIdle.h"
#include "aiStateDead.h"
#include "uSprite.h"
#include "mMonster.h"


void aiStateDead::enter(mMonster* pmon){
	m_sprite = pmon->getSprite();
	pmon->onDeath();
}

void aiStateDead::execute(mMonster* pmon){
	accumtime += pmon->getdeltaTime();
	if (accumtime < FRAMERATE * 1.0f){
		m_sprite->nextFrame(pmon->getdeltaTime());
	}

	// ����� ���̵�ƿ� ȿ��
	pmon->setAlpha(pmon->getAlpha() - 0.025f);

	// ���� delete ���ٴ� setVisible�� �̿��ؼ�
	// �ٽ� �̿��ϴ� ����� ���� �� �ϵ��̴�
	// ���� �ð��� ���� �� ���� trigger on
	if (accumtime > FRAMERATE*8.0f){
		pmon->setState(ONDEAD);		
	}
}

void aiStateDead::exit(mMonster* pmon){

}