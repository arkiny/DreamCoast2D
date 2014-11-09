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

#include "movePacket.h"
#include "netWorkCharManager.h"
#include "char_client.h"

//상태진입
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

	movePacket toServer;
	toServer.id = ::netWorkCharManager::GetInstance().getMyId();
	toServer.state = pplayer->getState();
	toServer.px = pplayer->getDrawPos()->x;
	toServer.py = pplayer->getDrawPos()->y;
	toServer.seedir = pplayer->getSeeDir();
	toServer.speed = pplayer->getMoveSpeed();
	toServer.direction = pplayer->getMoveDir();

	::CharCIPMessage::GetInstance().SendMessagePort(toServer);
}
//상태진행
void pStateMove::execute(mPlayer* pplayer){	
	// 이동 중지 일때(키보드를 뗏을때 아이들로 이동)	
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

	// 이동중 공격받았을때
	// onhit
	if (pplayer->getState() == ONHIT){
		pplayer->setState(ONHIT);
		pplayer->changeStatus(new pStateOnHit);
		return;
	}
	
	// 이동중 공격키를 눌렀을때
	// on attack
	if (::coControl::GetInstance().getKeyControlInfo()[0x5A]){
		pplayer->setState(ONATTACK);
		pplayer->changeStatus(new pStateAttack);
		return;
	}

	// 이동중 스킬키를 눌렀을때
	// oncasting
	if (::coControl::GetInstance().getKeyControlInfo()[0x58]){
		pplayer->setState(ONCASTING);
		pplayer->changeStatus(new pStateOnCasting);
		return;
	}

	// 애니메이션 처리
	m_sprite->nextFrame(pplayer->getDeltaTime());

	// 이동 처리	
	VECTOR2D vMover = VECTOR2D(0.0f, 0.0f);
	vMover = pplayer->vectorMove(pplayer->getDeltaTime(), (DIRECTION)pplayer->getMoveDir());
		//mCharacter::vectorMove(fdeltatime, m_MoveDir);

	// Todo
	// 맵 포인터에서 맵 정보를 받아와서 이동 불가 컨트롤, 차후 동적할당식으로 전환
	// 맵 포인터는 스테이지가 바뀔때마다 업데이트를 해줘야 한다.
	// 컨트롤 클래스나, 월드클래스에서 조정해주면 더 나으려나?
	// 일단 자연스러운 오더링을 위해 이동불가는 둘 모두를 통해 이동불가 처리
	// 가장 좋은 건 사각형을 써서 오더링을 하는 걸까나?
	float topX = pplayer->getTileMap()->getTileCoordinates(*pplayer->getDrawPos() + vMover).x;
	float topY = pplayer->getTileMap()->getTileCoordinates(*pplayer->getDrawPos() + vMover).y;

	float bottomX = pplayer->getTileMap()->getTileCoordinates(*pplayer->getRealPos() + vMover).x;
	float bottomY = pplayer->getTileMap()->getTileCoordinates(*pplayer->getRealPos() + vMover).y;

	// 외곽 충돌 처리
	if (topX >= pplayer->getTileMap()->getMapLimit().x || topY >= pplayer->getTileMap()->getMapLimit().y ||
		bottomX >= pplayer->getTileMap()->getMapLimit().x || bottomY >= pplayer->getTileMap()->getMapLimit().y ||
		topX < 0 || topY < 0 || bottomX < 0 || bottomY < 0){
		return;
	}


	// 이동불가시 이동불가 처리
	// move update, 여기서 float -> int 변환이 일어나 데이터 로스가 있을수도 있다.
	// 게임 특성상 몬스터와의 충돌처리는 아직 없음(만약 보스형이라면 충돌 처리가 있어야할지도)
	if (pplayer->getTileMap()->getMapinfo(static_cast<int>(topX), static_cast<int>(topY)) == 0
		&& pplayer->getTileMap()->getMapinfo(static_cast<int>(bottomX), static_cast<int>(bottomY)) == 0){
		VECTOR2D realin = *pplayer->getRealPos() + vMover;
		VECTOR2D drawin = *pplayer->getDrawPos() + vMover;
		pplayer->setRealPos(realin.x, realin.y);
		pplayer->setDrawPos(drawin.x, drawin.y);
	}	
}

//상태 이탈
void pStateMove::exit(mPlayer* pmon){

}