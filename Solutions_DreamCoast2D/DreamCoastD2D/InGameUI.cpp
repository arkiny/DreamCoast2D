#include "stdafx.h"
#include "InGameUI.h"
#include "uiInterface.h"
#include "uiPlayerStatBar.h"
#include "uiGameMiniMap.h"
#include "uiMenu.h"
#include "uiBelt.h"
#include "uiInventory.h"
#include "uiStat.h"
#include "uiInGameMenu.h"

InGameUI::InGameUI()
{
}

InGameUI::InGameUI(ICharacter* player, wTileMap* tileMap){
	m_pInterface.push_back(new uiPlayerStatBar(player));
	m_pInterface.push_back(new uiGameMiniMap(tileMap));	
	m_pInterface.push_back(new uiInventory(player));
	m_pInterface.push_back(new uiBelt(player));
	m_pInterface.push_back(new uiStat(player));
	m_pInterface.push_back(new uiInGameMenu());
}

InGameUI::~InGameUI()
{
}

void InGameUI::Render(){
	for (uiInterface* x : m_pInterface){
		x->Render();
	}
} 

void InGameUI::Update(float delta){
	// ºñÆ®¸Ê ÀÌ¿ë½Ã ÄÁÆ®·Ñ
	for (uiInterface* x : m_pInterface){
		x->Update(delta);
	}
}

void InGameUI::OnInit(sIScreen* in){
	// ºñÆ®¸Ê ÀÌ¿ë½Ã ÀÌ´Ï¼È ¶óÀÌÂ¡	
	m_callbackScreen = in;
	m_pInterface.push_back(new uiMenu(5, m_callbackScreen));
	for (uiInterface* x : m_pInterface){
		x->OnInit();
	}
}