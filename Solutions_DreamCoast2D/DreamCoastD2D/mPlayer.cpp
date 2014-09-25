#include "stdafx.h"
#include "cD2DRenderer.h"
#include "mPlayer.h"
#include "coControl.h"
#include "VECTOR2D.h"
#include "uSprite.h"
#include "wTileMap.h"
#include "uCamera.h"
#include "uTile.h"

mPlayer::mPlayer()
{	
	m_ipD2DBitmap = nullptr;
	m_Cam = nullptr;
	//todo: �ӽ÷� �߾ӿ� ���, ���� �������� ���� ������ ���� ����	
	_realVector = new VECTOR2D(514.0f, 384.0f);
	_drawVector = new VECTOR2D(_realVector->x, _realVector->y + 15.0f);
	m_spriteAtlas = new uSprite();
	m_SeeDir = RIGHTDOWN;
	m_State = ONMOVE;

	m_MAXHP = 2100.0f;
	m_MAXMP = 200.0f;
	m_HP = 2100.0f;
	m_MP = 200.0f;
}


mPlayer::~mPlayer()
{
	SafeRelease(m_ipD2DBitmap);
	if (m_Cam != NULL){
		delete m_Cam;
	}
	if (_drawVector != NULL){
		delete _drawVector;
	}
	if (m_spriteAtlas != NULL){
		delete m_spriteAtlas;
	}
}

void mPlayer::onInit(cD2DRenderer& renderer){
	HWND hWnd = renderer.GetHwnd();
	m_ipD2DBitmap = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/sprites.png", NULL);
	m_Cam = new uCamera(1028.0, 768.0f, this->getRealPos());
}

void mPlayer::onUpdate(float fdeltatime){	
	// ����� primitive�� ����� �������� �̿��� statecontroller, 
	// ���� �ð��� ������ statemachine���� ��ü
	if (m_State == ONHIT){
		// ���� �켱������ ���� �� �ǰ� ���� �׼�, ���� Ÿ�ӵ� �־���ϰ�...
		// �ǰ� �����ÿ��� ��� ��Ʈ�� �Ұ�...
		// ���� �������̳� ��ų�� ���� �ǰ� ������ ���� ����
		// TODO : �ϴ��� �ƹ�ó���� ���Ѵ�.
		//(�ǰݽ� wTileMap���� callback���� getHit() �Լ� ��)
		// �Ŀ� IDLE�� ���� ����... �ϴ� ���⼭ �������� ���� ���
		// ONMOVE���� ó�������Ƿ� ONMOVE�� ó��
		m_State = ONMOVE;
	}
	else if (m_pControl->getKeyControlInfo()[0x5A]){
		if (m_State == ONATTACK){
			mPlayer::onAttack(fdeltatime);
		}
		else {
			m_State = ONATTACK;
			m_attackaccumtime = 0.0f;
			m_spriteAtlas->setCurrentFrame(0);			
		}
	}
	else if (m_State == ONATTACK){
		mPlayer::onAttack(fdeltatime);
	}
	else if (m_State == ONMOVE){
		m_attackaccumtime = 0.0f;
		mPlayer::onMove(fdeltatime);
	}
}

// �ǰ� �� ó�� (ü�°���)
void mPlayer::getHit(float dmg){
	mIObject::getHit(dmg);
	if (this->getHealth() >= 0.0f){
		m_State = ONHIT;
	}
}

// todo: �������� ������ �ʿ���
void mPlayer::onAttack(float fdeltatime){
	// fdeltatime�� �޾Ƽ� ���� �ð��� �����Ͽ��� ��� attackó��
	m_attackaccumtime += fdeltatime;

	//bool attacktrigger = false;
	VECTOR2D currentTile = m_pTileMap->getTileCoordinates(*_realVector);
	float fx, fy;

	if (m_attackaccumtime > FRAMERATE * 2.0f){
		//attacktrigger = true;
		m_attackaccumtime = 0.0f;
		if (m_SeeDir == LEFTDOWN){
			fx = currentTile.x + 1.0f;
			fy = currentTile.y;
		}
		else if (m_SeeDir == LEFTUP){
			fx = currentTile.x;
			fy = currentTile.y - 1.0f;
		}
		else if (m_SeeDir == RIGHTDOWN){
			fx = currentTile.x;
			fy = currentTile.y + 1.0f;
		}
		else if (m_SeeDir == RIGHTUP){
			fx = currentTile.x - 1.0f;;
			fy = currentTile.y;
		}
		else {}
		// ���� Ÿ�ϳ��� ���� �������� �����Ƿ�...
		// ���� �� �ڸ����� Ÿ�� onHIT�迭�� ����. 
		m_pTileMap->getTile(currentTile.x, currentTile.y)->onHit(10.0f);
		m_pTileMap->getTile(fx, fy)->onHit(10.0f);
	}

	if (m_spriteAtlas->getCurrentFrame() == 7){
		m_spriteAtlas->setCurrentFrame(0);
		m_State = ONMOVE;
		return;
	}

	// ������ ó���� ���� �����ӿ� Ʈ���� �ǵ��� -> ���� �ð��� Ʈ���ŵǵ�����
	if (m_SeeDir == LEFTDOWN){
		m_spriteAtlas->pickSpriteAtlas(0.0f, 600.0f, 121.0f, 98.0f, 19.5f, 0.0f, 7);
	}
	else if (m_SeeDir == LEFTUP){
		m_spriteAtlas->pickSpriteAtlas(0.0f, 700.0f, 103.0f, 84.0f, 7);
	}
	else if (m_SeeDir == RIGHTDOWN){
		m_spriteAtlas->pickSpriteAtlas(0.0f, 800.0f, 121.0f, 98.0f, -19.5f, 0.0f, 7);
	}
	else if (m_SeeDir == RIGHTUP){
		m_spriteAtlas->pickSpriteAtlas(0.0f, 900.0f, 103.0f, 84.0f, 7);
	}
	//leftdown (0.0f, 600.0f, 121.0f, 98.0f, 7)
	//leftup (0.0f, 700.0f, 103.0f, 84.0f, 7)
	//rightdown (0.0f, 800.0f, 121.0f, 98.0f, 7)
	//rightup (0.0f, 900.0f, 103.0f, 84.0f, 7)

	m_spriteAtlas->nextFrame(fdeltatime*m_attackSpeed);
}

