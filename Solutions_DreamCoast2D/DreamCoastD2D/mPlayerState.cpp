#include "stdafx.h"
#include <vector>
#include "cD2DRenderer.h"
#include "mPlayer.h"
#include "coControl.h"
#include "VECTOR2D.h"
#include "uSprite.h"
#include "wTileMap.h"
#include "uCamera.h"
#include "uTile.h"
#include "cResourceManager.h"


void mPlayer::onHit(float fdeltatime){
	// ���� �ð��� FRAMERATE�� �� �ι�
	if (m_onhitAccumtime < FRAMERATE * 2.0f){
		m_onhitAccumtime += fdeltatime;
	}
	else {
		// ���� ���� ���� �ð��� ������ ���
		// Idle���·� ���ư�
		m_onhitAccumtime = 0.0f;
		m_State = ONMOVE;
		this->setDmg(0.0f);
	}

	//
	if (m_SeeDir == LEFTDOWN){
		m_spriteAtlas->pickSpriteAtlas(700.0f, 0.0f, 49.0f, 73.0f, 1);
	}
	else if (m_SeeDir == LEFTUP){
		m_spriteAtlas->pickSpriteAtlas(850.0f, 0.0f, 48.0f, 74.0f, 1);
	}
	else if (m_SeeDir == RIGHTDOWN){
		m_spriteAtlas->pickSpriteAtlas(700.0f, 100.0f, 49.0f, 73.0f, 1);
	}
	else if (m_SeeDir == RIGHTUP){
		m_spriteAtlas->pickSpriteAtlas(850.0f, 100.0f, 48.0f, 74.0f, 1);
	}

	m_spriteAtlas->nextFrame(fdeltatime);
}

void mPlayer::onCasting(float delta){
	if (m_SeeDir == LEFTDOWN){
		m_spriteAtlas->pickSpriteAtlas(880.0f, 300.0f, 50.0f, 89.0f, 10.5f, 0.0f, 0);
	}
	else if (m_SeeDir == LEFTUP){
		m_spriteAtlas->pickSpriteAtlas(950.0f, 300.0f, 46.0f, 85.0f, 0);
	}
	else if (m_SeeDir == RIGHTDOWN){
		m_spriteAtlas->pickSpriteAtlas(880.0f, 400.0f, 50.0f, 89.0f, -10.5f, 0.0f, 0);
	}
	else if (m_SeeDir == RIGHTUP){
		m_spriteAtlas->pickSpriteAtlas(950.0f, 400.0f, 46.0f, 85.0f, 0);
	}
	m_spriteAtlas->nextFrame(delta);
}



// todo: �������� ������ �ʿ���
void mPlayer::onAttack(float fdeltatime){
	// fdeltatime�� �޾Ƽ� ���� �ð��� �����Ͽ��� ��� attackó��
	if (m_spriteAtlas->getCurrentFrame() == 7){
		m_spriteAtlas->setCurrentFrame(0);
		m_bEndbehavior = true;
		m_castingSkill = 99;
		m_State = ONMOVE;
		return;
	}

	// ������ ó���� ���� �����ӿ� Ʈ���� �ǵ��� -> ���� �ð��� Ʈ���ŵǵ�����
	if (m_SeeDir == LEFTDOWN){
		m_spriteAtlas->pickSpriteAtlas(0.0f, 600.0f, 121.0f, 98.0f, 19.5f, 0.0f, 7);
	}
	else if (m_SeeDir == LEFTUP){
		m_spriteAtlas->pickSpriteAtlas(0.0f, 700.0f, 103.0f, 84.0f, 7);
	}
	else if (m_SeeDir == RIGHTDOWN){
		m_spriteAtlas->pickSpriteAtlas(0.0f, 800.0f, 121.0f, 98.0f, -19.5f, 0.0f, 7);
	}
	else if (m_SeeDir == RIGHTUP){
		m_spriteAtlas->pickSpriteAtlas(0.0f, 900.0f, 103.0f, 84.0f, 7);
	}
	//leftdown (0.0f, 600.0f, 121.0f, 98.0f, 7)
	//leftup (0.0f, 700.0f, 103.0f, 84.0f, 7)
	//rightdown (0.0f, 800.0f, 121.0f, 98.0f, 7)
	//rightup (0.0f, 900.0f, 103.0f, 84.0f, 7)

	m_spriteAtlas->nextFrame(fdeltatime*m_attackSpeed);
}


//void mPlayer::onIdle(){
//
//}

