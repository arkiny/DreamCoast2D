#include "stdafx.h"
#include "iInScreenUI.h"
#include "uiInterface.h"


iInScreenUI::iInScreenUI()
{
}


iInScreenUI::~iInScreenUI()
{
	uiInterface* ptr = nullptr;;
	while (!m_pInterface.empty()){
		ptr = m_pInterface.back();
		delete ptr;
		m_pInterface.pop_back();
	}
	ptr = nullptr;
}
