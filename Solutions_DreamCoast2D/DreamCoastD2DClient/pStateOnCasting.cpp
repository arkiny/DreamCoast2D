#include "stdafx.h"
#include "pStateOnCasting.h"

#include "cResourceManager.h"
#include "cSoundManager.h"
#include "coControl.h"
#include "uSprite.h"

#include "mPlayer.h"
#include "wTileMap.h"
#include "VECTOR2D.h"

#include "pStateMove.h"
#include "pStateAttack.h"
#include "pStateIdle.h"
#include "pStateOnSkillEffect.h"
#include "pStateOnHit.h"

//��������
void pStateOnCasting::enter(mPlayer* pplayer){
	pplayer->setState(ONCASTING);
	m_sprite = pplayer->getSprite();
	m_sprite->setCurrentFrame(0);
	if (pplayer->getSeeDir() == LEFTDOWN){
		//m_spriteAtlas->pickSpriteAtlas(880.0f, 300.0f, 50.0f, 89.0f, 10.5f, 0.0f, 0);
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 0)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 0)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 0)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 0)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 0)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 0)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 0)->maxFrame);
	}
	else if (pplayer->getSeeDir() == LEFTUP){
		//m_spriteAtlas->pickSpriteAtlas(950.0f, 300.0f, 46.0f, 85.0f, 0);
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 1)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 1)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 1)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 1)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 1)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 1)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 1)->maxFrame);
	}
	else if (pplayer->getSeeDir() == RIGHTDOWN){
		//m_spriteAtlas->pickSpriteAtlas(880.0f, 400.0f, 50.0f, 89.0f, -10.5f, 0.0f, 0);
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 2)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 2)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 2)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 2)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 2)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 2)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 2)->maxFrame);
	}
	else if (pplayer->getSeeDir() == RIGHTUP){
		//m_spriteAtlas->pickSpriteAtlas(950.0f, 400.0f, 46.0f, 85.0f, 0);
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 3)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 3)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 3)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 3)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 3)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 3)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(3, 3)->maxFrame);
	}

	cSoundManager::GetInstance().executeBeginSpell();
	pplayer->putKeyIntoQueue();
}
//��������
void pStateOnCasting::execute(mPlayer* pplayer){
	m_sprite->nextFrame(pplayer->getDeltaTime());
	pplayer->putKeyIntoQueue();

	if (pplayer->getState() == ONHIT){
		while (!pplayer->getKeyInput().empty()){
			pplayer->getKeyInput().pop();
		}
		pplayer->setState(ONHIT);
		pplayer->changeStatus(new pStateOnHit);
		return;
	}

	if (!::coControl::GetInstance().getKeyControlInfo()[0x58]){
		// TODO: Ű�� �������� ĳ���� ���� ���߱�
		cSoundManager::GetInstance().stopBeginSpell();

		// �Է� �� Ű�� ���ǥ�� ���Ͽ� ���ǥ�� ������ ��� �ش� ��ų��,
		// �ƴҰ�쿡�� �г�Ƽ�� �ο��Ѵ�. (�ڱ⿡�� ������)
		// ��ų �߻��, ���ݸ�ǰ� ���Ͼ� ����� ���ϴ� ���,
		// �ڱ��ֺ����� ��ų�� ���õ� ����Ʈ�� ǥ���ؾ��Ѵ�.

		// ������Ʈ �ø��� üũ�ϰ� �ǹǷ� ������ �ȴ�.
		// TODO ������Ʈ Ÿ�� üũ
		if (!pplayer->getKeyInput().empty()){
			for (unsigned int i = 0; i < pplayer->getSkillList().size(); i++){
				std::queue<int> temp = pplayer->getKeyInput();
				if (pplayer->skillCompare(temp, pplayer->getSkillList()[i], 0)){
					pplayer->setCastingSkill(i);
					break;
				}
			}

			if (pplayer->getCastingSkill() == 99) {
				// �ƴϸ� ���Ƽ�� �ִ� �ɷ�
				pplayer->getHit(10.0f);
			}

			while (!pplayer->getKeyInputPointer()->empty()){
				pplayer->getKeyInputPointer()->pop();
			}
		}
		else {
			if (pplayer->getCastingSkill() != 99){
				// skill������ ��ų ����
				if (pplayer->getMP() >= 10.0f){
					//
					pplayer->setState(ONSKILLEFFECTING);
					pplayer->changeStatus(new pStateOnSkillEffect);	
				}
				else{
					// ���� ������ ���Ƽ
					pplayer->getHit(10.0f);
				}
			}
			else {
				pplayer->setState(ONIDLE);
				pplayer->changeStatus(new pStateIdle);
			}
		}
	}
}
//���� ��Ż
void pStateOnCasting::exit(mPlayer* pplayer){

}