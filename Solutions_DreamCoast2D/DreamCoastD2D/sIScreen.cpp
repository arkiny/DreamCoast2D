#include "stdafx.h"
#include "sIScreen.h"

sIScreen::sIScreen(){
	m_pGameManager = nullptr;
}

sIScreen::sIScreen(cGameManager* in)
{	
	//communication init
	m_pGameManager = in;
}


sIScreen::~sIScreen()
{
}
