#include "stdafx.h"
#include "pStateMove.h"

#include "cResourceManager.h"
#include "coControl.h"
#include "uSprite.h"

#include "mPlayer.h"
#include "wTileMap.h"
#include "VECTOR2D.h"

#include "pStateOnHit.h"
#include "pStateAttack.h"
#include "pStateOnCasting.h"
#include "pStateIdle.h"

//��������
void pStateMove::enter(mPlayer* pplayer){
	pplayer->setState(ONMOVE);
	m_sprite = pplayer->getSprite();
	m_sprite->setCurrentFrame(0);

	if (pplayer->getMoveDir() == LEFTDOWN){
		pplayer->setSeeDir(LEFTDOWN);
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 0)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 0)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 0)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 0)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 0)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 0)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 0)->maxFrame);
	}
	else if (pplayer->getMoveDir() == LEFTUP){
		pplayer->setSeeDir(LEFTUP);
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 1)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 1)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 1)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 1)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 1)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 1)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 1)->maxFrame);
	}
	else if (pplayer->getMoveDir() == RIGHTDOWN){
		pplayer->setSeeDir(RIGHTDOWN);
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 2)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 2)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 2)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 2)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 2)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 2)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 2)->maxFrame);
	}
	else if (pplayer->getMoveDir() == RIGHTUP){
		pplayer->setSeeDir(RIGHTUP);
		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 3)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 3)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 3)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 3)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 3)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 3)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 3)->maxFrame);
	}
	else if (pplayer->getMoveDir() == RIGHT){
		if (pplayer->getSeeDir() == LEFTUP){
			pplayer->setSeeDir(RIGHTUP);
		}
		else if (pplayer->getSeeDir() == LEFTDOWN){
			pplayer->setSeeDir(RIGHTDOWN);
		}

		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 5)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 5)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 5)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 5)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 5)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 5)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 5)->maxFrame);
	}
	else if (pplayer->getMoveDir() == LEFT){
		if (pplayer->getSeeDir() == RIGHTUP){
			pplayer->setSeeDir(LEFTUP);
		}
		else if (pplayer->getSeeDir() == RIGHTDOWN){
			pplayer->setSeeDir(LEFTDOWN);
		}

		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 4)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 4)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 4)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 4)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 4)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 4)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 4)->maxFrame);
	}
	else if (pplayer->getMoveDir() == DOWN){
		if (pplayer->getSeeDir() == LEFTUP){
			pplayer->setSeeDir(LEFTDOWN);
		}
		else if (pplayer->getSeeDir() == RIGHTUP){
			pplayer->setSeeDir(RIGHTDOWN);
		}

		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 7)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 7)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 7)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 7)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 7)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 7)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 7)->maxFrame);
	}
	else if (pplayer->getMoveDir() == UP){
		if (pplayer->getSeeDir() == LEFTDOWN){
			pplayer->setSeeDir(LEFTUP);
		}
		else if (pplayer->getSeeDir() == RIGHTDOWN){
			pplayer->setSeeDir(RIGHTUP);
		}

		m_sprite->pickSpriteAtlas(
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 6)->x,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 6)->y,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 6)->width,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 6)->height,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 6)->offsetX,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 6)->offsetY,
			cResourceManager::GetInstance().getPlayerSpriteInfo(1, 6)->maxFrame);
	}
}
//��������
void pStateMove::execute(mPlayer* pplayer){	
	// �̵� ���� �϶�(Ű���带 ������ ���̵�� �̵�)	
	// idle
	if (pplayer->getMoveDir() == LEFTDOWN){
		if (!::coControl::GetInstance().getKeyControlInfo()[VK_LEFT] &&
			!::coControl::GetInstance().getKeyControlInfo()[VK_DOWN]){
			pplayer->changeStatus(new pStateIdle);
			return;
		}
		else if (!::coControl::GetInstance().getKeyControlInfo()[VK_LEFT]){
			pplayer->setMoveDir(DOWN);
			pplayer->changeStatus(new pStateMove);
			return;
		}
		else if (!::coControl::GetInstance().getKeyControlInfo()[VK_DOWN]){
			pplayer->setMoveDir(LEFT);
			pplayer->changeStatus(new pStateMove);
			return;
		}
	}
	else if (pplayer->getMoveDir() == LEFTUP){
		if (!::coControl::GetInstance().getKeyControlInfo()[VK_LEFT] &&
			!::coControl::GetInstance().getKeyControlInfo()[VK_UP]){
			pplayer->changeStatus(new pStateIdle);
			return;
		}
		else if (!::coControl::GetInstance().getKeyControlInfo()[VK_LEFT]){
			pplayer->setMoveDir(UP);
			pplayer->changeStatus(new pStateMove);
			return;
		}
		else if (!::coControl::GetInstance().getKeyControlInfo()[VK_UP]){
			pplayer->setMoveDir(LEFT);
			pplayer->changeStatus(new pStateMove);
			return;
		}
	}
	else if (pplayer->getMoveDir() == RIGHTDOWN){
		if (!::coControl::GetInstance().getKeyControlInfo()[VK_RIGHT] &&
			!::coControl::GetInstance().getKeyControlInfo()[VK_DOWN]){
			pplayer->changeStatus(new pStateIdle);
			return;
		}
		else if (!::coControl::GetInstance().getKeyControlInfo()[VK_RIGHT]){
			pplayer->setMoveDir(DOWN);
			pplayer->changeStatus(new pStateMove);
			return;
		}
		else if (!::coControl::GetInstance().getKeyControlInfo()[VK_DOWN]){
			pplayer->setMoveDir(RIGHT);
			pplayer->changeStatus(new pStateMove);
			return;
		}
	}
	else if (pplayer->getMoveDir() == RIGHTUP){
		if (!::coControl::GetInstance().getKeyControlInfo()[VK_RIGHT] &&
			!::coControl::GetInstance().getKeyControlInfo()[VK_UP]){
			pplayer->changeStatus(new pStateIdle);
			return;
		}
		else if (!::coControl::GetInstance().getKeyControlInfo()[VK_RIGHT]){
			pplayer->setMoveDir(UP);
			pplayer->changeStatus(new pStateMove);
			return;
		}
		else if (!::coControl::GetInstance().getKeyControlInfo()[VK_UP]){
			pplayer->setMoveDir(RIGHT);
			pplayer->changeStatus(new pStateMove);
			return;
		}
	}
	else if (pplayer->getMoveDir() == RIGHT){
		if (!::coControl::GetInstance().getKeyControlInfo()[VK_RIGHT]){
			pplayer->changeStatus(new pStateIdle);
			return;
		}
		else if (::coControl::GetInstance().getKeyControlInfo()[VK_RIGHT] &&
			::coControl::GetInstance().getKeyControlInfo()[VK_UP]){
			pplayer->setMoveDir(RIGHTUP);
			pplayer->changeStatus(new pStateMove);
			return;
		}
		else if (::coControl::GetInstance().getKeyControlInfo()[VK_RIGHT] &&
			::coControl::GetInstance().getKeyControlInfo()[VK_DOWN]){
			pplayer->setMoveDir(RIGHTDOWN);
			pplayer->changeStatus(new pStateMove);
			return;
		}
	}
	else if (pplayer->getMoveDir() == LEFT){
		if (!::coControl::GetInstance().getKeyControlInfo()[VK_LEFT]){
			pplayer->changeStatus(new pStateIdle);
			return;
		}
		else if (::coControl::GetInstance().getKeyControlInfo()[VK_LEFT] &&
			::coControl::GetInstance().getKeyControlInfo()[VK_UP]){
			pplayer->setMoveDir(LEFTUP);
			pplayer->changeStatus(new pStateMove);
			return;
		}
		else if (::coControl::GetInstance().getKeyControlInfo()[VK_LEFT] &&
			::coControl::GetInstance().getKeyControlInfo()[VK_DOWN]){
			pplayer->setMoveDir(LEFTDOWN);
			pplayer->changeStatus(new pStateMove);
			return;
		}
	}
	else if (pplayer->getMoveDir() == DOWN){
		if (!::coControl::GetInstance().getKeyControlInfo()[VK_DOWN]){
			pplayer->changeStatus(new pStateIdle);
			return;
		}
		else if (::coControl::GetInstance().getKeyControlInfo()[VK_LEFT] &&
			::coControl::GetInstance().getKeyControlInfo()[VK_DOWN]){
			pplayer->setMoveDir(LEFTDOWN);
			pplayer->changeStatus(new pStateMove);
			return;
		}
		else if (::coControl::GetInstance().getKeyControlInfo()[VK_RIGHT] &&
			::coControl::GetInstance().getKeyControlInfo()[VK_DOWN]){
			pplayer->setMoveDir(RIGHTDOWN);
			pplayer->changeStatus(new pStateMove);
			return;
		}
	}
	else if (pplayer->getMoveDir() == UP){
		if (!::coControl::GetInstance().getKeyControlInfo()[VK_UP]){
			pplayer->changeStatus(new pStateIdle);
			return;
		}
		else if (::coControl::GetInstance().getKeyControlInfo()[VK_LEFT] &&
			::coControl::GetInstance().getKeyControlInfo()[VK_UP]){
			pplayer->setMoveDir(LEFTUP);
			pplayer->changeStatus(new pStateMove);
			return;
		}
		else if (::coControl::GetInstance().getKeyControlInfo()[VK_RIGHT] &&
			::coControl::GetInstance().getKeyControlInfo()[VK_UP]){
			pplayer->setMoveDir(RIGHTUP);
			pplayer->changeStatus(new pStateMove);
			return;
		}
	}

	// �̵��� ���ݹ޾�����
	// onhit
	if (pplayer->getState() == ONHIT){
		pplayer->setState(ONHIT);
		pplayer->changeStatus(new pStateOnHit);
		return;
	}
	
	// �̵��� ����Ű�� ��������
	// on attack
	if (::coControl::GetInstance().getKeyControlInfo()[0x5A]){
		pplayer->setState(ONATTACK);
		pplayer->changeStatus(new pStateAttack);
		return;
	}

	// �̵��� ��ųŰ�� ��������
	// oncasting
	if (::coControl::GetInstance().getKeyControlInfo()[0x58]){
		pplayer->setState(ONCASTING);
		pplayer->changeStatus(new pStateOnCasting);
		return;
	}

	// �ִϸ��̼� ó��
	m_sprite->nextFrame(pplayer->getDeltaTime());

	// �̵� ó��	
	VECTOR2D vMover = VECTOR2D(0.0f, 0.0f);
	vMover = pplayer->vectorMove(pplayer->getDeltaTime(), (DIRECTION)pplayer->getMoveDir());
		//mCharacter::vectorMove(fdeltatime, m_MoveDir);

	// Todo
	// �� �����Ϳ��� �� ������ �޾ƿͼ� �̵� �Ұ� ��Ʈ��, ���� �����Ҵ������ ��ȯ
	// �� �����ʹ� ���������� �ٲ𶧸��� ������Ʈ�� ����� �Ѵ�.
	// ��Ʈ�� Ŭ������, ����Ŭ�������� �������ָ� �� ��������?
	// �ϴ� �ڿ������� �������� ���� �̵��Ұ��� �� ��θ� ���� �̵��Ұ� ó��
	// ���� ���� �� �簢���� �Ἥ �������� �ϴ� �ɱ?
	float topX = pplayer->getTileMap()->getTileCoordinates(*pplayer->getDrawPos() + vMover).x;
	float topY = pplayer->getTileMap()->getTileCoordinates(*pplayer->getDrawPos() + vMover).y;

	float bottomX = pplayer->getTileMap()->getTileCoordinates(*pplayer->getRealPos() + vMover).x;
	float bottomY = pplayer->getTileMap()->getTileCoordinates(*pplayer->getRealPos() + vMover).y;

	// �ܰ� �浹 ó��
	if (topX >= pplayer->getTileMap()->getMapLimit().x || topY >= pplayer->getTileMap()->getMapLimit().y ||
		bottomX >= pplayer->getTileMap()->getMapLimit().x || bottomY >= pplayer->getTileMap()->getMapLimit().y ||
		topX < 0 || topY < 0 || bottomX < 0 || bottomY < 0){
		return;
	}


	// �̵��Ұ��� �̵��Ұ� ó��
	// move update, ���⼭ float -> int ��ȯ�� �Ͼ ������ �ν��� �������� �ִ�.
	// ���� Ư���� ���Ϳ��� �浹ó���� ���� ����(���� �������̶�� �浹 ó���� �־��������)
	if (pplayer->getTileMap()->getMapinfo(static_cast<int>(topX), static_cast<int>(topY)) == 0
		&& pplayer->getTileMap()->getMapinfo(static_cast<int>(bottomX), static_cast<int>(bottomY)) == 0){
		VECTOR2D realin = *pplayer->getRealPos() + vMover;
		VECTOR2D drawin = *pplayer->getDrawPos() + vMover;
		pplayer->setRealPos(realin.x, realin.y);
		pplayer->setDrawPos(drawin.x, drawin.y);
	}	
}

//���� ��Ż
void pStateMove::exit(mPlayer* pmon){

}