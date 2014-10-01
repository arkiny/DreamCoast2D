#include "stdafx.h"
#include "InGameUI.h"
#include "uiInterface.h"
#include "uiPlayerStatBar.h"
#include "uiGameMiniMap.h"

InGameUI::InGameUI()
{
}

InGameUI::InGameUI(mIObject* player, wTileMap* tileMap){
	m_pInterface.push_back(new uiPlayerStatBar(player));
	m_pInterface.push_back(new uiGameMiniMap(tileMap));
}

InGameUI::~InGameUI()
{
}

void InGameUI::Render(cD2DRenderer& renderer){
	for (uiInterface* x : m_pInterface){
		x->Render(renderer);
	}
}

void InGameUI::Update(float delta){
	// ºñÆ®¸Ê ÀÌ¿ë½Ã ÄÁÆ®·Ñ
	for (uiInterface* x : m_pInterface){
		x->Update(delta);
	}
}

void InGameUI::OnInit(cD2DRenderer& renderer){
	// ºñÆ®¸Ê ÀÌ¿ë½Ã ÀÌ´Ï¼È ¶óÀÌÂ¡
	for (uiInterface* x : m_pInterface){
		x->OnInit(renderer);
	}
}