// Ű�� �޾ƿͼ� ������Ʈ(connector)-> todo: ���ڸ� const�� �ٲ㼭 �׻� ����
void mPlayer::setKeyControl(coControl* in){
	m_pControl = in;
}


// �̵����� ���� ���깫��
// �Ƹ� onMove ���� onControl
void mPlayer::onMove(float fdeltatime){
	VECTOR2D vMover = VECTOR2D(0.0f, 0.0f);

	// sprite data
	//leftdown (360.0f, 0.0f,39.0f, 94.0f, 6)
	//leftup (360.0f, 100.0f, 44.0f, 95.0f, 6)
	//rightdown (360.0f, 200.0f, 39.0f, 94.0f, 6)
	//rightup (360.0f, 300.0f, 44.0f, 95.0f, 6)
	// idle left up
	//(360.0f, 400.0f, 42.0f, 89.0f, 4)
	// idle right up
	//(360.0f, 500.0f, 42.0f, 89.0f, 4)
	// idle left down
	//(0.0f, 500.0f, 64.0f, 92.0f, 4)

	if (m_pControl->getKeyControlInfo()[VK_LEFT] &&
		m_pControl->getKeyControlInfo()[VK_DOWN]){
		m_SeeDir = LEFTDOWN;

		vMover = mIObject::vectorMove(fdeltatime, LEFTDOWN);
		m_spriteAtlas->pickSpriteAtlas(360.0f, 0.0f, 39.0f, 94.0f, 6);		
	}

	else if (m_pControl->getKeyControlInfo()[VK_LEFT] &&
		m_pControl->getKeyControlInfo()[VK_UP]){
		m_SeeDir = LEFTUP;

		vMover = mIObject::vectorMove(fdeltatime, LEFTUP);
		m_spriteAtlas->pickSpriteAtlas(360.0f, 100.0f, 44.0f, 95.0f, 6);		
	}

	else if (m_pControl->getKeyControlInfo()[VK_RIGHT] &&
		m_pControl->getKeyControlInfo()[VK_DOWN]){
		m_SeeDir = RIGHTDOWN;

		vMover = mIObject::vectorMove(fdeltatime, RIGHTDOWN);
		m_spriteAtlas->pickSpriteAtlas(360.0f, 200.0f, 39.0f, 94.0f, 6);
	}

	else if (m_pControl->getKeyControlInfo()[VK_RIGHT] &&
		m_pControl->getKeyControlInfo()[VK_UP]){
		m_SeeDir = RIGHTUP;		
		
		vMover = mIObject::vectorMove(fdeltatime, RIGHTUP);
		m_spriteAtlas->pickSpriteAtlas(360.0f, 300.0f, 44.0f, 95.0f, 6);		
	}

	else if (m_pControl->getKeyControlInfo()[VK_RIGHT]){
		if (m_SeeDir == LEFTUP){
			m_SeeDir = RIGHTUP;
		}
		else if (m_SeeDir == LEFTDOWN){
			m_SeeDir = RIGHTDOWN;
		}

		vMover = mIObject::vectorMove(fdeltatime, RIGHT);
		m_spriteAtlas->pickSpriteAtlas(0.0f, 0.0f, 47.0f, 88.0f, 6);		
	}
	else if (m_pControl->getKeyControlInfo()[VK_LEFT]){
		if (m_SeeDir == RIGHTUP){
			m_SeeDir = LEFTUP;
		}
		else if (m_SeeDir == RIGHTDOWN){
			m_SeeDir = LEFTDOWN;
		}

		vMover = mIObject::vectorMove(fdeltatime, LEFT);
		m_spriteAtlas->pickSpriteAtlas(0.0f, 185.0f, 47.0f, 88.0f, 6);		
	}
	else if (m_pControl->getKeyControlInfo()[VK_DOWN]){
		if (m_SeeDir == LEFTUP){
			m_SeeDir = LEFTDOWN;
		}
		else if (m_SeeDir == RIGHTUP){
			m_SeeDir = RIGHTDOWN;
		}

		vMover = mIObject::vectorMove(fdeltatime, DOWN);
		m_spriteAtlas->pickSpriteAtlas(0.0f, 279.0f, 35.0f, 91.0f, 6);		
	}
	else if (m_pControl->getKeyControlInfo()[VK_UP]){
		if (m_SeeDir == LEFTDOWN){
			m_SeeDir = LEFTUP;
		}
		else if (m_SeeDir == RIGHTDOWN){
			m_SeeDir = RIGHTUP;
		}

		vMover = mIObject::vectorMove(fdeltatime, UP);
		m_spriteAtlas->pickSpriteAtlas(0.0f, 373.0f, 37.0f, 92.0f, 6);		
	}
	else { // Idling

		if (m_SeeDir == RIGHTDOWN){
			// idle right down
			m_spriteAtlas->pickSpriteAtlas(0.0f, 92.0f, 64.0f, 92.0f, -19.5f, 0.0f, 4);			
			//m_spriteAtlas->pickSpriteAtlas(0.0f, 92.0f, 64.0f, 92.0f, 4);
		}
		else if (m_SeeDir == LEFTUP){
			m_spriteAtlas->pickSpriteAtlas(360.0f, 400.0f, 42.0f, 89.0f, 4);			
		}
		else if (m_SeeDir == RIGHTUP){
			m_spriteAtlas->pickSpriteAtlas(360.0f, 500.0f, 42.0f, 89.0f, 4);			
		}
		else if (m_SeeDir == LEFTDOWN){
			m_spriteAtlas->pickSpriteAtlas(0.0f, 500.0f, 64.0f, 92.0f, 19.5f, 0.0f, 4);
			//m_spriteAtlas->pickSpriteAtlas(0.0f, 500.0f, 64.0f, 92.0f, 4);
		}
	}	
	// frame update
	m_spriteAtlas->nextFrame(fdeltatime);
	
	// Todo
	// �� �����Ϳ��� �� ������ �޾ƿͼ� �̵� �Ұ� ��Ʈ��, ���� �����Ҵ������ ��ȯ
	// �� �����ʹ� ���������� �ٲ𶧸��� ������Ʈ�� ����� �Ѵ�.
	// ��Ʈ�� Ŭ������, ����Ŭ�������� �������ָ� �� ��������?
	// �ϴ� �ڿ������� �������� ���� �̵��Ұ��� �� ��θ� ���� �̵��Ұ� ó��
	// ���� ���� �� �簢���� �Ἥ �������� �ϴ� �ɱ?
	float topX = m_pTileMap->getTileCoordinates(*_drawVector + vMover).x;
	float topY = m_pTileMap->getTileCoordinates(*_drawVector + vMover).y;

	float bottomX = m_pTileMap->getTileCoordinates(*_realVector + vMover).x;
	float bottomY = m_pTileMap->getTileCoordinates(*_realVector + vMover).y;

	// �ܰ� �浹 ó��
	if (topX >= m_pTileMap->getMapLimit().x || topY >= m_pTileMap->getMapLimit().y||
		bottomX >= m_pTileMap->getMapLimit().x || bottomY >= m_pTileMap->getMapLimit().y||
		topX < 0 || topY < 0 ||bottomX < 0 || bottomY < 0){
		return;
	}

	// �̵��Ұ��� �̵��Ұ� ó��
	// move update, ���⼭ float -> int ��ȯ�� �Ͼ ������ �ν��� �������� �ִ�.
	// ���� Ư���� ���Ϳ��� �浹ó���� ���� ����(���� �������̶�� �浹 ó���� �־��������)
	if (m_pTileMap->getMapinfo(static_cast<int>(topX), static_cast<int>(topY)) == 0
		&& m_pTileMap->getMapinfo(static_cast<int>(bottomX), static_cast<int>(bottomY)) == 0){
		*_realVector = *_realVector + vMover;
		*_drawVector = *_drawVector + vMover;		
	}
	//
}

void mPlayer::onRender(cD2DRenderer& renderer){
	if (m_ipD2DBitmap != nullptr){
		//
		VECTOR2D cpos = m_Cam->translasteToScreen(_drawVector);
		//
		// Pivot �̹����� �Ѱ�� �ٴ� -> dxArea���� ����
		::D2D1_RECT_F dxArea
			= m_spriteAtlas->getCoordinateFromPivot(cpos);

		//	
		::D2D1_RECT_F srcArea
			= m_spriteAtlas->getSrcFrameFromSprite();

		renderer.GetRenderTarget()->DrawBitmap(m_ipD2DBitmap, dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);

		

		//ȸ��� �ʿ��� �κ�
		//renderer.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());

		//debug ��
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