// �̵����� ���� ���깫��
// �Ƹ� onMove ���� onControl
void mPlayer::onMove(float fdeltatime){
	VECTOR2D vMover = VECTOR2D(0.0f, 0.0f);

	// Animation Part
	// TODO:: Űó���� ����� �ϰ� �ʹ�..
	if (::coControl::GetInstance().getKeyControlInfo()[VK_LEFT] &&
		::coControl::GetInstance().getKeyControlInfo()[VK_DOWN]){
		m_SeeDir = LEFTDOWN;
		m_MoveDir = LEFTDOWN;

		m_spriteAtlas->pickSpriteAtlas(360.0f, 0.0f, 39.0f, 94.0f, 6);
	}

	else if (::coControl::GetInstance().getKeyControlInfo()[VK_LEFT] &&
		::coControl::GetInstance().getKeyControlInfo()[VK_UP]){
		m_SeeDir = LEFTUP;
		m_MoveDir = LEFTUP;
		m_spriteAtlas->pickSpriteAtlas(360.0f, 100.0f, 44.0f, 95.0f, 6);
	}

	else if (::coControl::GetInstance().getKeyControlInfo()[VK_RIGHT] &&
		::coControl::GetInstance().getKeyControlInfo()[VK_DOWN]){
		m_SeeDir = RIGHTDOWN;
		m_MoveDir = RIGHTDOWN;
		m_spriteAtlas->pickSpriteAtlas(360.0f, 200.0f, 39.0f, 94.0f, 6);
	}

	else if (::coControl::GetInstance().getKeyControlInfo()[VK_RIGHT] &&
		::coControl::GetInstance().getKeyControlInfo()[VK_UP]){
		m_SeeDir = RIGHTUP;
		m_MoveDir = RIGHTUP;
		m_spriteAtlas->pickSpriteAtlas(360.0f, 300.0f, 44.0f, 95.0f, 6);
	}

	else if (::coControl::GetInstance().getKeyControlInfo()[VK_RIGHT]){
		if (m_SeeDir == LEFTUP){
			m_SeeDir = RIGHTUP;
		}
		else if (m_SeeDir == LEFTDOWN){
			m_SeeDir = RIGHTDOWN;
		}
		m_MoveDir = RIGHT;
		m_spriteAtlas->pickSpriteAtlas(0.0f, 0.0f, 47.0f, 88.0f, 6);
	}
	else if (::coControl::GetInstance().getKeyControlInfo()[VK_LEFT]){
		if (m_SeeDir == RIGHTUP){
			m_SeeDir = LEFTUP;
		}
		else if (m_SeeDir == RIGHTDOWN){
			m_SeeDir = LEFTDOWN;
		}

		m_MoveDir = LEFT;
		m_spriteAtlas->pickSpriteAtlas(0.0f, 185.0f, 47.0f, 88.0f, 6);
	}
	else if (::coControl::GetInstance().getKeyControlInfo()[VK_DOWN]){
		if (m_SeeDir == LEFTUP){
			m_SeeDir = LEFTDOWN;
		}
		else if (m_SeeDir == RIGHTUP){
			m_SeeDir = RIGHTDOWN;
		}

		m_MoveDir = DOWN;
		m_spriteAtlas->pickSpriteAtlas(0.0f, 279.0f, 35.0f, 91.0f, 6);
	}
	else if (::coControl::GetInstance().getKeyControlInfo()[VK_UP]){
		if (m_SeeDir == LEFTDOWN){
			m_SeeDir = LEFTUP;
		}
		else if (m_SeeDir == RIGHTDOWN){
			m_SeeDir = RIGHTUP;
		}

		m_MoveDir = UP;
		m_spriteAtlas->pickSpriteAtlas(0.0f, 373.0f, 37.0f, 92.0f, 6);
	}
	else { // Idling
		if (m_SeeDir == RIGHTDOWN){
			// idle right down
			m_spriteAtlas->pickSpriteAtlas(0.0f, 92.0f, 64.0f, 92.0f, -19.5f, 0.0f, 4);
		}
		else if (m_SeeDir == LEFTUP){
			m_spriteAtlas->pickSpriteAtlas(360.0f, 400.0f, 42.0f, 89.0f, 4);
		}
		else if (m_SeeDir == RIGHTUP){
			m_spriteAtlas->pickSpriteAtlas(360.0f, 500.0f, 42.0f, 89.0f, 4);
		}
		else if (m_SeeDir == LEFTDOWN){
			m_spriteAtlas->pickSpriteAtlas(0.0f, 500.0f, 64.0f, 92.0f, 19.5f, 0.0f, 4);
		}
		m_MoveDir = NOMOVE;
	}
	// frame update
	m_spriteAtlas->nextFrame(fdeltatime);
	vMover = 
		mCharacter::vectorMove(fdeltatime, m_MoveDir);

	// Todo
	// �� �����Ϳ��� �� ������ �޾ƿͼ� �̵� �Ұ� ��Ʈ��, ���� �����Ҵ������ ��ȯ
	// �� �����ʹ� ���������� �ٲ𶧸��� ������Ʈ�� ����� �Ѵ�.
	// ��Ʈ�� Ŭ������, ����Ŭ�������� �������ָ� �� ��������?
	// �ϴ� �ڿ������� �������� ���� �̵��Ұ��� �� ��θ� ���� �̵��Ұ� ó��
	// ���� ���� �� �簢���� �Ἥ �������� �ϴ� �ɱ?
	float topX = m_pTileMap->getTileCoordinates(*_drawVector + vMover).x;
	float topY = m_pTileMap->getTileCoordinates(*_drawVector + vMover).y;

	float bottomX = m_pTileMap->getTileCoordinates(*_realVector + vMover).x;
	float bottomY = m_pTileMap->getTileCoordinates(*_realVector + vMover).y;

	// �ܰ� �浹 ó��
	if (topX >= m_pTileMap->getMapLimit().x || topY >= m_pTileMap->getMapLimit().y ||
		bottomX >= m_pTileMap->getMapLimit().x || bottomY >= m_pTileMap->getMapLimit().y ||
		topX < 0 || topY < 0 || bottomX < 0 || bottomY < 0){
		return;
	}


	// �̵��Ұ��� �̵��Ұ� ó��
	// move update, ���⼭ float -> int ��ȯ�� �Ͼ ������ �ν��� �������� �ִ�.
	// ���� Ư���� ���Ϳ��� �浹ó���� ���� ����(���� �������̶�� �浹 ó���� �־��������)
	if (m_pTileMap->getMapinfo(static_cast<int>(topX), static_cast<int>(topY)) == 0
		&& m_pTileMap->getMapinfo(static_cast<int>(bottomX), static_cast<int>(bottomY)) == 0){
		*_realVector = *_realVector + vMover;
		*_drawVector = *_drawVector + vMover;
	}
	//
}

