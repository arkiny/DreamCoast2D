#include "stdafx.h"
#include "cD2DRenderer.h"
#include "mPlayer.h"
#include "coControl.h"
#include "VECTOR2D.h"
#include "uSprite.h"
#include "wTileMap.h"
#include "uCamera.h"
#include "uTile.h"

mPlayer::mPlayer()
{	
	m_ipD2DBitmap = nullptr;
	m_Cam = nullptr;
	
	//todo: 임시로 중앙에 대기, 차후 맵정보에 따라 시작점 정보 수정	
	_realVector = new VECTOR2D(514.0f, 384.0f);
	_drawVector = new VECTOR2D(_realVector->x, _realVector->y + 15.0f);
	m_spriteAtlas = new uSprite();
	m_SeeDir = RIGHTDOWN;
	m_State = ONMOVE;

	m_MAXHP = 2000.0f;
	m_MAXMP = 200.0f;
	m_HP = 2000.0f;
	m_MP = 200.0f;
}


mPlayer::~mPlayer()
{
	SafeRelease(m_ipD2DBitmap);
	if (m_Cam != NULL){
		delete m_Cam;
	}
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
	m_Cam = new uCamera(1028.0, 768.0f, this->getRealPos());
}

void mPlayer::onUpdate(float fdeltatime){	
	// 대단히 primitive한 컨디션 스테잇을 이용한 statecontroller, 
	// 차후 시간이 남으면 statemachine으로 교체
	
	if (m_State == ONDEAD){
		// 플레이어 사망 처리, 가장 기본적인 DeadEnd State
		// 가장 1순위 처리는 사망시 처리,
		mPlayer::onDead(fdeltatime);
	}
	else if (m_State == ONHIT){
		// 가장 우선순위가 높은 건 피격 판정 액션, 경직 타임도 있어야하고...
		// 피격 경직시에는 모든 컨트롤 불가...
		// 차후 아이템이나 스킬에 따라 피격 판정시 경직 제거
		//(피격시 wTileMap에서 callback으로 getHit() 함수 콜이 되고 state가 변경됨)
		// 후에 IDLE로 상태 변경... 일단 여기서 움직임이 없을 경우
		// ONMOVE에서 처리했으므로 ONMOVE로 처리
		mPlayer::onHit(fdeltatime);
	}
	else if (m_pControl->getKeyControlInfo()[0x5A]){
		if (m_State == ONATTACK){
			mPlayer::onAttack(fdeltatime);
		}
		else {
			m_State = ONATTACK;
			m_attackaccumtime = 0.0f;
			m_spriteAtlas->setCurrentFrame(0);			
		}
	}
	else if (m_State == ONATTACK){
		mPlayer::onAttack(fdeltatime);
	}
	else if (m_State == ONMOVE){
		m_attackaccumtime = 0.0f;
		mPlayer::onMove(fdeltatime);
	}
}

