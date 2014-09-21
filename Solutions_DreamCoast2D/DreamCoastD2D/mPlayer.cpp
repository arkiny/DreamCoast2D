#include "stdafx.h"
#include "cD2DRenderer.h"
#include "mPlayer.h"
#include "coControl.h"
#include "VECTOR2D.h"
#include "uSprite.h"
#include "wTileMap.h"

mPlayer::mPlayer()
{	
	m_ipD2DBitmap = nullptr;
	
	//todo: 임시로 중앙에 대기, 차후 맵정보에 따라 시작점 정보 수정
	
	_realVector = new VECTOR2D(514.0f, 384.0f);
	_drawVector = new VECTOR2D(_realVector->x, _realVector->y + 15.0f);
	m_spriteAtlas = new uSprite();
	m_SeeDir = RIGHTDOWN;
	m_State = ONMOVE;
}


mPlayer::~mPlayer()
{
	SafeRelease(m_ipD2DBitmap);

	if (_drawVector != NULL){
		delete _drawVector;
	}
	if (m_spriteAtlas != NULL){
		delete m_spriteAtlas;
	}
}

void mPlayer::onInit(cD2DRenderer& renderer){
	HWND hWnd = renderer.GetHwnd();
	m_ipD2DBitmap = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/sprites.png", NULL);
}

void mPlayer::onUpdate(float fdeltatime){	
	if (m_pControl->getKeyControlInfo()[0x5A]){
		if (m_State == ONATTACK){
			mPlayer::onAttack(fdeltatime);
		}
		else {
			m_State = ONATTACK;
			m_spriteAtlas->setCurrentFrame(0);
			
		}
	}
	else if (m_State == ONATTACK){
		mPlayer::onAttack(fdeltatime);
	}
	else if (m_State == ONMOVE){
		mPlayer::onMove(fdeltatime);
	}
}

