#include "stdafx.h"
#include "cD2DRenderer.h"
#include "mIObject.h"
#include "VECTOR2D.h"
#include "uSprite.h"

mIObject::~mIObject()
{
}

void mIObject::onRender(){
	if (m_ipD2DBitmap != nullptr){

		// Pivot �̹����� �Ѱ�� �ٴ� -> dxArea���� ����
		::D2D1_RECT_F dxArea
			= m_spriteAtlas->getCoordinateFromPivot(*_drawVector);

		//	
		::D2D1_RECT_F srcArea
			= m_spriteAtlas->getSrcFrameFromSprite();

		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);

		//ȸ��� �ʿ��� �κ�
		//renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());

		//debug ��
		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(dxArea, ::cD2DRenderer::GetInstance().GetBlackBrush());
		::D2D1_RECT_F pivotArea;
		pivotArea.top = _drawVector->y - 2.0f;
		pivotArea.bottom = _drawVector->y + 2.0f;
		pivotArea.left = _drawVector->x - 2.0f;
		pivotArea.right = _drawVector->x + 2.0f;
		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(pivotArea, ::cD2DRenderer::GetInstance().GetBlackBrush());

		//renderer.GetRenderTarget()->DrawRectangle(dxArea, renderer.GetBlackBrush());
		pivotArea;
		pivotArea.top = _realVector->y - 2.0f;
		pivotArea.bottom = _realVector->y + 2.0f;
		pivotArea.left = _realVector->x - 2.0f;
		pivotArea.right = _realVector->x + 2.0f;
		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(pivotArea, ::cD2DRenderer::GetInstance().GetBlackBrush());
	}	
}

void mIObject::onRender(bool alpha){
	if (m_ipD2DBitmap != nullptr){

		// Pivot �̹����� �Ѱ�� �ٴ� -> dxArea���� ����
		::D2D1_RECT_F dxArea
			= m_spriteAtlas->getCoordinateFromPivot(*_drawVector);

		//	
		::D2D1_RECT_F srcArea
			= m_spriteAtlas->getSrcFrameFromSprite();

		if (alpha){
			::cD2DRenderer::GetInstance().GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, 0.4f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
		//ȸ��� �ʿ��� �κ�
		//renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());

		//debug ��
		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(dxArea, ::cD2DRenderer::GetInstance().GetBlackBrush());
		::D2D1_RECT_F pivotArea;
		pivotArea.top = _drawVector->y - 2.0f;
		pivotArea.bottom = _drawVector->y + 2.0f;
		pivotArea.left = _drawVector->x - 2.0f;
		pivotArea.right = _drawVector->x + 2.0f;
		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(pivotArea, ::cD2DRenderer::GetInstance().GetBlackBrush());
	}
}

void mIObject::setRealPos(float x, float y){
	_realVector->x = x;
	_realVector->y = y;
}

void mIObject::setDrawPos(float x, float y){
	_drawVector->x = x;
	_drawVector->y = y;
}

void mIObject::setTileMap(wTileMap* in){
	m_pTileMap = in;
}

VECTOR2D mIObject::vectorMove(float fdeltatime, DIRECTION dir){
	VECTOR2D vMover = VECTOR2D(0.0f, 0.0f);
	VECTOR2D vDir = VECTOR2D(0.0f, 0.0f);
	switch (dir)
	{
	case LEFT:
		vDir = vLeft;
		break;
	case RIGHT:
		vDir = vRight;
		break;
	case UP:
		vDir = vUp;
		break;
	case DOWN:
		vDir = vDown;
		break;
	case RIGHTDOWN:
		// 1:2 isometric�̹Ƿ� ���� �̵��ӵ��� �������� ����
		vDir = vRight + (vDown / 2.0f);
		break;
	case LEFTUP:
		vDir = vLeft + (vUp / 2.0f);
		break;
	case LEFTDOWN:
		vDir = vLeft + (vDown / 2.0f);
		break;
	case RIGHTUP:
		vDir = vRight + (vUp / 2.0f);
		break;
	case NOMOVE:
		break;
	default:
		break;
	}

	// todo: ���� 100.0f�� �� object�� �̼����� ����
	if (dir != NOMOVE){
		vDir.Normalize();
	}
	vMover = vDir*(m_moveSpeed * fdeltatime);

	return vMover;
}

void mIObject::getHit(float dmg){
	mIObject::setHealth(this->getHealth() - dmg);
}