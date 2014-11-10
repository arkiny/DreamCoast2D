#include "stdafx.h"
#include <stdlib.h>
#include "mMonster.h"
#include "VECTOR2D.h"
#include "uSprite.h"
#include "cD2DRenderer.h"
#include "uCamera.h"
#include "aiStateIdle.h"
#include "wTileMap.h"
#include "cResourceManager.h"
#include "mGFX.h"
#include "mEffect.h"

#include "char_client.h"
#include "movePacket.h"
#include "netWorkCharManager.h"

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
	if (_drawVector != NULL){
		delete _drawVector;
	}
	if (m_spriteAtlas != NULL){
		delete m_spriteAtlas;
	}
	if (m_pState != NULL){
		delete m_pState;
	}
}

void mMonster::onInit(){
	// 현재는 기본으로 포링이지만, 상속받아서 바꿀수 있다.
	// 여기서 몬스터 타입에 따라 스프라이트 배정
	m_ipD2DBitmap = ::cResourceManager::GetInstance().getMobBitMap(m_nMonsterType);
	//m_ipD2DBitmap = ::cResourceManager::GetInstance().getMobBitMap(2);
	//resource;
	// idle에서 시작

	if (m_nMonsterType == 2){
		m_visionRange = 5.0;
		//m_attackRange = 1.0;
		m_moveSpeed = 150.0f;
		m_MAXHP = 1000.0f;
		m_HP = 1000.0f;
	}

	m_pState = new aiStateIdle();
	m_pState->enter(this);	
}

void mMonster::setMobID(int id){
	m_nMobID = id;
}

//void mMonster::onInit(cD2DRenderer& renderer){
//	// 현재는 기본으로 포링이지만, 상속받아서 바꿀수 있다.
//	::mMonster::onInit(renderer);	
//}

void mMonster::onUpdate(float fdeltatime){
	m_fdeltatime = fdeltatime;
	//
	if (m_nMonsterType == 2 && m_fcurAggroLevel == m_fMaxAggroLevel){
		m_skillAccumtime += fdeltatime;
	}
	//
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
		SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(m_nMonsterType, 0, 0);
		//SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(2, 0, 0);
		m_spriteAtlas->pickSpriteAtlas(
			in->x,
			in->y,
			in->width,
			in->height,
			in->offsetX,
			in->offsetY,
			in->maxFrame);
		//m_spriteAtlas->pickSpriteAtlas(0.0f, 310.0f, 50.0f, 40.0f, 1);
	} 
	else if (m_SeeDir == LEFTUP || m_SeeDir == RIGHTUP){
		//m_spriteAtlas->pickSpriteAtlas(240.0f, 0.0f, 60.0f, 60.0f, 0.0f, 5.0f, 3);

		SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(m_nMonsterType, 0, 1);
		//SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(2, 0, 1);
		m_spriteAtlas->pickSpriteAtlas(
			in->x,
			in->y,
			in->width,
			in->height,
			in->offsetX,
			in->offsetY,
			in->maxFrame);
	}
	//mMonster::onHit();	
	
}

void mMonster::onAttack(){
	//if (m_nMonsterType != 0 || m_nMonsterType != 1){
		if (m_SeeDir == LEFTDOWN || m_SeeDir == RIGHTDOWN){
			SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(m_nMonsterType, 2, 0);
			//SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(2, 2, 0);
			m_spriteAtlas->pickSpriteAtlas(
				in->x,
				in->y,
				in->width,
				in->height,
				in->offsetX,
				in->offsetY,
				in->maxFrame);
			//m_spriteAtlas->pickSpriteAtlas(0.0f, 310.0f, 50.0f, 40.0f, 1);
		}
		else if (m_SeeDir == LEFTUP || m_SeeDir == RIGHTUP){
			//m_spriteAtlas->pickSpriteAtlas(240.0f, 0.0f, 60.0f, 60.0f, 0.0f, 5.0f, 3);

			SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(m_nMonsterType, 2, 1);
			//SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(2, 2, 1);
			m_spriteAtlas->pickSpriteAtlas(
				in->x,
				in->y,
				in->width,
				in->height,
				in->offsetX,
				in->offsetY,
				in->maxFrame);
		}
	//}
}