void mPlayer::onDead(float delta){
	//on dead
	//	ld 700, 200, 69, 55, 0
	//	lu 850, 200, 62, 43, 0
	//	rd 700, 250, 69, 44, 0
	//	rd 850, 250, 62, 43, 0

	//accumtime += pmon->getdeltaTime();
	//if (accumtime < FRAMERATE * 1.0f){
	//	m_sprite->nextFrame(pmon->getdeltaTime());
	//}

	//// ����� ���̵�ƿ� ȿ��
	//pmon->setAlpha(pmon->getAlpha() - 0.025f);

	//// ���� delete ���ٴ� setVisible�� �̿��ؼ�
	//// �ٽ� �̿��ϴ� ����� ���� �� �ϵ��̴�
	//// ���� �ð��� ���� �� ���� trigger on
	//if (accumtime > FRAMERATE*8.0f){
	//	pmon->setState(ONDEAD);
	//}
	if (m_SeeDir == RIGHTDOWN){
		m_spriteAtlas->pickSpriteAtlas(700.0f, 250.0f, 69.0f, 44.0f, -19.5f, 0.0f, 0);
	}
	else if (m_SeeDir == LEFTUP){
		m_spriteAtlas->pickSpriteAtlas(850.0f, 200.0f, 62.0f, 50.0f, 0);
	}
	else if (m_SeeDir == RIGHTUP){
		m_spriteAtlas->pickSpriteAtlas(850.0f, 250.0f, 62.0f, 50.0f, 0);
	}
	else if (m_SeeDir == LEFTDOWN){
		m_spriteAtlas->pickSpriteAtlas(700.0f, 200.0f, 69.0f, 44.0f, 19.5f, 0.0f, 0);
	}
	m_spriteAtlas->nextFrame(delta);

	m_deadFadeOutTime += delta;
	m_alpha -= 0.025f;
	if (m_deadFadeOutTime > FRAMERATE*8.0f){
		//if (m_alpha <= 0.0f){
		// todo: ���̵�ƿ� ������ ���� ���� ó��
		m_deadcomp = true;
	}
}