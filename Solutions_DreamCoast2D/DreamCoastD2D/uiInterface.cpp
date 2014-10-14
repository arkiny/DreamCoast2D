#include "stdafx.h"
#include "uiInterface.h"
#include "VECTOR2D.h"


uiInterface::uiInterface()
{
	m_vpos = nullptr;
	m_fMB_cache_old = { 0.0f, 0.0f };
	m_fMB_cache_gap = { 0.0f, 0.0f };
	m_MoveWindowRect = { 0.0f, 0.0f,0.0f, 0.0f };
}

uiInterface::uiInterface(float x, float y)
{
	m_vpos = new VECTOR2D(x, y);
	m_fMB_cache_old = { 0.0f, 0.0f };
	m_fMB_cache_gap = { 0.0f, 0.0f };
	m_MoveWindowRect = { 0.0f, 0.0f, 0.0f, 0.0f };
}


uiInterface::~uiInterface()
{
	if (m_vpos != nullptr && m_vpos != NULL){
		delete m_vpos;
	}
}

void uiInterface::setPos(float x, float y){
	m_vpos->x = x;
	m_vpos->y = y;
}

void uiInterface::setPos(VECTOR2D* in){
	if (m_vpos != nullptr && m_vpos != NULL){
		delete m_vpos;
		m_vpos = nullptr;
	}
	m_vpos = in;
}

void uiInterface::moveTo(float x, float y){
	this->setPos(x - m_fMB_cache_gap.x, y - m_fMB_cache_gap.y);
	m_MoveWindowRect = { this->getPos()->x + 4.0f,
		this->getPos()->y + 0.0f,
		this->getPos()->x + 54.0f,
		this->getPos()->y + 13.0f };
}

void uiInterface::saveOldPos(float x, float y){
	m_fMB_cache_old = { this->getPos()->x, this->getPos()->y };
	m_fMB_cache_gap = { x - this->getPos()->x, y - this->getPos()->y };
}

bool uiInterface::isInside(float mousex, float mousey){
	return (mousex >= m_MoveWindowRect.left &&
		mousey >= m_MoveWindowRect.top&&
		mousex <= m_MoveWindowRect.right &&
		mousey <= m_MoveWindowRect.bottom);
}