void mPlayer::onHit(float fdeltatime){
	// 경직 시간은 FRAMERATE의 딱 두배
	if (m_onhitAccumtime < FRAMERATE * 2.0f){
		m_onhitAccumtime += fdeltatime;
	}
	else {
		// 맞은 이후 일정 시간이 지났을 경우
		// Idle상태로 돌아감
		m_onhitAccumtime = 0.0f;
		m_State = ONMOVE;
	}

	//
	if (m_SeeDir == LEFTDOWN){
		m_spriteAtlas->pickSpriteAtlas(700.0f, 0.0f, 49.0f, 73.0f,  1);
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

// 피격 시 처리 (체력감소)
void mPlayer::getHit(float dmg){
	mIObject::getHit(dmg);
	if (this->getHealth() >= 0.0f){
		m_State = ONHIT;
	}
	else {
		m_State = ONDEAD;
	}
}

// todo: 공속조정 변수가 필요함
void mPlayer::onAttack(float fdeltatime){
	// fdeltatime을 받아서 일정 시간에 도달하였을 경우 attack처리
	m_attackaccumtime += fdeltatime;

	//bool attacktrigger = false;
	VECTOR2D currentTile = m_pTileMap->getTileCoordinates(*_realVector);
	float fx, fy;

	if (m_attackaccumtime > FRAMERATE * 2.0f){
		//attacktrigger = true;
		m_attackaccumtime = 0.0f;
		if (m_SeeDir == LEFTDOWN){
			fx = currentTile.x + 1.0f;
			fy = currentTile.y;
		}
		else if (m_SeeDir == LEFTUP){
			fx = currentTile.x;
			fy = currentTile.y - 1.0f;
		}
		else if (m_SeeDir == RIGHTDOWN){
			fx = currentTile.x;
			fy = currentTile.y + 1.0f;
		}
		else if (m_SeeDir == RIGHTUP){
			fx = currentTile.x - 1.0f;;
			fy = currentTile.y;
		}
		else {}
		// 같은 타일내에 겹쳐 있을수도 있으므로...
		// 차후 이 자리에는 타일 onHIT계열이 들어간다. 
		m_pTileMap->getTile(currentTile.x, currentTile.y)->onHit(10.0f);
		m_pTileMap->getTile(fx, fy)->onHit(10.0f);
	}

	if (m_spriteAtlas->getCurrentFrame() == 7){
		m_spriteAtlas->setCurrentFrame(0);
		m_State = ONMOVE;
		return;
	}

	// 데미지 처리는 일정 프레임에 트리거 되도록 -> 일정 시간에 트리거되도록함
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

// 키를 받아와서 업데이트(connector)-> todo: 인자를 const로 바꿔서 항상성 유지
void mPlayer::setKeyControl(coControl* in){
	m_pControl = in;
}

//void mPlayer::onIdle(){
//
//}

// 이동간에 따른 무브무브
// 아마 onMove 보단 onControl
void mPlayer::onMove(float fdeltatime){
	VECTOR2D vMover = VECTOR2D(0.0f, 0.0f);

	// Animation Part
	if (m_pControl->getKeyControlInfo()[VK_LEFT] &&
		m_pControl->getKeyControlInfo()[VK_DOWN]){
		m_SeeDir = LEFTDOWN;

		vMover = mIObject::vectorMove(fdeltatime, LEFTDOWN);
		m_spriteAtlas->pickSpriteAtlas(360.0f, 0.0f, 39.0f, 94.0f, 6);		
	}

	else if (m_pControl->getKeyControlInfo()[VK_LEFT] &&
		m_pControl->getKeyControlInfo()[VK_UP]){
		m_SeeDir = LEFTUP;

		vMover = mIObject::vectorMove(fdeltatime, LEFTUP);
		m_spriteAtlas->pickSpriteAtlas(360.0f, 100.0f, 44.0f, 95.0f, 6);		
	}

	else if (m_pControl->getKeyControlInfo()[VK_RIGHT] &&
		m_pControl->getKeyControlInfo()[VK_DOWN]){
		m_SeeDir = RIGHTDOWN;

		vMover = mIObject::vectorMove(fdeltatime, RIGHTDOWN);
		m_spriteAtlas->pickSpriteAtlas(360.0f, 200.0f, 39.0f, 94.0f, 6);
	}

	else if (m_pControl->getKeyControlInfo()[VK_RIGHT] &&
		m_pControl->getKeyControlInfo()[VK_UP]){
		m_SeeDir = RIGHTUP;		
		
		vMover = mIObject::vectorMove(fdeltatime, RIGHTUP);
		m_spriteAtlas->pickSpriteAtlas(360.0f, 300.0f, 44.0f, 95.0f, 6);		
	}

	else if (m_pControl->getKeyControlInfo()[VK_RIGHT]){
		if (m_SeeDir == LEFTUP){
			m_SeeDir = RIGHTUP;
		}
		else if (m_SeeDir == LEFTDOWN){
			m_SeeDir = RIGHTDOWN;
		}

		vMover = mIObject::vectorMove(fdeltatime, RIGHT);
		m_spriteAtlas->pickSpriteAtlas(0.0f, 0.0f, 47.0f, 88.0f, 6);		
	}
	else if (m_pControl->getKeyControlInfo()[VK_LEFT]){
		if (m_SeeDir == RIGHTUP){
			m_SeeDir = LEFTUP;
		}
		else if (m_SeeDir == RIGHTDOWN){
			m_SeeDir = LEFTDOWN;
		}

		vMover = mIObject::vectorMove(fdeltatime, LEFT);
		m_spriteAtlas->pickSpriteAtlas(0.0f, 185.0f, 47.0f, 88.0f, 6);		
	}
	else if (m_pControl->getKeyControlInfo()[VK_DOWN]){
		if (m_SeeDir == LEFTUP){
			m_SeeDir = LEFTDOWN;
		}
		else if (m_SeeDir == RIGHTUP){
			m_SeeDir = RIGHTDOWN;
		}

		vMover = mIObject::vectorMove(fdeltatime, DOWN);
		m_spriteAtlas->pickSpriteAtlas(0.0f, 279.0f, 35.0f, 91.0f, 6);		
	}
	else if (m_pControl->getKeyControlInfo()[VK_UP]){
		if (m_SeeDir == LEFTDOWN){
			m_SeeDir = LEFTUP;
		}
		else if (m_SeeDir == RIGHTDOWN){
			m_SeeDir = RIGHTUP;
		}

		vMover = mIObject::vectorMove(fdeltatime, UP);
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

	// 외곽 충돌 처리
	if (topX >= m_pTileMap->getMapLimit().x || topY >= m_pTileMap->getMapLimit().y||
		bottomX >= m_pTileMap->getMapLimit().x || bottomY >= m_pTileMap->getMapLimit().y||
		topX < 0 || topY < 0 ||bottomX < 0 || bottomY < 0){
		return;
	}

	// 이동불가시 이동불가 처리
	// move update, 여기서 float -> int 변환이 일어나 데이터 로스가 있을수도 있다.
	// 게임 특성상 몬스터와의 충돌처리는 아직 없음(만약 보스형이라면 충돌 처리가 있어야할지도)
	if (m_pTileMap->getMapinfo(static_cast<int>(topX), static_cast<int>(topY)) == 0
		&& m_pTileMap->getMapinfo(static_cast<int>(bottomX), static_cast<int>(bottomY)) == 0){
		*_realVector = *_realVector + vMover;
		*_drawVector = *_drawVector + vMover;		
	}
	//
}

void mPlayer::onRender(cD2DRenderer& renderer){
	if (m_ipD2DBitmap != nullptr){
		//
		VECTOR2D cpos = m_Cam->translasteToScreen(_drawVector);
		//
		// Pivot 이미지의 한가운데 바닥 -> dxArea에서 지정
		::D2D1_RECT_F dxArea
			= m_spriteAtlas->getCoordinateFromPivot(cpos);

		//	
		::D2D1_RECT_F srcArea
			= m_spriteAtlas->getSrcFrameFromSprite();

		renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, m_alpha,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
		
		//회전등에 필요한 부분
		//renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());

		//debug 용
		renderer.GetRenderTarget()->DrawRectangle(dxArea, renderer.GetBrush());
		
		::D2D1_RECT_F pivotArea;
		pivotArea.top = cpos.y - 2.0f;
		pivotArea.bottom = cpos.y + 2.0f;
		pivotArea.left = cpos.x - 2.0f;
		pivotArea.right = cpos.x + 2.0f;
		renderer.GetRenderTarget()->DrawRectangle(pivotArea, renderer.GetBrush());
		
		//renderer.GetRenderTarget()->DrawRectangle(dxArea, renderer.GetBrush());
		//pivotArea;
		cpos = m_Cam->translasteToScreen(_realVector);
		pivotArea.top = cpos.y - 2.0f;
		pivotArea.bottom = cpos.y + 2.0f;
		pivotArea.left = cpos.x - 2.0f;
		pivotArea.right = cpos.x + 2.0f;
		renderer.GetRenderTarget()->DrawRectangle(pivotArea, renderer.GetBrush());
	}
}

void mPlayer::onRender(cD2DRenderer& renderer, bool alpha){
	if (m_ipD2DBitmap != nullptr){
		VECTOR2D cpos = m_Cam->translasteToScreen(_drawVector);
		// Pivot 이미지의 한가운데 바닥 -> dxArea에서 지정
		::D2D1_RECT_F dxArea
			= m_spriteAtlas->getCoordinateFromPivot(cpos);

		//	
		::D2D1_RECT_F srcArea
			= m_spriteAtlas->getSrcFrameFromSprite();

		if (alpha){
			renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, 0.4f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
		//회전등에 필요한 부분
		//renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());

		//debug 용
		renderer.GetRenderTarget()->DrawRectangle(dxArea, renderer.GetBrush());

		::D2D1_RECT_F pivotArea;
		pivotArea.top = cpos.y - 2.0f;
		pivotArea.bottom = cpos.y + 2.0f;
		pivotArea.left = cpos.x - 2.0f;
		pivotArea.right = cpos.x + 2.0f;
		renderer.GetRenderTarget()->DrawRectangle(pivotArea, renderer.GetBrush());


		//renderer.GetRenderTarget()->DrawRectangle(dxArea, renderer.GetBrush());
		//pivotArea;
		cpos = m_Cam->translasteToScreen(_realVector);
		pivotArea.top = cpos.y - 2.0f;
		pivotArea.bottom = cpos.y + 2.0f;
		pivotArea.left = cpos.x - 2.0f;
		pivotArea.right = cpos.x + 2.0f;
		renderer.GetRenderTarget()->DrawRectangle(pivotArea, renderer.GetBrush());
	}
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

	//// 사망시 페이드아웃 효과
	//pmon->setAlpha(pmon->getAlpha() - 0.025f);

	//// 차후 delete 보다는 setVisible을 이용해서
	//// 다시 이용하는 방법도 있을 듯 하뎌이다
	//// 일정 시간이 지난 뒤 삭제 trigger on
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
	if (m_deadFadeOutTime > FRAMERATE*20.0f){
	//if (m_alpha <= 0.0f){
		// todo: 페이드아웃 종료후 게임 오버 처리
		m_deadcomp = true;
	}
}