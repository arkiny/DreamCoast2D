#include "stdafx.h"
//// rotation... then flip?
//if (m_ipD2DBitmap != nullptr)
//{
//	::D2D1_RECT_F dxArea = ::D2D1::RectF(x, y, x + 100.0f, y + 100.0f);
//	::D2D1_RECT_F srcArea = ::D2D1::RectF(0.0f, 0.0f, 512.0f, 512.0f);

//	D2D1::Matrix3x2F rot = D2D1::Matrix3x2F::Rotation(m_fAngle, D2D1::Point2F(x + 50, y + 50));
//	renderer.GetRenderTarget()->SetTransform(rot);

//	renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, m_fAlpha,
//		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
//		srcArea);

//	renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
//}

//// flipped
//if (m_ipD2DBitmapFlip != nullptr)
//{
//	// render 할 구역
//	::D2D1_RECT_F dxArea = ::D2D1::RectF(x, y + 100.0f, x + 100.0f, y + 200.0f);
//	// sprite의 구역
//	::D2D1_RECT_F srcArea = ::D2D1::RectF(0.0f, 0.0f, 512.0f, 512.0f);

//	renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmapFlip, dxArea, 1.0f,
//		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
//		srcArea);

//	renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
//}

//// 그냥 이동
//if (m_ipD2DBitmap != nullptr)
//{
//	::D2D1_RECT_F dxArea = ::D2D1::RectF(x, y + 200.0f, x + 100.0f, y + 300.0f);
//	::D2D1_RECT_F srcArea = ::D2D1::RectF(0.0f, 0.0f, 512.0f, 512.0f);

//	//D2D1::Matrix3x2F rot = D2D1::Matrix3x2F::Rotation(m_fAngle, D2D1::Point2F(x + 50, y + 50));
//	//renderer.GetRenderTarget()->SetTransform(rot);

//	renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, 1.0f,
//		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
//		srcArea);

//	renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
//}



// 머리
//if (m_ipD2DBitmapHeadFlipped != nullptr){
//	// pivot기술을 이용하여 중심을 잡고 실행해야하나?
//	::D2D1_RECT_F dxArea = ::D2D1::RectF(x + 10.0f, y+2, x + 27.0f + 9.0f, y + 30.0f);
//	//
//	float pickframeX = 12 * 28.0f;		
//	::D2D1_RECT_F srcArea = ::D2D1::RectF(0.0f + pickframeX, 0.0f, 28.0f + pickframeX, 30.0f);
//	//

//	//D2D1::Matrix3x2F rot = D2D1::Matrix3x2F::Rotation(m_fAngle, D2D1::Point2F(x + 50, y + 50));
//	//renderer.GetRenderTarget()->SetTransform(rot);

//	renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmapHeadFlipped, dxArea, 1.0f,
//		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
//		srcArea);

//	renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
//}



// 몸
//if (m_ipD2DBitmap != nullptr){
//	//
//	::D2D1_RECT_F dxArea
//		= ::D2D1::RectF(_posX, _posY, _posX + m_frameWidth, _posY + m_frameHeight);
//	//
//	float pickframeX = m_nframe * m_frameWidth;
//	::D2D1_RECT_F srcArea
//		= ::D2D1::RectF(
//		m_frameX + pickframeX,
//		m_frameY,
//		m_frameX + pickframeX + m_frameWidth,
//		m_frameY + m_frameHeight);
//	//

//	//D2D1::Matrix3x2F rot = D2D1::Matrix3x2F::Rotation(m_fAngle, D2D1::Point2F(x + 50, y + 50));
//	//renderer.GetRenderTarget()->SetTransform(rot);

//	renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, 1.0f,
//		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
//		srcArea);

//	renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
//}


//RECT clientRect;
//::GetClientRect(hWnd, &clientRect);
// Position init
/*_posX = 514.0f;
_posY = 384.0f;*/



// 플레이어의 포지션과 피봇이 일치하게 조정하여 리턴
//D2D1_RECT_F mPlayer::getCoordinateFromPivot(VECTOR2D& pos){
//	::D2D1_RECT_F ret
//		= ::D2D1::RectF(
//		pos.x - (m_frameWidth / 2.0f),
//		pos.y - (m_frameHeight),
//		(pos.x - (m_frameWidth / 2.0f)) + m_frameWidth,
//		(pos.y - (m_frameHeight)) + m_frameHeight);
//	return ret;
//}


//mPlayer::pickSpriteAtlas(0.0f, 90.0f, 64.0f, 94.0f);
//m_accumtime += fdeltatime;
//if (m_accumtime > 0.125f){
//	m_nframe++;
//	m_accumtime = 0.0f;
//}
//if (m_nframe > 4){
//	m_nframe = 0;
//}


//mPlayer::pickSpriteAtlas(0.0f, 279.0f, 35.0f, 91.0f);