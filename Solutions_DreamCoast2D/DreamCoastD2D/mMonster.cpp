#include "stdafx.h"
#include "mMonster.h"
#include "VECTOR2D.h"
#include "uSprite.h"
#include "cD2DRenderer.h"
#include "aiState.h"
#include "uCamera.h"

mMonster::mMonster()
{
	m_ipD2DBitmap = nullptr;
	_realVector = new VECTOR2D(200.0f, 300.0f);
	_drawVector = new VECTOR2D(_realVector->x, _realVector->y + 15.0f);
	m_spriteAtlas = new uSprite();

	m_pState = nullptr; // 현재 상태는 nullptr로 init

	m_SeeDir = RIGHTDOWN;
	m_State = ONMOVE;

	m_MAXHP = 1000.0f;
	m_HP = 1000.0f;
}

mMonster::mMonster(float x, float y){
	m_ipD2DBitmap = nullptr;
	_realVector = new VECTOR2D(x, y);
	_drawVector = new VECTOR2D(_realVector->x, _realVector->y + 15.0f);
	m_spriteAtlas = new uSprite();
	m_pState = nullptr; // 현재 상태는 nullptr로 init

	m_SeeDir = RIGHTDOWN;
	m_State = ONMOVE;
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
	if (m_SeeDir == LEFTDOWN){
		m_spriteAtlas->pickSpriteAtlas(0.0f, 0.0f, 60.0f, 60.0f, 3);
	} 
	else if (m_SeeDir == LEFTUP){
		m_spriteAtlas->pickSpriteAtlas(240.0f, 0.0f, 60.0f, 60.0f, 3);
	}
	else if (m_SeeDir == RIGHTUP){
		m_spriteAtlas->pickSpriteAtlas(240.0f, 0.0f, 60.0f, 60.0f, 3);
	}
	else if (m_SeeDir == RIGHTDOWN){
		m_spriteAtlas->pickSpriteAtlas(0.0f, 0.0f, 60.0f, 60.0f, 3);
	}
}

void mMonster::onAttack(){
}

void mMonster::onHit(){
}

void mMonster::onDeath(){

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
			renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
		else if (m_SeeDir == RIGHTDOWN || m_SeeDir == RIGHTUP) {
			renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Scale(
				D2D1::Size(-1.0f, 1.0f),
				D2D1::Point2F(cpos.x, cpos.y)));
			
			renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, 1.0f,
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