#include "stdafx.h"
#include <stdlib.h>
#include "mMonster.h"
#include "VECTOR2D.h"
#include "uSprite.h"
#include "cD2DRenderer.h"
#include "uCamera.h"
#include "aiStateIdle.h"
#include "aiStateOnHit.h"
#include "wTileMap.h"

mMonster::mMonster()
{
	//
	srand(GetTickCount());
	//
	m_ipD2DBitmap = nullptr;
	_realVector = new VECTOR2D(200.0f, 300.0f);
	_drawVector = new VECTOR2D(_realVector->x, _realVector->y + 15.0f);
	m_dest = new VECTOR2D(_realVector->x, _realVector->y);

	m_spriteAtlas = new uSprite();

	m_pState = nullptr; // 현재 상태는 nullptr로 init

	m_SeeDir = RIGHTDOWN;
	m_State = ONIDLE;

	m_MAXHP = 100.0f;
	m_HP = 100.0f;
	m_moveSpeed = 20.0f;
}

mMonster::mMonster(float x, float y){
	//
	srand(GetTickCount());
	//
	m_ipD2DBitmap = nullptr;
	_realVector = new VECTOR2D(x, y);
	_drawVector = new VECTOR2D(_realVector->x, _realVector->y + 15.0f);
	m_dest = new VECTOR2D(_realVector->x, _realVector->y);

	m_spriteAtlas = new uSprite();
	m_pState = nullptr; // 현재 상태는 nullptr로 init

	m_SeeDir = RIGHTDOWN;
	m_State = ONIDLE;
	m_moveSpeed = 20.0f;
}

mMonster::~mMonster()
{
	SafeRelease(m_ipD2DBitmap);
	if (_drawVector != NULL){
		delete _drawVector;
	}
	if (m_spriteAtlas != NULL){
		delete m_spriteAtlas;
	}
}

void mMonster::onInit(cD2DRenderer& renderer){
	// 현재는 기본으로 포링이지만, 상속받아서 바꿀수 있다.
	HWND hWnd = renderer.GetHwnd();
	m_ipD2DBitmap = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/poring.png", NULL);
	// idle에서 시작
	m_pState = new aiStateIdle();
	m_pState->enter(this);	
}

//void mMonster::onInit(cD2DRenderer& renderer){
//	// 현재는 기본으로 포링이지만, 상속받아서 바꿀수 있다.
//	::mMonster::onInit(renderer);	
//}

void mMonster::onUpdate(float fdeltatime){
	m_fdeltatime = fdeltatime;
	m_pState->execute(this);
}

void mMonster::changeState(aiState* pnew){
	if (m_pState == nullptr || pnew == nullptr) return;
	m_pState->exit(this);
	delete m_pState;

	m_pState = pnew;
	m_pState->enter(this);
}

// 164, 39, 4frame
void mMonster::onIdle(){
	if (m_SeeDir == LEFTDOWN || m_SeeDir == RIGHTDOWN){
		m_spriteAtlas->pickSpriteAtlas(0.0f, 0.0f, 60.0f, 60.0f, 3);
		//m_spriteAtlas->pickSpriteAtlas(0.0f, 310.0f, 50.0f, 40.0f, 1);
	} 
	else if (m_SeeDir == LEFTUP || m_SeeDir == RIGHTUP){
		m_spriteAtlas->pickSpriteAtlas(240.0f, 0.0f, 60.0f, 60.0f, 3);
	}
	//mMonster::onHit();	
}

void mMonster::onAttack(){
}

void mMonster::onHit(){
	if (m_SeeDir == LEFTDOWN || m_SeeDir == RIGHTDOWN){
		m_spriteAtlas->pickSpriteAtlas(0.0f, 210.0f, 50.0f, 40.0f, 1);
		//m_spriteAtlas->pickSpriteAtlas(10.0f, 210.0f, 40.0f, 40.0f, 1);
	}
	else if (m_SeeDir == LEFTUP || m_SeeDir == RIGHTUP){
		m_spriteAtlas->pickSpriteAtlas(0.0f, 310.0f, 50.0f, 40.0f, 1);
		//m_spriteAtlas->pickSpriteAtlas(240.0f, 0.0f, 60.0f, 60.0f, 1);
	}
}

void mMonster::onDeath(){
	if (m_SeeDir == LEFTDOWN || m_SeeDir == RIGHTDOWN){
		m_spriteAtlas->pickSpriteAtlas(0.0f, 210.0f, 50.0f, 40.0f, 1);
		//m_spriteAtlas->pickSpriteAtlas(10.0f, 210.0f, 40.0f, 40.0f, 1);
	}
	else if (m_SeeDir == LEFTUP || m_SeeDir == RIGHTUP){
		m_spriteAtlas->pickSpriteAtlas(0.0f, 310.0f, 50.0f, 40.0f, 1);
		//m_spriteAtlas->pickSpriteAtlas(240.0f, 0.0f, 60.0f, 60.0f, 1);
	}
}

void mMonster::onMove(){
	if (m_SeeDir == LEFTDOWN || m_SeeDir == RIGHTDOWN){
		m_spriteAtlas->pickSpriteAtlas(0.0f, 68.0f, 53.0f, 40.0f, 7);
	}
	else if (m_SeeDir == LEFTUP || m_SeeDir == RIGHTUP){
		m_spriteAtlas->pickSpriteAtlas(0.0f, 128.0f, 50.0f, 40.0f, 7);
	}
}

