#include "stdafx.h"
#include "mMonster.h"
#include "aiStateDead.h"
#include "aiStateOnHit.h"
#include "aiStateIdle.h"
#include "VECTOR2D.h"
#include "aiStateSkillEffect.h"
#include "uSprite.h"
#include "wTileMap.h"
#include "cSoundManager.h"
#include "mGFX.h"
#include "mEffect.h"
#include "wTileMap.h"

void aiStateSkillEffect::enter(mMonster* pmon){
	cSoundManager::GetInstance().stopBeginSpell();
	m_sprite = pmon->getSprite();
	if (pmon->getMonsterType() == 2){
		pmon->onAttack();
		m_sprite->setCurrentFrame(0);
	}
	else {

	}
	cSoundManager::GetInstance().executeSkill(0);
}

void aiStateSkillEffect::execute(mMonster* pmon){
	nextIdle += pmon->getdeltaTime();
	attacktimer += pmon->getdeltaTime();
	m_sprite->nextFrame(pmon->getdeltaTime());

	if (pmon->getHealth() <= 0.0f){
		pmon->changeState(new aiStateDead);
		return;
	}

	// �������̶� ���� ������ ����
	if (pmon->getState() == ONHIT){
		pmon->changeState(new aiStateOnHit);
	}

	// �������� 3������ ���Ŀ�, ���� ������ ���
	if (attacktimer >= FRAMERATE * 3 && !attacked){
		pmon->getTileMap()->playerGetHit(pmon->getAttackPower()*5.0f);
		attacked = true;

		// �÷��̾��� ��ġ�� ��ų ����Ʈ ����
		float x, y;
		VECTOR2D in;
		VECTOR2D iso;
		iso.x = pmon->getTileMap()->getPlayerTilePos().y;
		iso.y = pmon->getTileMap()->getPlayerTilePos().x;
		x = iso.x * pmon->getTileMap()->getRectTileWidth();
		y = iso.y*pmon->getTileMap()->getRectTileHeight();
		in = VECTOR2D(x, y);
		iso = pmon->getTileMap()->twoDtoISO(in);
		::mGFX::GetInstance().pushToEventQueue(new mEffect(1, 0, new VECTOR2D(iso.x, iso.y), pmon->getCam()));
		//::mGFX::GetInstance().pushToEventQueue(new mEffect(1, 0, new VECTOR2D(in.x, in.y), m_Cam));
		//skillCoord.pop();
		
	}

	// ������ ����� ���̵�� ���ư��� ��׷�üũ���� �ٽ�
	if (nextIdle >= FRAMERATE * 8){
		pmon->changeState(new aiStateIdle);
	}
}

void aiStateSkillEffect::exit(mMonster* pmon){

}