void mMonster::onHit(){
	if (m_SeeDir == LEFTDOWN || m_SeeDir == RIGHTDOWN){
		//m_spriteAtlas->pickSpriteAtlas(0.0f, 210.0f, 50.0f, 40.0f, 1);
		/*m_spriteAtlas->pickSpriteAtlas(
			cResourceManager::GetInstance().getMonsterSpriteInfo(m_nMonsterType, 4, 0)->x,
			cResourceManager::GetInstance().getMonsterSpriteInfo(m_nMonsterType, 4, 0)->y,
			cResourceManager::GetInstance().getMonsterSpriteInfo(m_nMonsterType, 4, 0)->width,
			cResourceManager::GetInstance().getMonsterSpriteInfo(m_nMonsterType, 4, 0)->height,
			cResourceManager::GetInstance().getMonsterSpriteInfo(m_nMonsterType, 4, 0)->offsetX,
			cResourceManager::GetInstance().getMonsterSpriteInfo(m_nMonsterType, 4, 0)->offsetY,
			cResourceManager::GetInstance().getMonsterSpriteInfo(m_nMonsterType, 4, 0)->maxFrame);*/
		SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(m_nMonsterType, 4, 0);
		//SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(2, 4, 0);
		m_spriteAtlas->pickSpriteAtlas(
			in->x,
			in->y,
			in->width,
			in->height,
			in->offsetX,
			in->offsetY,
			in->maxFrame);
		//m_spriteAtlas->pickSpriteAtlas(10.0f, 210.0f, 40.0f, 40.0f, 1);
	}
	else if (m_SeeDir == LEFTUP || m_SeeDir == RIGHTUP){
		//m_spriteAtlas->pickSpriteAtlas(0.0f, 310.0f, 50.0f, 40.0f, 1);
		/*m_spriteAtlas->pickSpriteAtlas(
			cResourceManager::GetInstance().getMonsterSpriteInfo(m_nMonsterType, 4, 1)->x,
			cResourceManager::GetInstance().getMonsterSpriteInfo(m_nMonsterType, 4, 1)->y,
			cResourceManager::GetInstance().getMonsterSpriteInfo(m_nMonsterType, 4, 1)->width,
			cResourceManager::GetInstance().getMonsterSpriteInfo(m_nMonsterType, 4, 1)->height,
			cResourceManager::GetInstance().getMonsterSpriteInfo(m_nMonsterType, 4, 1)->offsetX,
			cResourceManager::GetInstance().getMonsterSpriteInfo(m_nMonsterType, 4, 1)->offsetY,
			cResourceManager::GetInstance().getMonsterSpriteInfo(m_nMonsterType, 4, 1)->maxFrame);*/
		SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(m_nMonsterType, 4, 1);
		//SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(2, 4, 1);
		m_spriteAtlas->pickSpriteAtlas(
			in->x,
			in->y,
			in->width,
			in->height,
			in->offsetX,
			in->offsetY,
			in->maxFrame);
		//m_spriteAtlas->pickSpriteAtlas(240.0f, 0.0f, 60.0f, 60.0f, 1);
	}
}

void mMonster::onDeath(){
	if (m_SeeDir == LEFTDOWN || m_SeeDir == RIGHTDOWN){
		//m_spriteAtlas->pickSpriteAtlas(0.0f, 210.0f, 50.0f, 40.0f, 1);
		/*m_spriteAtlas->pickSpriteAtlas(
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,5, 0)->x,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,5, 0)->y,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,5, 0)->width,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,5, 0)->height,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,5, 0)->offsetX,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,5, 0)->offsetY,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,5, 0)->maxFrame);*/
		SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(m_nMonsterType, 5, 0);
		//SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(2, 5, 0);
		m_spriteAtlas->pickSpriteAtlas(
			in->x,
			in->y,
			in->width,
			in->height,
			in->offsetX,
			in->offsetY,
			in->maxFrame);
		//m_spriteAtlas->pickSpriteAtlas(10.0f, 210.0f, 40.0f, 40.0f, 1);
	}
	else if (m_SeeDir == LEFTUP || m_SeeDir == RIGHTUP){
		//m_spriteAtlas->pickSpriteAtlas(0.0f, 310.0f, 50.0f, 40.0f, 1);
		/*m_spriteAtlas->pickSpriteAtlas(
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,5, 1)->x,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,5, 1)->y,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,5, 1)->width,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,5, 1)->height,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,5, 1)->offsetX,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,5, 1)->offsetY,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,5, 1)->maxFrame);*/
		SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(m_nMonsterType, 5, 1);
		//SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(2, 5, 1);
		m_spriteAtlas->pickSpriteAtlas(
			in->x,
			in->y,
			in->width,
			in->height,
			in->offsetX,
			in->offsetY,
			in->maxFrame);
		//m_spriteAtlas->pickSpriteAtlas(240.0f, 0.0f, 60.0f, 60.0f, 1);
	}
}

