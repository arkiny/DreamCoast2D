#include "stdafx.h"
#include "coControl.h"


coControl::coControl()
{
	memset(m_bKeyCodeArray, 0, sizeof(m_bKeyCodeArray));
	m_MousePos = { 0, 0 };
}


coControl::~coControl()
{
}

// Key Control
void coControl::onKeyDown(WPARAM wParam){
	m_bKeyCodeArray[wParam] = true;
}
void coControl::onKeyUp(WPARAM wParam){
	m_bKeyCodeArray[wParam] = false;
}

// Mouse Control
void coControl::onLMBDown(LPARAM lParam){
	m_MousePos.x = LOWORD(lParam);
	m_MousePos.y = HIWORD(lParam);
}
void coControl::onLMBUp(LPARAM lParam){
	m_MousePos.x = LOWORD(lParam);
	m_MousePos.y = HIWORD(lParam);
}

// Getter
bool* coControl::getKeyControlInfo(){
	return m_bKeyCodeArray;
}
POINT coControl::getMousePosition(){
	return m_MousePos;
}
