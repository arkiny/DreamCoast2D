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
//	// render �� ����
//	::D2D1_RECT_F dxArea = ::D2D1::RectF(x, y + 100.0f, x + 100.0f, y + 200.0f);
//	// sprite�� ����
//	::D2D1_RECT_F srcArea = ::D2D1::RectF(0.0f, 0.0f, 512.0f, 512.0f);

//	renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmapFlip, dxArea, 1.0f,
//		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
//		srcArea);

//	renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
//}

//// �׳� �̵�
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



// �Ӹ�
//if (m_ipD2DBitmapHeadFlipped != nullptr){
//	// pivot����� �̿��Ͽ� �߽��� ��� �����ؾ��ϳ�?
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



// ��
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



// �÷��̾��� �����ǰ� �Ǻ��� ��ġ�ϰ� �����Ͽ� ����
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

//������ �ҽ������
//float pickframeX = m_spriteAtlas->getCurrentFrame() * m_spriteAtlas->getframeWidth();
/*::D2D1::RectF(
m_spriteAtlas->getframeX() + pickframeX,
m_spriteAtlas->getframeY(),
m_spriteAtlas->getframeX() + pickframeX + m_spriteAtlas->getframeWidth(),
m_spriteAtlas->getframeY() + m_spriteAtlas->getframeHeight());*/
//

//D2D1::Matrix3x2F rot = D2D1::Matrix3x2F::Rotation(m_fAngle, D2D1::Point2F(x + 50, y + 50));
//renderer.GetRenderTarget()->SetTransform(rot);

// Sprite Atlas Ŭ������ ���߿� �и�(?)
//float m_frameWidth;
//float m_frameHeight;
//float m_frameX;
//float m_frameY;
//void pickSpriteAtlas(float x, float y, float width, float height);

// ���� ���� Sprite Atlas�� �μ��� �޾Ƽ� �Ǻ�ȭ�� ��ǥ�� ����
//D2D1_RECT_F getCoordinateFromPivot(VECTOR2D& pos);

/// Ŭ���� �̵� �ִϸ��̼� ó���� ��� �ڵ�
/// Ŭ����ȭ �Ǿ���
//float m_accumtime;
//int m_nframe;
//void nextFrame(float fdeltatime);

//m_accumtime = 0.0f;
//m_nframe = 0;

//void mPlayer::nextFrame(float fdeltatime){
//	m_accumtime += fdeltatime;
//	if (m_accumtime > 0.125f){
//		m_nframe++;
//		m_accumtime = 0.0f;
//	}
//	if (m_nframe > 6){
//		m_nframe = 0;
//	}
//}

/// mplayer ����
//void mPlayer::onRender(cD2DRenderer& renderer){	
//	// �÷��̾� ����
//	if (m_ipD2DBitmap != nullptr){
//		
//		// Pivot �̹����� �Ѱ�� �ٴ� -> dxArea���� ����
//		::D2D1_RECT_F dxArea
//			= m_spriteAtlas->getCoordinateFromPivot(*_posVector);
//
//		//	
//		::D2D1_RECT_F srcArea
//			= m_spriteAtlas->getSrcFrameFromSprite();
//
//		renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, 1.0f,
//			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
//			srcArea);
//		
//		//ȸ��� �ʿ��� �κ�
//		//renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
//	}
//}