void mMonster::onMove(){
	if (m_SeeDir == LEFTDOWN || m_SeeDir == RIGHTDOWN){
		//m_spriteAtlas->pickSpriteAtlas(0.0f, 68.0f, 53.0f, 40.0f, 7);
		/*m_spriteAtlas->pickSpriteAtlas(
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 0)->x,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 0)->y,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 0)->width,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 0)->height,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 0)->offsetX,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 0)->offsetY,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 0)->maxFrame);*/
		SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(m_nMonsterType, 1, 0);
		//SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(2, 1, 0);
		m_spriteAtlas->pickSpriteAtlas(
			in->x,
			in->y,
			in->width,
			in->height,
			in->offsetX,
			in->offsetY,
			in->maxFrame);
	}
	else if (m_SeeDir == LEFTUP || m_SeeDir == RIGHTUP){
		/*m_spriteAtlas->pickSpriteAtlas(
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 1)->x,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 1)->y,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 1)->width,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 1)->height,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 1)->offsetX,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 1)->offsetY,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 1)->maxFrame);*/
		SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(m_nMonsterType, 1, 1);
		//SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(2, 1, 1);
		m_spriteAtlas->pickSpriteAtlas(
			in->x,
			in->y,
			in->width,
			in->height,
			in->offsetX,
			in->offsetY,
			in->maxFrame);
	}
}

void mMonster::onCasting(){
	if (m_SeeDir == LEFTDOWN || m_SeeDir == RIGHTDOWN){
		//m_spriteAtlas->pickSpriteAtlas(0.0f, 68.0f, 53.0f, 40.0f, 7);
		/*m_spriteAtlas->pickSpriteAtlas(
		cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 0)->x,
		cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 0)->y,
		cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 0)->width,
		cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 0)->height,
		cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 0)->offsetX,
		cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 0)->offsetY,
		cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 0)->maxFrame);*/
		SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(m_nMonsterType, 3, 0);
		//SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(2, 1, 0);
		m_spriteAtlas->pickSpriteAtlas(
			in->x,
			in->y,
			in->width,
			in->height,
			in->offsetX,
			in->offsetY,
			in->maxFrame);
	}
	else if (m_SeeDir == LEFTUP || m_SeeDir == RIGHTUP){
		/*m_spriteAtlas->pickSpriteAtlas(
		cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 1)->x,
		cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 1)->y,
		cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 1)->width,
		cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 1)->height,
		cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 1)->offsetX,
		cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 1)->offsetY,
		cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 1)->maxFrame);*/
		SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(m_nMonsterType, 3, 1);
		//SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(2, 1, 1);
		m_spriteAtlas->pickSpriteAtlas(
			in->x,
			in->y,
			in->width,
			in->height,
			in->offsetX,
			in->offsetY,
			in->maxFrame);
	}
}

