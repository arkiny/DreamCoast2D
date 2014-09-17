#include "stdafx.h"
#include "cD2DRenderer.h"
#include "mPlayer.h"
#include "coControl.h"
#include "VECTOR2D.h"
#include "uSprite.h"

mPlayer::mPlayer()
{	
	m_ipD2DBitmap = nullptr;
	
	//임시로 중앙에 대기
	_posVector = new VECTOR2D(514.0f, 384.0f);

	m_accumtime = 0.0f;
	m_nframe = 0;

	m_spriteAtlas = new uSprite();
}


mPlayer::~mPlayer()
{
	SafeRelease(m_ipD2DBitmap);

	if (_posVector != NULL){
		delete _posVector;
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
	mPlayer::onMove(fdeltatime);
}

void mPlayer::onRender(cD2DRenderer& renderer){
	
	// 몸
	if (m_ipD2DBitmap != nullptr){
		
		// Pivot 이미지의 한가운데 바닥 -> dxArea에서 지정
		::D2D1_RECT_F dxArea
			= m_spriteAtlas->getCoordinateFromPivot(*_posVector);

		//
		float pickframeX = m_nframe * m_spriteAtlas->getframeWidth();
		::D2D1_RECT_F srcArea 
			= ::D2D1::RectF(
			m_spriteAtlas->getframeX() + pickframeX, 
			m_spriteAtlas->getframeY(),
			m_spriteAtlas->getframeX() + pickframeX + m_spriteAtlas->getframeWidth(),
			m_spriteAtlas->getframeY() + m_spriteAtlas->getframeHeight());
		//

		//D2D1::Matrix3x2F rot = D2D1::Matrix3x2F::Rotation(m_fAngle, D2D1::Point2F(x + 50, y + 50));
		//renderer.GetRenderTarget()->SetTransform(rot);

		renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);

		renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	}
}

// 키를 받아와서 업데이트
void mPlayer::setKeyControl(coControl* in){
	m_pControl = in;
}

// 이동간에 따른 무브무브
void mPlayer::onMove(float fdeltatime){
	VECTOR2D vMover = VECTOR2D(0.0f, 0.0f);
	VECTOR2D vDir = VECTOR2D(0.0f, 0.0f);;

	if (m_pControl->getKeyControlInfo()[VK_RIGHT]){

		vMover = vRight*(100.0f * fdeltatime);
		m_spriteAtlas->pickSpriteAtlas(0.0f, 0.0f, 47.0f, 88.0f);

		m_accumtime += fdeltatime;
		if (m_accumtime > 0.125f){
			m_nframe++;
			m_accumtime = 0.0f;
		}
		if (m_nframe > 6){
			m_nframe = 0;
		}
	}
	else if (m_pControl->getKeyControlInfo()[VK_LEFT]){

		vMover = vLeft*(100.0f * fdeltatime);
		m_spriteAtlas->pickSpriteAtlas(0.0f, 185.0f, 47.0f, 88.0f);

		m_accumtime += fdeltatime;
		if (m_accumtime > 0.125f){
			m_nframe++;
			m_accumtime = 0.0f;
		}
		if (m_nframe > 6){
			m_nframe = 0;
		}
	}
	else if (m_pControl->getKeyControlInfo()[VK_DOWN]){

		vMover = vDown*(100.0f * fdeltatime);
		m_spriteAtlas->pickSpriteAtlas(0.0f, 279.0f, 35.0f, 91.0f);

		m_accumtime += fdeltatime;
		if (m_accumtime > 0.125f){
			m_nframe++;
			m_accumtime = 0.0f;
		}
		if (m_nframe > 6){
			m_nframe = 0;
		}
	}
	else if (m_pControl->getKeyControlInfo()[VK_UP]){

		vMover = vUp*(100.0f * fdeltatime);
		m_spriteAtlas->pickSpriteAtlas(0.0f, 373.0f, 37.0f, 92.0f);

		m_accumtime += fdeltatime;
		if (m_accumtime > 0.125f){
			m_nframe++;
			m_accumtime = 0.0f;
		}
		if (m_nframe > 6){
			m_nframe = 0;
		}
	}
	else {
		m_spriteAtlas->pickSpriteAtlas(0.0f, 279.0f, 35.0f, 91.0f);
		m_nframe = 0;
	}

	*_posVector = *_posVector + vMover;
}
