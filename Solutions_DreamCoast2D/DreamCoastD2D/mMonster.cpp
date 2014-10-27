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

	m_pState = nullptr; // ���� ���´� nullptr�� init

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
	m_pState = nullptr; // ���� ���´� nullptr�� init

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
	// ����� �⺻���� ����������, ��ӹ޾Ƽ� �ٲܼ� �ִ�.
	m_ipD2DBitmap = ::cResourceManager::GetInstance().getPoringBitMap();
	//resource;
	// idle���� ����
	m_pState = new aiStateIdle();
	m_pState->enter(this);	
}

//void mMonster::onInit(cD2DRenderer& renderer){
//	// ����� �⺻���� ����������, ��ӹ޾Ƽ� �ٲܼ� �ִ�.
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
		
		m_spriteAtlas->pickSpriteAtlas(
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,0, 0)->x, 
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,0, 0)->y, 
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,0, 0)->width, 
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,0, 0)->height,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,0, 0)->offsetX, 
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,0, 0)->offsetY, 
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,0, 0)->maxFrame);
		//m_spriteAtlas->pickSpriteAtlas(0.0f, 310.0f, 50.0f, 40.0f, 1);
	} 
	else if (m_SeeDir == LEFTUP || m_SeeDir == RIGHTUP){
		//m_spriteAtlas->pickSpriteAtlas(240.0f, 0.0f, 60.0f, 60.0f, 0.0f, 5.0f, 3);
		m_spriteAtlas->pickSpriteAtlas(
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,0, 1)->x,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,0, 1)->y,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,0, 1)->width,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,0, 1)->height,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,0, 1)->offsetX,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,0, 1)->offsetY,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,0, 1)->maxFrame);
	}
	//mMonster::onHit();	
	
}

void mMonster::onAttack(){
}

void mMonster::onHit(){
	if (m_SeeDir == LEFTDOWN || m_SeeDir == RIGHTDOWN){
		//m_spriteAtlas->pickSpriteAtlas(0.0f, 210.0f, 50.0f, 40.0f, 1);
		m_spriteAtlas->pickSpriteAtlas(
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,4, 0)->x,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,4, 0)->y,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,4, 0)->width,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,4, 0)->height,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,4, 0)->offsetX,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,4, 0)->offsetY,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,4, 0)->maxFrame);
		//m_spriteAtlas->pickSpriteAtlas(10.0f, 210.0f, 40.0f, 40.0f, 1);
	}
	else if (m_SeeDir == LEFTUP || m_SeeDir == RIGHTUP){
		//m_spriteAtlas->pickSpriteAtlas(0.0f, 310.0f, 50.0f, 40.0f, 1);
		m_spriteAtlas->pickSpriteAtlas(
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,4, 1)->x,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,4, 1)->y,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,4, 1)->width,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,4, 1)->height,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,4, 1)->offsetX,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,4, 1)->offsetY,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,4, 1)->maxFrame);
		//m_spriteAtlas->pickSpriteAtlas(240.0f, 0.0f, 60.0f, 60.0f, 1);
	}
}

void mMonster::onDeath(){
	if (m_SeeDir == LEFTDOWN || m_SeeDir == RIGHTDOWN){
		//m_spriteAtlas->pickSpriteAtlas(0.0f, 210.0f, 50.0f, 40.0f, 1);
		m_spriteAtlas->pickSpriteAtlas(
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,5, 0)->x,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,5, 0)->y,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,5, 0)->width,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,5, 0)->height,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,5, 0)->offsetX,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,5, 0)->offsetY,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,5, 0)->maxFrame);
		//m_spriteAtlas->pickSpriteAtlas(10.0f, 210.0f, 40.0f, 40.0f, 1);
	}
	else if (m_SeeDir == LEFTUP || m_SeeDir == RIGHTUP){
		//m_spriteAtlas->pickSpriteAtlas(0.0f, 310.0f, 50.0f, 40.0f, 1);
		m_spriteAtlas->pickSpriteAtlas(
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,5, 1)->x,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,5, 1)->y,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,5, 1)->width,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,5, 1)->height,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,5, 1)->offsetX,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,5, 1)->offsetY,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,5, 1)->maxFrame);
		//m_spriteAtlas->pickSpriteAtlas(240.0f, 0.0f, 60.0f, 60.0f, 1);
	}
}