void mMonster::onRender(){
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
			::cD2DRenderer::GetInstance().GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, m_alpha,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
		else if (m_SeeDir == RIGHTDOWN || m_SeeDir == RIGHTUP) {
			::cD2DRenderer::GetInstance().GetRenderTarget()->SetTransform(
				D2D1::Matrix3x2F::Scale(D2D1::Size(-1.0f, 1.0f), D2D1::Point2F(cpos.x, cpos.y)));
			
			::cD2DRenderer::GetInstance().GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, m_alpha,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);

			::cD2DRenderer::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
		}
		// debug
		if (m_nMonsterType != 0){
			wchar_t* wszText_ = new wchar_t[4];
			int length = 0;
			length += swprintf(wszText_ + length, 4, L"A");
			UINT32 cTextLength_ = (UINT32)wcslen(wszText_);

			::cD2DRenderer::GetInstance().GetRenderTarget()->DrawTextW(
				wszText_,
				cTextLength_,
				::cD2DRenderer::GetInstance().GetTextFormat2(),
				dxArea,
				::cD2DRenderer::GetInstance().GetBlackBrush());

			delete[] wszText_;

		}

		//if (this->getDmg() > 0){
		//	/// 텍스트 출력
		//	wchar_t* wszText_ = new wchar_t[20];
		//	swprintf(wszText_, 20, L" %.0f",
		//		this->getDmg());
		//	UINT32 cTextLength_ = (UINT32)wcslen(wszText_);

		//	D2D1_RECT_F layoutRect = dxArea;
		//	// draw text
		//	::cD2DRenderer::GetInstance().GetRenderTarget()->DrawTextW(
		//		wszText_,
		//		cTextLength_,
		//		::cD2DRenderer::GetInstance().GetTextFormatDmg(),
		//		layoutRect,
		//		::cD2DRenderer::GetInstance().GetRedBrush());
		//}
		::D2D1_RECT_F pointer;
		pointer.top = dxArea.top - 8.0f;
		pointer.left = cpos.x - 3.0f;
		pointer.bottom = dxArea.top - 2.0f;
		pointer.right = cpos.x + 3.0f;
		::cD2DRenderer::GetInstance().GetRenderTarget()->FillRectangle(pointer, ::cD2DRenderer::GetInstance().GetRedBrush());
		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(pointer, ::cD2DRenderer::GetInstance().GetBlackBrush());

		//회전등에 필요한 부분
		//renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());

		////debug 용
		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(dxArea, ::cD2DRenderer::GetInstance().GetBlackBrush());

		::D2D1_RECT_F pivotArea;
		pivotArea.top = cpos.y - 2.0f;
		pivotArea.bottom = cpos.y + 2.0f;
		pivotArea.left = cpos.x - 2.0f;
		pivotArea.right = cpos.x + 2.0f;
		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(pivotArea, ::cD2DRenderer::GetInstance().GetBlackBrush());

		//renderer.GetRenderTarget()->DrawRectangle(dxArea, renderer.GetBlackBrush());
		//pivotArea;
		cpos = m_Cam->translasteToScreen(_realVector);
		pivotArea.top = cpos.y - 2.0f;
		pivotArea.bottom = cpos.y + 2.0f;
		pivotArea.left = cpos.x - 2.0f;
		pivotArea.right = cpos.x + 2.0f;
		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(pivotArea, ::cD2DRenderer::GetInstance().GetBlackBrush());
	}
}

