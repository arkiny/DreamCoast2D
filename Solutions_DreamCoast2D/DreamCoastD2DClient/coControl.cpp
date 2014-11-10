#include "stdafx.h"
#include "coControl.h"

template<> coControl* Singleton<coControl>::_instance = 0;

coControl::coControl()
{
	memset(m_bKeyCodeArray, 0, sizeof(m_bKeyCodeArray));
	m_MousePos = { 0, 0 };
}


coControl::~coControl()
{
}

// Key Control
// todo : 반대방향 키를 눌렀을때, 반대방향이 true가 되며
// 다른방향이 false가 되게 수정
// 위와 같이 고치게 되면
void coControl::onKeyDown(WPARAM wParam){
	m_bKeyCodeArray[wParam] = true;
	//if (wParam == VK_RIGHT){
	//	m_bKeyCodeArray[VK_LEFT] = false;
	//}
	//if (wParam == VK_LEFT){
	//	m_bKeyCodeArray[VK_RIGHT] = false;
	//}
	//if (wParam == VK_UP){
	//	m_bKeyCodeArray[VK_DOWN] = false;
	//}
	//if (wParam == VK_DOWN){
	//	m_bKeyCodeArray[VK_UP] = false;
	//}
}
void coControl::onKeyUp(WPARAM wParam){
	m_bKeyCodeArray[wParam] = false;
}

// Mouse Control
//void coControl::onLMBDown(WPARAM wParam){
//	m_bKeyCodeArray[wParam] = true;
//}
//void coControl::onLMBUp(WPARAM wParam){
//	m_bKeyCodeArray[wParam] = false;
//}

void coControl::onMouseMove(LPARAM lParam){
	m_MousePos.x = LOWORD(lParam);
	m_MousePos.y = HIWORD(lParam);
}

void coControl::onMouseClick(LPARAM lParam){
	m_ClickPos.x = LOWORD(lParam);
	m_ClickPos.y = HIWORD(lParam);
}


// Getter
bool* coControl::getKeyControlInfo(){
	return m_bKeyCodeArray;
}

POINTFLOAT coControl::getMousePosition(){
	return m_MousePos;
}

POINTFLOAT coControl::getClickPosition(){
	return m_ClickPos;
}