#include "stdafx.h"
#include "cD2DRenderer.h"
#include "mPlayer.h"
#include "coControl.h"

mPlayer::mPlayer()
{	
	m_ipD2DBitmap = nullptr;
	//임시로 중앙에 대기
	//RECT clientRect;
	//::GetClientRect(hWnd, &clientRect);
	_pos = { 514.0f, 384.0f };
	m_accumtime = 0.0f;
	m_nframe = 0;
	m_frameWidth = 0.0f;
	m_frameHeight=0.0f;

	// pivot 연구용
	playerCollisionBox = {};
	m_playerPivotX = 0.0f;
	m_playerPivotY = 0.0f;
}


mPlayer::~mPlayer()
{
	SafeRelease(m_ipD2DBitmap);
}

void mPlayer::onInit(cD2DRenderer& renderer){
	HWND hWnd = renderer.GetHwnd();
	m_ipD2DBitmap = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/sprites.png", NULL);
}

void mPlayer::onUpdate(float fdeltatime){

	if (m_pControl->getKeyControlInfo()[VK_RIGHT]){
		_pos.x = _pos.x + (100.0f * fdeltatime);
		mPlayer::pickSpriteAtlas(0.0f, 0.0f, 47.0f, 88.0f);

		m_accumtime += fdeltatime;
		if (m_accumtime > 0.125f){
			m_nframe++;
			m_accumtime = 0.0f;
		}
		if (m_nframe > 6){
			m_nframe = 0;
		}		
	} else if (m_pControl->getKeyControlInfo()[VK_LEFT]){
		// 이동속도가 좌우하고 차이가 난다. 왜?!
		_pos.x = _pos.x + (-100.0f * fdeltatime);
		mPlayer::pickSpriteAtlas(0.0f, 185.0f, 47.0f, 88.0f);

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
		// 이동속도가 좌우하고 차이가 난다. 왜?!
		_pos.y = _pos.y + (100.0f * fdeltatime);
		mPlayer::pickSpriteAtlas(0.0f, 279.0f, 35.0f, 91.0f);
		m_frameY = 279.0f;
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
		// 이동속도가 좌우하고 차이가 난다. 왜?!
		_pos.y = _pos.y + (-100.0f * fdeltatime);
		mPlayer::pickSpriteAtlas(0.0f, 373.0f, 37.0f, 92.0f);

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
		mPlayer::pickSpriteAtlas(0.0f, 279.0f, 35.0f, 91.0f);
		m_nframe = 0;
		//mPlayer::pickSpriteAtlas(0.0f, 90.0f, 64.0f, 94.0f);
		//m_accumtime += fdeltatime;
		//if (m_accumtime > 0.125f){
		//	m_nframe++;
		//	m_accumtime = 0.0f;
		//}
		//if (m_nframe > 4){
		//	m_nframe = 0;
		//}
	}
}

void mPlayer::pickSpriteAtlas(float x, float y, float width, float height){
	m_frameWidth = width;
	m_frameHeight = height;
	m_frameX = x;
	m_frameY = y;
}

void mPlayer::onRender(cD2DRenderer& renderer){
	// 몸
	if (m_ipD2DBitmap != nullptr){
		//
		::D2D1_RECT_F dxArea 
			= ::D2D1::RectF(_pos.x, _pos.y, _pos.x + m_frameWidth, _pos.y + m_frameHeight);
		//
		float pickframeX = m_nframe * m_frameWidth;
		::D2D1_RECT_F srcArea 
			= ::D2D1::RectF(
			m_frameX + pickframeX, 
			m_frameY, 
			m_frameX + pickframeX + m_frameWidth,
			m_frameY+m_frameHeight);
		//

		//D2D1::Matrix3x2F rot = D2D1::Matrix3x2F::Rotation(m_fAngle, D2D1::Point2F(x + 50, y + 50));
		//renderer.GetRenderTarget()->SetTransform(rot);

		renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);

		renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	}
}

void mPlayer::setKeyControl(coControl* in){
	m_pControl = in;
}