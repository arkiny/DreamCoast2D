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