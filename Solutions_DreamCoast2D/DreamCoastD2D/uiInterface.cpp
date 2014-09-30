#include "stdafx.h"
#include "uiInterface.h"
#include "VECTOR2D.h"


uiInterface::uiInterface()
{
	m_vpos = nullptr;
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