#include "stdafx.h"
#include "sIScreen.h"

sIScreen::sIScreen(){
	m_pGameManager = nullptr;
}

sIScreen::sIScreen(cGameManager* in)
{	
	m_pGameManager = in;
}


sIScreen::~sIScreen()
{
}