void mMonster::getHit(float dmg){	
	mCharacter::getHit(dmg);
	
	if (this->getHealth() >= 0.0f){
		m_State = ONHIT;
	}

	mGFX::GetInstance().pushToEventQueue(new mEffect(0, dmg, new VECTOR2D(*_drawVector), m_Cam));
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

	//movePacket toServer;

	

	if (m_dest->x < _realVector->x && m_dest->y < _realVector->y){
		vMover= mCharacter::vectorMove(deltaTime, LEFTUP);
		m_SeeDir = LEFTUP;
		/*toServer.direction = LEFTUP;
		toServer.seedir = LEFTUP;*/
	}
	else if (m_dest->x > _realVector->x && m_dest->y > _realVector->y){
		vMover= mCharacter::vectorMove(deltaTime, RIGHTDOWN);
		m_SeeDir = RIGHTDOWN;
		/*toServer.direction = RIGHTDOWN;
		toServer.seedir = RIGHTDOWN;*/
	}
	else if (m_dest->x < _realVector->x && m_dest->y > _realVector->y){
		vMover = mCharacter::vectorMove(deltaTime, LEFTDOWN);
		m_SeeDir = LEFTDOWN;
		/*toServer.direction = LEFTDOWN;
		toServer.seedir = LEFTDOWN;*/
	}
	else if (m_dest->x > _realVector->x && m_dest->y < _realVector->y){
		vMover= mCharacter::vectorMove(deltaTime, RIGHTUP);
		m_SeeDir = RIGHTUP;
		/*toServer.direction = RIGHTUP;
		toServer.seedir = RIGHTUP;*/
	}
	else if (m_dest->x < _realVector->x){
		vMover = mCharacter::vectorMove(deltaTime, LEFT);
		/*if (m_SeeDir == RIGHTUP){
			m_SeeDir = LEFTUP;
		}
		else if (m_SeeDir == RIGHTDOWN){
			m_SeeDir = LEFTDOWN;
		}*/		
		m_SeeDir = LEFTDOWN;

	/*	toServer.direction = LEFT;
		toServer.seedir = LEFTDOWN;*/
	}
	else if (m_dest->x > _realVector->x){
		vMover = mCharacter::vectorMove(deltaTime, RIGHT);
		/*if (m_SeeDir == LEFTUP){
			m_SeeDir = RIGHTUP;
		}
		else if (m_SeeDir == LEFTDOWN){
			m_SeeDir = RIGHTDOWN;
		}*/
		m_SeeDir = RIGHTDOWN;

		/*toServer.direction = RIGHT;
		toServer.seedir = RIGHTDOWN;*/
	}
	else if (m_dest->y < _realVector->y){
		vMover= mCharacter::vectorMove(deltaTime, UP);
		//toServer.direction = UP;
		
		if (m_SeeDir == LEFTDOWN){
			m_SeeDir = LEFTUP;
			//toServer.seedir = LEFTUP;
		}
		else if (m_SeeDir == RIGHTDOWN){
			m_SeeDir = RIGHTUP;
			//toServer.seedir = RIGHTUP;
		}
	}
	else if (m_dest->y > _realVector->y){
		vMover = mCharacter::vectorMove(deltaTime, DOWN);
		//toServer.direction = DOWN;

		if (m_SeeDir == LEFTUP){
			m_SeeDir = LEFTDOWN;
			//toServer.seedir = LEFTDOWN;
		}
		else if (m_SeeDir == RIGHTUP){
			m_SeeDir = RIGHTDOWN;
			//toServer.seedir = RIGHTDOWN;
		}
	}

	*_realVector = *_realVector + vMover;
	*_drawVector = *_drawVector + vMover;
	
	// 플롯 벡터 움직임 오차범위
	// 플롯이고, 또한 벡터 무빙으로 움직이기 때문에 어느정도의 오차는 발생한다.
	// 오차범위내에 들어가면 도착한걸로 결정
	float tolerance = 2.0f;
	if (abs(_realVector->x - m_dest->x) < tolerance){
		m_dest->x = _realVector->x;
	}
	if (abs(_realVector->y - m_dest->y) < tolerance){
		m_dest->y = _realVector->y;
	}	

	/*toServer.msgtype = ::MESSAGETYPE_ID::MOB_ID_UPDATE;
	toServer.id = ::netWorkCharManager::GetInstance().getMyId();
	toServer.mob_uniq_id = getMobID();
	toServer.mob_type = getMonsterType();
	toServer.state = ONMOVE;
	toServer.px = getDrawPos()->x;
	toServer.py = getDrawPos()->y;
	toServer.speed = getMoveSpeed();
	
	::CharCIPMessage::GetInstance().SendMessagePort(toServer);*/
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

	// todo: 이동 불가타일 도착 불가하게 만들기
	if (m_pTileMap->getMapinfo(static_cast<int>(destTilePos.x), static_cast<int>(destTilePos.y))!=0){
		return;
	}

	destTilePos.x = destTilePos.x * 45.0f;
	destTilePos.y = destTilePos.y * 45.0f;

	destTilePos = m_pTileMap->twoDtoISO(destTilePos);
	m_dest->x = destTilePos.x;
	m_dest->y = destTilePos.y;
}

void mMonster::setMonsterType(int in){
	m_nMonsterType = in; 
	/*if (m_nMonsterType != 0){
		m_fcurAggroLevel = m_fMaxAggroLevel;
	}*/
}