// todo: 공속조정 변수가 필요함
void mPlayer::onAttack(float fdeltatime){
	if (m_spriteAtlas->getCurrentFrame() == 7){
		m_spriteAtlas->setCurrentFrame(0);
		m_State = ONMOVE;
		return;
	}

	// 데미지 처리는 일정 프레임에 트리거 되도록

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

// 키를 받아와서 업데이트
void mPlayer::setKeyControl(coControl* in){
	m_pControl = in;
}


VECTOR2D mPlayer::vectorMove(float fdeltatime, DIRECTION dir){
	VECTOR2D vMover = VECTOR2D(0.0f, 0.0f);
	VECTOR2D vDir = VECTOR2D(0.0f, 0.0f);
	switch (dir)
	{
	case LEFT:
		vDir = vLeft;
		break;
	case RIGHT:
		vDir = vRight;
		break;
	case UP:
		vDir = vUp;
		break;
	case DOWN:
		vDir = vDown;
		break;
	case RIGHTDOWN:
		// 1:2 isometric이므로 세로 이동속도는 절반으로 수정
		vDir = vRight + (vDown/2.0f);
		break;
	case LEFTUP:
		vDir = vLeft + (vUp/2.0f);
		break;
	case LEFTDOWN:
		vDir = vLeft + (vDown/2.0f);
		break;
	case RIGHTUP:
		vDir = vRight + (vUp/2.0f);
		break;
	default:
		break;
	}
	
	vDir.Normalize();
	vMover = vDir*(100.0f * fdeltatime);

	return vMover;
}

// 이동간에 따른 무브무브
// 아마 onMove 보단 onControl
void mPlayer::onMove(float fdeltatime){
	VECTOR2D vMover = VECTOR2D(0.0f, 0.0f);

	// sprite data
	//leftdown (360.0f, 0.0f,39.0f, 94.0f, 6)
	//leftup (360.0f, 100.0f, 44.0f, 95.0f, 6)
	//rightdown (360.0f, 200.0f, 39.0f, 94.0f, 6)
	//rightup (360.0f, 300.0f, 44.0f, 95.0f, 6)
	// idle left up
	//(360.0f, 400.0f, 42.0f, 89.0f, 4)
	// idle right up
	//(360.0f, 500.0f, 42.0f, 89.0f, 4)
	// idle left down
	//(0.0f, 500.0f, 64.0f, 92.0f, 4)

	if (m_pControl->getKeyControlInfo()[VK_LEFT] &&
		m_pControl->getKeyControlInfo()[VK_DOWN]){
		m_SeeDir = LEFTDOWN;

		vMover = mPlayer::vectorMove(fdeltatime, LEFTDOWN);
		m_spriteAtlas->pickSpriteAtlas(360.0f, 0.0f, 39.0f, 94.0f, 6);		
	}

	else if (m_pControl->getKeyControlInfo()[VK_LEFT] &&
		m_pControl->getKeyControlInfo()[VK_UP]){
		m_SeeDir = LEFTUP;

		vMover = mPlayer::vectorMove(fdeltatime, LEFTUP);
		m_spriteAtlas->pickSpriteAtlas(360.0f, 100.0f, 44.0f, 95.0f, 6);		
	}

	else if (m_pControl->getKeyControlInfo()[VK_RIGHT] &&
		m_pControl->getKeyControlInfo()[VK_DOWN]){
		m_SeeDir = RIGHTDOWN;

		vMover = mPlayer::vectorMove(fdeltatime, RIGHTDOWN);
		m_spriteAtlas->pickSpriteAtlas(360.0f, 200.0f, 39.0f, 94.0f, 6);
	}

	else if (m_pControl->getKeyControlInfo()[VK_RIGHT] &&
		m_pControl->getKeyControlInfo()[VK_UP]){
		m_SeeDir = RIGHTUP;		
		
		vMover = mPlayer::vectorMove(fdeltatime, RIGHTUP);
		m_spriteAtlas->pickSpriteAtlas(360.0f, 300.0f, 44.0f, 95.0f, 6);		
	}

	else if (m_pControl->getKeyControlInfo()[VK_RIGHT]){
		if (m_SeeDir == LEFTUP){
			m_SeeDir = RIGHTUP;
		}
		else if (m_SeeDir == LEFTDOWN){
			m_SeeDir = RIGHTDOWN;
		}

		vMover = mPlayer::vectorMove(fdeltatime, RIGHT);
		m_spriteAtlas->pickSpriteAtlas(0.0f, 0.0f, 47.0f, 88.0f, 6);		
	}
	else if (m_pControl->getKeyControlInfo()[VK_LEFT]){
		if (m_SeeDir == RIGHTUP){
			m_SeeDir = LEFTUP;
		}
		else if (m_SeeDir == RIGHTDOWN){
			m_SeeDir = LEFTDOWN;
		}

		vMover = mPlayer::vectorMove(fdeltatime, LEFT);
		m_spriteAtlas->pickSpriteAtlas(0.0f, 185.0f, 47.0f, 88.0f, 6);		
	}
	else if (m_pControl->getKeyControlInfo()[VK_DOWN]){
		if (m_SeeDir == LEFTUP){
			m_SeeDir = LEFTDOWN;
		}
		else if (m_SeeDir == RIGHTUP){
			m_SeeDir = RIGHTDOWN;
		}

		vMover = mPlayer::vectorMove(fdeltatime, DOWN);
		m_spriteAtlas->pickSpriteAtlas(0.0f, 279.0f, 35.0f, 91.0f, 6);		
	}
	else if (m_pControl->getKeyControlInfo()[VK_UP]){
		if (m_SeeDir == LEFTDOWN){
			m_SeeDir = LEFTUP;
		}
		else if (m_SeeDir == RIGHTDOWN){
			m_SeeDir = RIGHTUP;
		}

		vMover = mPlayer::vectorMove(fdeltatime, UP);
		m_spriteAtlas->pickSpriteAtlas(0.0f, 373.0f, 37.0f, 92.0f, 6);		
	}
	else { // Idling

		if (m_SeeDir == RIGHTDOWN){
			// idle right down
			m_spriteAtlas->pickSpriteAtlas(0.0f, 92.0f, 64.0f, 92.0f, -19.5f, 0.0f, 4);			
			//m_spriteAtlas->pickSpriteAtlas(0.0f, 92.0f, 64.0f, 92.0f, 4);
		}
		else if (m_SeeDir == LEFTUP){
			m_spriteAtlas->pickSpriteAtlas(360.0f, 400.0f, 42.0f, 89.0f, 4);			
		}
		else if (m_SeeDir == RIGHTUP){
			m_spriteAtlas->pickSpriteAtlas(360.0f, 500.0f, 42.0f, 89.0f, 4);			
		}
		else if (m_SeeDir == LEFTDOWN){
			m_spriteAtlas->pickSpriteAtlas(0.0f, 500.0f, 64.0f, 92.0f, 19.5f, 0.0f, 4);
			//m_spriteAtlas->pickSpriteAtlas(0.0f, 500.0f, 64.0f, 92.0f, 4);
		}
	}
	
	// frame update
	m_spriteAtlas->nextFrame(fdeltatime);
	
	// Todo
	// 맵 포인터에서 맵 정보를 받아와서 이동 불가 컨트롤, 차후 동적할당식으로 전환
	// 맵 포인터는 스테이지가 바뀔때마다 업데이트를 해줘야 한다.
	// 컨트롤 클래스나, 월드클래스에서 조정해주면 더 나으려나?
	// 일단 자연스러운 오더링을 위해 이동불가는 둘 모두를 통해 이동불가 처리
	// 가장 좋은 건 사각형을 써서 오더링을 하는 걸까나?
	float topX = m_pTileMap->getTileCoordinates(*_drawVector + vMover).x;
	float topY = m_pTileMap->getTileCoordinates(*_drawVector + vMover).y;

	float bottomX = m_pTileMap->getTileCoordinates(*_realVector + vMover).x;
	float bottomY = m_pTileMap->getTileCoordinates(*_realVector + vMover).y;
	
	// move update, 여기서 float -> int 변환이 일어나 데이터 로스가 있을수도 있다.
	if (m_pTileMap->getMapinfo(static_cast<int>(topX), static_cast<int>(topY)) == 0
		&& m_pTileMap->getMapinfo(static_cast<int>(bottomX), static_cast<int>(bottomY)) == 0){
		*_realVector = *_realVector + vMover;
		*_drawVector = *_drawVector + vMover;		
	}
	//
}

void mPlayer::setTileMap(wTileMap* in){
	m_pTileMap = in;
}