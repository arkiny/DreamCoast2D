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
//			= m_spriteAtlas->getCoordinateFromPivot(*_drawVector);
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

/// Iso ��ǥ��� ������
//BOOL wTileMap::isInISOTile(VECTOR2D cur, VECTOR2D tilepos){
//	float x = tilepos.y * _RectTileWidth;
//	float y = tilepos.x * _RectTileHeight;
//	VECTOR2D pt = twoDtoISO(VECTOR2D(x, y));
//	float m = 0.5f;
//		
//	::D2D1_RECT_F tileArea = {
//		pt.x - _RectTileWidth,
//		pt.y - (_RectTileHeight / 2),
//		pt.x + _RectTileWidth,
//		pt.y + (_RectTileHeight / 2) };
//
//	POINTFLOAT left = { tileArea.left, (tileArea.top + ((tileArea.bottom - tileArea.top) / 2)) };
//	POINTFLOAT top = { (tileArea.left + ((tileArea.right - tileArea.left) / 2)), tileArea.top };
//	POINTFLOAT right = { tileArea.right, (tileArea.top + ((tileArea.bottom - tileArea.top) / 2)) };
//	POINTFLOAT bottom = { (tileArea.left + ((tileArea.right - tileArea.left) / 2)), tileArea.bottom };
//
//	float l1 = left.y + (m*left.x); // ���� �� ������
//	float l2 = top.y + (-m*top.x); // ������ �� ������
//	float l3 = right.y + (m*right.x); // ���� �Ʒ� ������
//	float l4 = bottom.y + (-m*bottom.x); // ������ �Ʒ� ������
//
//	float r1 = -m * cur.x - cur.y + l1;
//	float r2 = m * cur.x - cur.y + l2;
//	float r3 = -m * cur.x - cur.y + l3;
//	float r4 = m * cur.x - cur.y + l4;
//
//	if (r1 <= 0.0f && r2 <= 0.0f && r3 >= 0.0f && r4 >= 0.0f){
//		return true;
//	}
//	else {
//		return false;
//	}
//}


/*float tileY = ((in.y * 2.0f) - (_RectTileWidth*_vertical) + in.x) / 2.0f;
float tileX = in.x - tileY;
tileY = roundf(tileY / _RectTileHeight);
tileX = roundf(tileX / _RectTileHeight);
temp.x = tileX;
temp.y = tileY;*/

/*var tileY = ((mouseY * 2) - ((gridSize*tileWidth) / 2) + mouseX) / 2;
var tileX = mouseX - tileY;
tileY = Math.round(tileY / tileHeight);
tileX = Math.round(tileX / tileHeight);*/


/// �ؽ�Ʈ ���
//wchar_t* wszText_ = L"Hello World using DirectWrite!";
//UINT32 cTextLength_ = (UINT32)wcslen(wszText_);

//D2D1_RECT_F layoutRect = D2D1::RectF(
//	100,
//	300,
//	800,
//	400
//	);

//renderer.GetRenderTarget()->DrawTextW(
//	wszText_,
//	cTextLength_,
//	renderer.GetTextFormat(),
//	layoutRect,
//	renderer.GetBrush());

/// background
	//if (m_ipD2DBitmapBG != nullptr)
	//{
	//	D2D1_SIZE_U size = renderer.GetRenderTargetSize();
	//	::D2D1_RECT_F dxArea = ::D2D1::RectF(0.0f, 0.0f, static_cast<float>(size.width), static_cast<float>(size.height));
	//	::D2D1_RECT_F srcArea = ::D2D1::RectF(0.0f, 0.0f, 1024.0f, 768.0f);

	//	renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmapBG, dxArea, 1.0f,
	//		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
	//		srcArea);
//}

/// static map info
//int m_mapinfo[14][14];			// ���� �������� ����Ÿ ����

/// wTileMap ���� uTile�� �̵���
//void wTileMap::hRender(cD2DRenderer& renderer, VECTOR2D tilePos){
//	if (m_ipD2DBitmap != nullptr){
//
//		// Pivot �̹����� �Ѱ�� �ٴ� -> dxArea���� ����
//		::D2D1_RECT_F dxArea
//			= m_spriteAtlas->getCoordinateFromPivotCenter(tilePos);
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
//
//void wTileMap::renderTile(float x, float y, int type, cD2DRenderer& renderer){
//	VECTOR2D tilePos(x, y);
//	// debug
//	switch (type){
//	case 0:
//		m_spriteAtlas->pickSpriteAtlas(0.0f, 0.0f, 90.0f, 45.0f, 0);		
//		break;
//	case 1:
//		m_spriteAtlas->pickSpriteAtlas(100.0f, 0.0f, 90.0f, 45.0f, 0);		
//		break;
//	case 2:
//		m_spriteAtlas->pickSpriteAtlas(200.0f, 0.0f, 90.0f, 62.0f, 0);
//		break;
//	case 3:
//		// offsetY = -((���� - ����Ÿ�ϳ���) / 2)
//		m_spriteAtlas->pickSpriteAtlas(0.0f, 80.0f, 90.0f, 162.0f, 0.0f, -58.5f, 0);
//		break;
//	default:
//		m_spriteAtlas->pickSpriteAtlas(0.0f, 0.0f, 90.0f, 45.0f, 0);
//		break;
//	}
//
//	wTileMap::hRender(renderer, m_Cam->translasteToScreen(&tilePos));
//}


///mplayer->mCharacter
//VECTOR2D mPlayer::vectorMove(float fdeltatime, DIRECTION dir){
//	VECTOR2D vMover = VECTOR2D(0.0f, 0.0f);
//	VECTOR2D vDir = VECTOR2D(0.0f, 0.0f);
//	switch (dir)
//	{
//	case LEFT:
//		vDir = vLeft;
//		break;
//	case RIGHT:
//		vDir = vRight;
//		break;
//	case UP:
//		vDir = vUp;
//		break;
//	case DOWN:
//		vDir = vDown;
//		break;
//	case RIGHTDOWN:
//		// 1:2 isometric�̹Ƿ� ���� �̵��ӵ��� �������� ����
//		vDir = vRight + (vDown/2.0f);
//		break;
//	case LEFTUP:
//		vDir = vLeft + (vUp/2.0f);
//		break;
//	case LEFTDOWN:
//		vDir = vLeft + (vDown/2.0f);
//		break;
//	case RIGHTUP:
//		vDir = vRight + (vUp/2.0f);
//		break;
//	default:
//		break;
//	}
//	
//	vDir.Normalize();
//	vMover = vDir*(100.0f * fdeltatime);
//
//	return vMover;
//}