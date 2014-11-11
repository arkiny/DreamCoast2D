#include "stdafx.h"
#include "mNetworkMob.h"

#include "cD2DRenderer.h"
#include "uCamera.h"
#include "VECTOR2D.h"
#include "cResourceManager.h"

#include "uSprite.h"

#include "niMobStateIdle.h"

mNetworkMob::mNetworkMob(){
	m_spriteAtlas = new uSprite();
	m_CurrentState = new niMobStateIdle;

	m_CurrentState->enter(this);
}

mNetworkMob::mNetworkMob(movePacket in){
	m_CurrentPacket = in;
	m_spriteAtlas = new uSprite();

	m_CurrentState = new niMobStateIdle;
	m_CurrentState->enter(this);
}

mNetworkMob::~mNetworkMob(){
	if (m_spriteAtlas != NULL){
		delete m_spriteAtlas;
	}
	if (m_CurrentState != NULL){
		delete m_CurrentState;
	}
}

void mNetworkMob::init(){

}

void mNetworkMob::render(uCamera* cam){



	VECTOR2D pos(m_CurrentPacket.px, m_CurrentPacket.py);
	VECTOR2D cpos = cam->translasteToScreen(&pos);


	if (::cResourceManager::GetInstance().getMobBitMap(m_CurrentPacket.mob_type) != nullptr){
		// Pivot 이미지의 한가운데 바닥 -> dxArea에서 지정
		::D2D1_RECT_F dxArea
			= m_spriteAtlas->getCoordinateFromPivot(cpos);

		//	
		::D2D1_RECT_F srcArea
			= m_spriteAtlas->getSrcFrameFromSprite();

		if (m_CurrentPacket.seedir == LEFTDOWN || m_CurrentPacket.seedir == LEFTUP){
			::cD2DRenderer::GetInstance().GetRenderTarget()->DrawBitmap(
				::cResourceManager::GetInstance().getMobBitMap(m_CurrentPacket.mob_type), dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
		else if (m_CurrentPacket.seedir == RIGHTDOWN || m_CurrentPacket.seedir == RIGHTUP){
			::cD2DRenderer::GetInstance().GetRenderTarget()->SetTransform(
				D2D1::Matrix3x2F::Scale(D2D1::Size(-1.0f, 1.0f), D2D1::Point2F(cpos.x, cpos.y)));

			::cD2DRenderer::GetInstance().GetRenderTarget()->DrawBitmap(
				::cResourceManager::GetInstance().getMobBitMap(m_CurrentPacket.mob_type), dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);

			::cD2DRenderer::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
		}
	}
}

void mNetworkMob::update(float delta){
	m_fDelta = delta;
	m_CurrentState->execute(this);
}

void mNetworkMob::changeState(niMobState* pnew){
	if (m_CurrentState == nullptr || pnew == nullptr) return;
	m_CurrentState->exit(this);
	delete m_CurrentState;

	m_CurrentState = pnew;
	m_CurrentState->enter(this);
}

VECTOR2D mNetworkMob::vectorMove(float fdeltatime, DIRECTION dir){
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

void mNetworkMob::setPacketPosition(float x, float y){
	m_CurrentPacket.px = x;
	m_CurrentPacket.py = y;
}

// 164, 39, 4frame
void mNetworkMob::onIdle(){
	if (m_CurrentPacket.seedir == LEFTDOWN || m_CurrentPacket.seedir == RIGHTDOWN){
		SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(m_CurrentPacket.mob_type, 0, 0);
		m_spriteAtlas->pickSpriteAtlas(
			in->x,
			in->y,
			in->width,
			in->height,
			in->offsetX,
			in->offsetY,
			in->maxFrame);
	}
	else if (m_CurrentPacket.seedir == LEFTUP || m_CurrentPacket.seedir == RIGHTUP){

		SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(m_CurrentPacket.mob_type, 0, 1);
		m_spriteAtlas->pickSpriteAtlas(
			in->x,
			in->y,
			in->width,
			in->height,
			in->offsetX,
			in->offsetY,
			in->maxFrame);
	}
}

void mNetworkMob::onAttack(){
	if (m_CurrentPacket.seedir == LEFTDOWN || m_CurrentPacket.seedir == RIGHTDOWN){
		SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(m_CurrentPacket.mob_type, 2, 0);
		m_spriteAtlas->pickSpriteAtlas(
			in->x,
			in->y,
			in->width,
			in->height,
			in->offsetX,
			in->offsetY,
			in->maxFrame);
	}
	else if (m_CurrentPacket.seedir == LEFTUP || m_CurrentPacket.seedir == RIGHTUP){
		SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(m_CurrentPacket.mob_type, 2, 1);
		m_spriteAtlas->pickSpriteAtlas(
			in->x,
			in->y,
			in->width,
			in->height,
			in->offsetX,
			in->offsetY,
			in->maxFrame);
	}
}

void mNetworkMob::onHit(){
	if (m_CurrentPacket.seedir == LEFTDOWN || m_CurrentPacket.seedir == RIGHTDOWN){
		SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(m_CurrentPacket.mob_type, 4, 0);
		m_spriteAtlas->pickSpriteAtlas(
			in->x,
			in->y,
			in->width,
			in->height,
			in->offsetX,
			in->offsetY,
			in->maxFrame);
	}
	else if (m_CurrentPacket.seedir == LEFTUP || m_CurrentPacket.seedir == RIGHTUP){
		SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(m_CurrentPacket.mob_type, 4, 1);
		m_spriteAtlas->pickSpriteAtlas(
			in->x,
			in->y,
			in->width,
			in->height,
			in->offsetX,
			in->offsetY,
			in->maxFrame);
	}
}

void mNetworkMob::onDeath(){
	if (m_CurrentPacket.seedir == LEFTDOWN || m_CurrentPacket.seedir == RIGHTDOWN){
		SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(m_CurrentPacket.mob_type, 5, 0);
		m_spriteAtlas->pickSpriteAtlas(
			in->x,
			in->y,
			in->width,
			in->height,
			in->offsetX,
			in->offsetY,
			in->maxFrame);
	}
	else if (m_CurrentPacket.seedir == LEFTUP || m_CurrentPacket.seedir == RIGHTUP){
		SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(m_CurrentPacket.mob_type, 5, 1);
		m_spriteAtlas->pickSpriteAtlas(
			in->x,
			in->y,
			in->width,
			in->height,
			in->offsetX,
			in->offsetY,
			in->maxFrame);
	}
}

void mNetworkMob::onMove(){
	if (m_CurrentPacket.seedir == LEFTDOWN || m_CurrentPacket.seedir == RIGHTDOWN){
		SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(m_CurrentPacket.mob_type, 1, 0);
		m_spriteAtlas->pickSpriteAtlas(
			in->x,
			in->y,
			in->width,
			in->height,
			in->offsetX,
			in->offsetY,
			in->maxFrame);
	}
	else if (m_CurrentPacket.seedir == LEFTUP || m_CurrentPacket.seedir == RIGHTUP){
		SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(m_CurrentPacket.mob_type, 1, 1);
		m_spriteAtlas->pickSpriteAtlas(
			in->x,
			in->y,
			in->width,
			in->height,
			in->offsetX,
			in->offsetY,
			in->maxFrame);
	}
}

void mNetworkMob::onCasting(){
	if (m_CurrentPacket.seedir == LEFTDOWN || m_CurrentPacket.seedir == RIGHTDOWN){
		SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(m_CurrentPacket.mob_type, 3, 0);
		m_spriteAtlas->pickSpriteAtlas(
			in->x,
			in->y,
			in->width,
			in->height,
			in->offsetX,
			in->offsetY,
			in->maxFrame);
	}
	else if (m_CurrentPacket.seedir == LEFTUP || m_CurrentPacket.seedir == RIGHTUP){
		SpriteAnimationInfo* in = cResourceManager::GetInstance().getMonsterSpriteInfo(m_CurrentPacket.mob_type, 3, 1);
		m_spriteAtlas->pickSpriteAtlas(
			in->x,
			in->y,
			in->width,
			in->height,
			in->offsetX,
			in->offsetY,
			in->maxFrame);
	}
}

// todo: 상하좌우 움직임 없앨것 (알고리즘을 그렇게 처리)
void mNetworkMob::moveToDest(float deltaTime){
	VECTOR2D vMover;

	if (m_CurrentPacket.dx < m_CurrentPacket.px && m_CurrentPacket.dy < m_CurrentPacket.py){
		vMover = vectorMove(deltaTime, LEFTUP);
		m_CurrentPacket.seedir = LEFTUP;
		m_CurrentPacket.direction = LEFTUP;
		/*toServer.direction = LEFTUP;
		toServer.seedir = LEFTUP;*/
	}
	else if (m_CurrentPacket.dx > m_CurrentPacket.px && m_CurrentPacket.dy > m_CurrentPacket.py){
		vMover = vectorMove(deltaTime, RIGHTDOWN);
		m_CurrentPacket.seedir = RIGHTDOWN;
		m_CurrentPacket.direction = RIGHTDOWN;
		/*toServer.direction = RIGHTDOWN;
		toServer.seedir = RIGHTDOWN;*/
	}
	else if (m_CurrentPacket.dx < m_CurrentPacket.px && m_CurrentPacket.dy >  m_CurrentPacket.py){
		vMover = vectorMove(deltaTime, LEFTDOWN);
		m_CurrentPacket.seedir = LEFTDOWN;
		m_CurrentPacket.direction = LEFTDOWN;
		/*toServer.direction = LEFTDOWN;
		toServer.seedir = LEFTDOWN;*/
	}
	else if (m_CurrentPacket.dx > m_CurrentPacket.px && m_CurrentPacket.dy < m_CurrentPacket.py){
		vMover = vectorMove(deltaTime, RIGHTUP);
		m_CurrentPacket.seedir = RIGHTUP;
		m_CurrentPacket.direction = RIGHTUP;
		/*toServer.direction = RIGHTUP;
		toServer.seedir = RIGHTUP;*/
	}
	else if (m_CurrentPacket.dx < m_CurrentPacket.px){
		vMover = vectorMove(deltaTime, LEFT);
		/*if (m_SeeDir == RIGHTUP){
		m_SeeDir = LEFTUP;
		}
		else if (m_SeeDir == RIGHTDOWN){
		m_SeeDir = LEFTDOWN;
		}*/
		m_CurrentPacket.seedir = LEFTDOWN;
		m_CurrentPacket.direction = LEFTDOWN;
		/*	toServer.direction = LEFT;
		toServer.seedir = LEFTDOWN;*/
	}
	else if (m_CurrentPacket.dx > m_CurrentPacket.px){
		vMover = vectorMove(deltaTime, RIGHT);
		/*if (m_SeeDir == LEFTUP){
		m_SeeDir = RIGHTUP;
		}
		else if (m_SeeDir == LEFTDOWN){
		m_SeeDir = RIGHTDOWN;
		}*/
		m_CurrentPacket.seedir = RIGHTDOWN;
		m_CurrentPacket.direction = RIGHTDOWN;
		/*toServer.direction = RIGHT;
		toServer.seedir = RIGHTDOWN;*/
	}
	else if (m_CurrentPacket.dy < m_CurrentPacket.py){
		vMover = vectorMove(deltaTime, UP);
		//toServer.direction = UP;

		if (m_CurrentPacket.seedir == LEFTDOWN){
			m_CurrentPacket.seedir = LEFTUP;
			m_CurrentPacket.direction = LEFTUP;
			//toServer.seedir = LEFTUP;
		}
		else if (m_CurrentPacket.seedir == RIGHTDOWN){
			m_CurrentPacket.seedir = RIGHTUP;
			m_CurrentPacket.direction = RIGHTUP;
			//toServer.seedir = RIGHTUP;
		}
	}
	else if (m_CurrentPacket.dy > m_CurrentPacket.py){
		vMover = vectorMove(deltaTime, DOWN);
		//toServer.direction = DOWN;

		if (m_CurrentPacket.seedir == LEFTUP){
			m_CurrentPacket.seedir = LEFTDOWN;
			m_CurrentPacket.direction = LEFTDOWN;
			//toServer.seedir = LEFTDOWN;
		}
		else if (m_CurrentPacket.seedir == RIGHTUP){
			m_CurrentPacket.seedir = RIGHTDOWN;
			m_CurrentPacket.direction = RIGHTDOWN;
			//toServer.seedir = RIGHTDOWN;
		}
	}
	m_CurrentPacket.px = m_CurrentPacket.px + vMover.x;
	m_CurrentPacket.py = m_CurrentPacket.py + vMover.y;

	// 플롯 벡터 움직임 오차범위
	// 플롯이고, 또한 벡터 무빙으로 움직이기 때문에 어느정도의 오차는 발생한다.
	// 오차범위내에 들어가면 도착한걸로 결정
	float tolerance = 2.0f;
	if (abs(m_CurrentPacket.px - m_CurrentPacket.dx) < tolerance){
		m_CurrentPacket.dx = m_CurrentPacket.px;
	}
	if (abs(m_CurrentPacket.py - m_CurrentPacket.dy) < tolerance){
		m_CurrentPacket.dy = m_CurrentPacket.py;
	}
}