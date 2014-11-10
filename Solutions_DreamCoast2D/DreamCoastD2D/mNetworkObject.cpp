#include "stdafx.h"
#include "mNetworkObject.h"

#include "cD2DRenderer.h"
#include "uCamera.h"
#include "VECTOR2D.h"
#include "cResourceManager.h"

#include "uSprite.h"

#include "nStateIdle.h"
#include "wTileMap.h"
#include "uTile.h"
#include "uSprite.h"

mNetworkObject::mNetworkObject()
{
	m_spriteAtlas = new uSprite();
	m_CurrentState = new nStateIdle;
	m_ipD2DBitmap = ::cResourceManager::GetInstance().getPlayerBitMap();
	m_CurrentState->enter(this);
}

mNetworkObject::mNetworkObject(movePacket in){
	m_CurrentPacket = in;
	m_spriteAtlas = new uSprite();
	m_CurrentState = new nStateIdle;
	m_ipD2DBitmap = ::cResourceManager::GetInstance().getPlayerBitMap();
	m_CurrentState->enter(this);
}

mNetworkObject::~mNetworkObject()
{
	if (m_spriteAtlas != NULL){
		delete m_spriteAtlas;
	}
	if (m_CurrentState != NULL){
		delete m_CurrentState;
	}
}


void mNetworkObject::init(){

}

void mNetworkObject::render(uCamera* cam){
	VECTOR2D pos(m_CurrentPacket.px, m_CurrentPacket.py);
	VECTOR2D cpos = cam->translasteToScreen(&pos);


	if (::cResourceManager::GetInstance().getPlayerBitMap()!=nullptr){
		// Pivot 이미지의 한가운데 바닥 -> dxArea에서 지정
		::D2D1_RECT_F dxArea
			= m_spriteAtlas->getCoordinateFromPivot(cpos);

		//	
		::D2D1_RECT_F srcArea
			= m_spriteAtlas->getSrcFrameFromSprite();

		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawBitmap(
			::cResourceManager::GetInstance().getPlayerBitMap(), dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);	
	}

	/*::D2D1_RECT_F MiniRectangle = {
		cpos.x - 20.0f,
		cpos.y - 20.0f,
		cpos.x + 20.0f,
		cpos.y + 20.0f
	};

	::D2D1_RECT_F point = {
		cpos.x - 2.0f,
		cpos.y - 2.0f,
		cpos.x + 2.0f,
		cpos.y + 2.0f
	};

	::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(point,
		::cD2DRenderer::GetInstance().GetBlackBrush());

	::cD2DRenderer::GetInstance().GetRenderTarget()->DrawRectangle(MiniRectangle,
			::cD2DRenderer::GetInstance().GetBlackBrush());*/
}

void mNetworkObject::update(float delta){
	// 이동중일때 이동한 좌표를 출력
	m_fDelta = delta;
	m_CurrentState->execute(this);

	//if (m_CurrentPacket.state == ONMOVE){
	//	VECTOR2D vMover;
	//	vMover = vectorMove(delta, (DIRECTION)m_CurrentPacket.direction);
	//	VECTOR2D pos(m_CurrentPacket.px, m_CurrentPacket.py);
	//	pos = pos + vMover;
	//	m_CurrentPacket.px = pos.x;
	//	m_CurrentPacket.py = pos.y;
	//}
	//else { 
	//	// idle일때는 그대로 출력
	//}
}

void mNetworkObject::setPacketPosition(float x, float y){
	m_CurrentPacket.px = x;
	m_CurrentPacket.py = y;
}

void mNetworkObject::changeState(niState* pnew){
	if (m_CurrentState == nullptr || pnew == nullptr) return;
	m_CurrentState->exit(this);
	delete m_CurrentState;

	m_CurrentState = pnew;
	m_CurrentState->enter(this);
}

VECTOR2D mNetworkObject::vectorMove(float fdeltatime, DIRECTION dir){
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
		// 1:2 isometric이므로 세로 이동속도는 절반으로 수정
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

	// todo: 차후 100.0f각 각 object별 이속으로 변경
	if (dir != NOMOVE){
		vDir.Normalize();
	}
	vMover = vDir*(m_CurrentPacket.speed * fdeltatime);

	return vMover;
}

// 공격 속도 조정
void mNetworkObject::dmgToTile(float delta, float dmg){
	m_attackaccumtime += delta;
	VECTOR2D currentVector(m_CurrentPacket.px, m_CurrentPacket.py);
	VECTOR2D currentTile = m_pTileMap->getTileCoordinates(currentVector);

	float fx, fy;

	if (m_attackaccumtime > FRAMERATE * 2.5f){
	//if (m_spriteAtlas->getCurrentFrame() == 4){
		//attacktrigger = true;
		m_attackaccumtime = 0.0f;
		if (m_CurrentPacket.seedir == LEFTDOWN){
			fx = currentTile.x + 1.0f;
			fy = currentTile.y;
		}
		else if (m_CurrentPacket.seedir == LEFTUP){
			fx = currentTile.x;
			fy = currentTile.y - 1.0f;
		}
		else if (m_CurrentPacket.seedir == RIGHTDOWN){
			fx = currentTile.x;
			fy = currentTile.y + 1.0f;
		}
		else if (m_CurrentPacket.seedir == RIGHTUP){
			fx = currentTile.x - 1.0f;;
			fy = currentTile.y;
		}
		else {}
		// 같은 타일내에 겹쳐 있을수도 있으므로...
		m_pTileMap->getTile(currentTile.x, currentTile.y)->onHit(dmg);
		m_pTileMap->getTile(fx, fy)->onHit(dmg);
	}
}