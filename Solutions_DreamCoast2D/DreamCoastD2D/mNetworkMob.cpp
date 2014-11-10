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

		::cD2DRenderer::GetInstance().GetRenderTarget()->DrawBitmap(
			::cResourceManager::GetInstance().getMobBitMap(m_CurrentPacket.mob_type), dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
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