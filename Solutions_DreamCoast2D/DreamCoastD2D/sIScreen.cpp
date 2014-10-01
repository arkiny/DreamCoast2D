#include "stdafx.h"
#include "sIScreen.h"

sIScreen::sIScreen(){
	m_pGameManager = nullptr;
}

sIScreen::sIScreen(cGameManager* in, cResourceManager* inr)
{	
	//communication init
	m_pGameManager = in;
	m_pResource = inr;
}


sIScreen::~sIScreen()
{
}