void mMonster::onRender(cD2DRenderer& renderer){
	if (m_ipD2DBitmap != nullptr){
		//
		VECTOR2D cpos = m_Cam->translasteToScreen(_drawVector);
		//
		// Pivot 이미지의 한가운데 바닥 -> dxArea에서 지정
		::D2D1_RECT_F dxArea
			= m_spriteAtlas->getCoordinateFromPivot(cpos);
			
			//= m_spriteAtlas->getCoordinateFromPivot(cpos);

		//	
		::D2D1_RECT_F srcArea
			= m_spriteAtlas->getSrcFrameFromSprite();
				
		if (m_SeeDir == LEFTDOWN || m_SeeDir == LEFTUP){
			renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, m_alpha,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
		else if (m_SeeDir == RIGHTDOWN || m_SeeDir == RIGHTUP) {
			renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Scale(
				D2D1::Size(-1.0f, 1.0f),
				D2D1::Point2F(cpos.x, cpos.y)));
			
			renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, m_alpha,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);

			renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
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

void mMonster::getHit(float dmg){	
	mIObject::getHit(dmg);
	if (this->getHealth() >= 0.0f){
		m_State = ONHIT;
	}
}
void mMonster::setDestinTile(float x, float y){
	VECTOR2D in;
	in.x = x*m_pTileMap->getRectTileWidth();
	in.y = y*m_pTileMap->getRectTileHeight();
	in = m_pTileMap->twoDtoISO(in);
	setDest(in.x, in.y);
}
void mMonster::setDest(float x, float y){
	m_dest->x = x;
	m_dest->y = y;
}
// todo: 상하좌우 움직임 없앨것 (알고리즘을 그렇게 처리)
void mMonster::moveToDest(float deltaTime){
	VECTOR2D vMover;
	if (m_dest->x < _realVector->x && m_dest->y < _realVector->y){
		vMover= mIObject::vectorMove(deltaTime, LEFTUP);
		m_SeeDir = LEFTUP;
	}
	else if (m_dest->x > _realVector->x && m_dest->y > _realVector->y){
		vMover= mIObject::vectorMove(deltaTime, RIGHTDOWN);
		m_SeeDir = RIGHTDOWN;
	}
	else if (m_dest->x < _realVector->x && m_dest->y > _realVector->y){
		vMover = mIObject::vectorMove(deltaTime, LEFTDOWN);
		m_SeeDir = LEFTDOWN;
	}
	else if (m_dest->x > _realVector->x && m_dest->y < _realVector->y){
		vMover= mIObject::vectorMove(deltaTime, RIGHTUP);
		m_SeeDir = RIGHTUP;
	}
	else if (m_dest->x < _realVector->x){
		vMover = mIObject::vectorMove(deltaTime, LEFT);
		if (m_SeeDir == RIGHTUP){
			m_SeeDir = LEFTUP;
		}
		else if (m_SeeDir == RIGHTDOWN){
			m_SeeDir = LEFTDOWN;
		}			
	}
	else if (m_dest->x > _realVector->x){
		vMover = mIObject::vectorMove(deltaTime, RIGHT);
		if (m_SeeDir == LEFTUP){
			m_SeeDir = RIGHTUP;
		}
		else if (m_SeeDir == LEFTDOWN){
			m_SeeDir = RIGHTDOWN;
		}
	}
	else if (m_dest->y < _realVector->y){
		vMover= mIObject::vectorMove(deltaTime, UP);
		if (m_SeeDir == LEFTDOWN){
			m_SeeDir = LEFTUP;
		}
		else if (m_SeeDir == RIGHTDOWN){
			m_SeeDir = RIGHTUP;
		}
	}
	else if (m_dest->y > _realVector->y){
		vMover = mIObject::vectorMove(deltaTime, DOWN);
		if (m_SeeDir == LEFTUP){
			m_SeeDir = LEFTDOWN;
		}
		else if (m_SeeDir == RIGHTUP){
			m_SeeDir = RIGHTDOWN;
		}
	}

	*_realVector = *_realVector + vMover;
	*_drawVector = *_drawVector + vMover;
	
	// 플롯 벡터 움직임 오차범위
	// 플롯이고, 또한 벡터 무빙으로 움직이기 때문에 어느정도의 오차는 발생한다.
	// 오차범위내에 들어가면 도착한걸로 결정
	float tolerance = 0.5f;
	if (abs(_realVector->x - m_dest->x) < tolerance){
		m_dest->x = _realVector->x;
	}
	if (abs(_realVector->y - m_dest->y) < tolerance){
		m_dest->y = _realVector->y;
	}	
}

void mMonster::moveRandom(){
	VECTOR2D adder;
	VECTOR2D destTilePos;
	VECTOR2D currentPosinTile = m_pTileMap->getTileCoordinates(*_realVector);
	adder.x = static_cast<float>(rand() % 2);
	adder.y = static_cast<float>(rand() % 2);
	if (rand() % 2 == 0){
		adder.x *= -1;
	}
	if (rand() % 2 == 0){
		adder.y *= -1;
	}

	destTilePos.x = currentPosinTile.x + adder.x;
	destTilePos.y = currentPosinTile.y + adder.y;

	// 외곽 충돌 처리, 만약 랜덤 무브가 외곽으로 벗어나려고 할시
	// 아예 해당 프로세스 자체를 취소한다.
	if (destTilePos.x >= m_pTileMap->getMapLimit().x || 
		destTilePos.y >= m_pTileMap->getMapLimit().y ||
		destTilePos.x <= 0 || destTilePos.y <= 0){
		return;
	}

	// todo: 이동 불가타일 이동 불가하게 만들기

	destTilePos.x = destTilePos.x * 45.0f;
	destTilePos.y = destTilePos.y * 45.0f;

	destTilePos = m_pTileMap->twoDtoISO(destTilePos);
	m_dest->x = destTilePos.x;
	m_dest->y = destTilePos.y;
}