#include "stdafx.h"
#include "uiInterface.h"
#include "VECTOR2D.h"


uiInterface::uiInterface()
{
	m_vpos = nullptr;
	m_fMB_cache_old = { 0.0f, 0.0f };
	m_fMB_cache_gap = { 0.0f, 0.0f };
	m_MoveWindowRect = { 0.0f, 0.0f,0.0f, 0.0f };
	m_ClickWindowRect = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_MoveWindowRectOrigin = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_ClickWindowRectOrigin = { 0.0f, 0.0f, 0.0f, 0.0f };
}

uiInterface::uiInterface(float x, float y)
{
	m_vpos = new VECTOR2D(x, y);
	m_fMB_cache_old = { 0.0f, 0.0f };
	m_fMB_cache_gap = { 0.0f, 0.0f };
	m_MoveWindowRect = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_ClickWindowRect = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_MoveWindowRectOrigin = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_ClickWindowRectOrigin = { 0.0f, 0.0f, 0.0f, 0.0f };
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

void uiInterface::setMoveRectangle(D2D1_RECT_F in){
	m_MoveWindowRectOrigin = in;
	m_MoveWindowRect = {
		this->getPos()->x + m_MoveWindowRectOrigin.left,
		this->getPos()->y + m_MoveWindowRectOrigin.top,
		this->getPos()->x + m_MoveWindowRectOrigin.right,
		this->getPos()->y + m_MoveWindowRectOrigin.bottom
	};
}

void uiInterface::setClickRenctangle(D2D1_RECT_F in){
	m_ClickWindowRectOrigin = in;
	m_ClickWindowRect = {
		this->getPos()->x + m_ClickWindowRectOrigin.left,
		this->getPos()->y + m_ClickWindowRectOrigin.top,
		this->getPos()->x + m_ClickWindowRectOrigin.right,
		this->getPos()->y + m_ClickWindowRectOrigin.bottom
	};
}

void uiInterface::moveTo(float x, float y){
	this->setPos(x - m_fMB_cache_gap.x, y - m_fMB_cache_gap.y);

	m_MoveWindowRect = { this->getPos()->x + m_MoveWindowRectOrigin.left,
		this->getPos()->y + m_MoveWindowRectOrigin.top,
		this->getPos()->x + m_MoveWindowRectOrigin.right,
		this->getPos()->y + m_MoveWindowRectOrigin.bottom };

	m_ClickWindowRect = {
		this->getPos()->x + m_ClickWindowRectOrigin.left,
		this->getPos()->y + m_ClickWindowRectOrigin.top,
		this->getPos()->x + m_ClickWindowRectOrigin.right,
		this->getPos()->y + m_ClickWindowRectOrigin.bottom
	};
}

void uiInterface::saveOldPos(float x, float y){
	m_fMB_cache_old = { this->getPos()->x, this->getPos()->y };
	m_fMB_cache_gap = { x - this->getPos()->x, y - this->getPos()->y };
}

bool uiInterface::isInsideMovingRect(float mousex, float mousey){
	return (mousex >= m_MoveWindowRect.left &&
		mousey >= m_MoveWindowRect.top&&
		mousex <= m_MoveWindowRect.right &&
		mousey <= m_MoveWindowRect.bottom);
}

bool uiInterface::isInsideClickRect(float x, float y){
	return (x >= m_ClickWindowRectOrigin.left &&
		y >= m_ClickWindowRectOrigin.top&&
		x <= m_ClickWindowRectOrigin.right &&
		y <= m_ClickWindowRectOrigin.bottom);
}