void mMonster::onMove(){
	if (m_SeeDir == LEFTDOWN || m_SeeDir == RIGHTDOWN){
		//m_spriteAtlas->pickSpriteAtlas(0.0f, 68.0f, 53.0f, 40.0f, 7);
		m_spriteAtlas->pickSpriteAtlas(
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 0)->x,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 0)->y,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 0)->width,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 0)->height,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 0)->offsetX,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 0)->offsetY,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 0)->maxFrame);
	}
	else if (m_SeeDir == LEFTUP || m_SeeDir == RIGHTUP){
		m_spriteAtlas->pickSpriteAtlas(
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 1)->x,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 1)->y,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 1)->width,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 1)->height,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 1)->offsetX,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 1)->offsetY,
			cResourceManager::GetInstance().getMonsterSpriteInfo(0,1, 1)->maxFrame);
	}
}

void mMonster::onRender(){
	if (m_ipD2DBitmap != nullptr){
		//
		VECTOR2D cpos = m_Cam->translasteToScreen(_drawVector);
		//
		// Pivot �̹����� �Ѱ�� �ٴ� -> dxArea���� ����
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
			::cD2DRenderer::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Scale(
				D2D1::Size(-1.0f, 1.0f),
				D2D1::Point2F(cpos.x, cpos.y)));
			
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
		//	/// �ؽ�Ʈ ���
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


		//ȸ��� �ʿ��� �κ�
		//renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());

		////debug ��
		//::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(dxArea, ::cD2DRenderer::GetInstance().GetBlackBrush());

		//::D2D1_RECT_F pivotArea;
		//pivotArea.top = cpos.y - 2.0f;
		//pivotArea.bottom = cpos.y + 2.0f;
		//pivotArea.left = cpos.x - 2.0f;
		//pivotArea.right = cpos.x + 2.0f;
		//::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(pivotArea, ::cD2DRenderer::GetInstance().GetBlackBrush());

		////renderer.GetRenderTarget()->DrawRectangle(dxArea, renderer.GetBlackBrush());
		////pivotArea;
		//cpos = m_Cam->translasteToScreen(_realVector);
		//pivotArea.top = cpos.y - 2.0f;
		//pivotArea.bottom = cpos.y + 2.0f;
		//pivotArea.left = cpos.x - 2.0f;
		//pivotArea.right = cpos.x + 2.0f;
		//::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(pivotArea, ::cD2DRenderer::GetInstance().GetBlackBrush());
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
// todo: �����¿� ������ ���ٰ� (�˰����� �׷��� ó��)
void mMonster::moveToDest(float deltaTime){
	VECTOR2D vMover;
	if (m_dest->x < _realVector->x && m_dest->y < _realVector->y){
		vMover= mCharacter::vectorMove(deltaTime, LEFTUP);
		m_SeeDir = LEFTUP;
	}
	else if (m_dest->x > _realVector->x && m_dest->y > _realVector->y){
		vMover= mCharacter::vectorMove(deltaTime, RIGHTDOWN);
		m_SeeDir = RIGHTDOWN;
	}
	else if (m_dest->x < _realVector->x && m_dest->y > _realVector->y){
		vMover = mCharacter::vectorMove(deltaTime, LEFTDOWN);
		m_SeeDir = LEFTDOWN;
	}
	else if (m_dest->x > _realVector->x && m_dest->y < _realVector->y){
		vMover= mCharacter::vectorMove(deltaTime, RIGHTUP);
		m_SeeDir = RIGHTUP;
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
	}
	else if (m_dest->y < _realVector->y){
		vMover= mCharacter::vectorMove(deltaTime, UP);
		if (m_SeeDir == LEFTDOWN){
			m_SeeDir = LEFTUP;
		}
		else if (m_SeeDir == RIGHTDOWN){
			m_SeeDir = RIGHTUP;
		}
	}
	else if (m_dest->y > _realVector->y){
		vMover = mCharacter::vectorMove(deltaTime, DOWN);
		if (m_SeeDir == LEFTUP){
			m_SeeDir = LEFTDOWN;
		}
		else if (m_SeeDir == RIGHTUP){
			m_SeeDir = RIGHTDOWN;
		}
	}

	*_realVector = *_realVector + vMover;
	*_drawVector = *_drawVector + vMover;
	
	// �÷� ���� ������ ��������
	// �÷��̰�, ���� ���� �������� �����̱� ������ ��������� ������ �߻��Ѵ�.
	// ������������ ���� �����Ѱɷ� ����
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

	// �ܰ� �浹 ó��, ���� ���� ���갡 �ܰ����� ������� �ҽ�
	// �ƿ� �ش� ���μ��� ��ü�� ����Ѵ�.
	if (destTilePos.x >= m_pTileMap->getMapLimit().x || 
		destTilePos.y >= m_pTileMap->getMapLimit().y ||
		destTilePos.x <= 0 || destTilePos.y <= 0){
		return;
	}

	// todo: �̵� �Ұ�Ÿ�� ���� �Ұ��ϰ� �����
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