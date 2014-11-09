#include "stdafx.h"
#include "mTestObject.h"

#include "cD2DRenderer.h"
#include "uCamera.h"
#include "VECTOR2D.h"


mTestObject::mTestObject()
{
}

mTestObject::mTestObject(movePacket in){
	m_CurrentPacket = in;
}

mTestObject::~mTestObject()
{
}


void mTestObject::init(){

}

void mTestObject::render(uCamera* cam){
	VECTOR2D pos(m_CurrentPacket.px, m_CurrentPacket.py);
	VECTOR2D cpos = cam->translasteToScreen(&pos);

	::D2D1_RECT_F MiniRectangle = {
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
			::cD2DRenderer::GetInstance().GetBlackBrush());
}

void mTestObject::update(float delta){
	// 이동중일때 이동한 좌표를 출력
	if (m_CurrentPacket.state == ONMOVE){
		VECTOR2D vMover;
		vMover = vectorMove(delta, (DIRECTION)m_CurrentPacket.direction);
		VECTOR2D pos(m_CurrentPacket.px, m_CurrentPacket.py);
		pos = pos + vMover;
		m_CurrentPacket.px = pos.x;
		m_CurrentPacket.py = pos.y;
	}
	else { 
		// idle일때는 그대로 출력
	}
}

VECTOR2D mTestObject::vectorMove(float fdeltatime, DIRECTION dir){
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