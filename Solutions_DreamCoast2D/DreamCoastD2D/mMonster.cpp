#include "stdafx.h"
#include "mMonster.h"
#include "VECTOR2D.h"
#include "uSprite.h"
#include "cD2DRenderer.h"

mMonster::mMonster()
{
	m_ipD2DBitmap = nullptr;
	_realVector = new VECTOR2D(514.0f, 384.0f);
	_drawVector = new VECTOR2D(_realVector->x, _realVector->y + 15.0f);
	m_spriteAtlas = new uSprite();
	m_pState = nullptr; // 현재 상태는 nullptr로 시작

	m_SeeDir = RIGHTDOWN;
	m_State = ONMOVE;
}


mMonster::~mMonster()
{
	SafeRelease(m_ipD2DBitmap);
	if (_drawVector != NULL){
		delete _drawVector;
	}
	if (m_spriteAtlas != NULL){
		delete m_spriteAtlas;
	}
}

void mMonster::onInit(cD2DRenderer& renderer){
	// 현재는 기본으로 포링이지만, 상속받아서 바꿀수 있다.
	HWND hWnd = renderer.GetHwnd();
	m_ipD2DBitmap = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/poring.png", NULL);
}

void mMonster::onUpdate(float fdeltatime){
	
}
