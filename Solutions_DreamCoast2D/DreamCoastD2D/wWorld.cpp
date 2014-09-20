#include "stdafx.h"
#include "wWorld.h"
#include "mPlayer.h"
#include "wTileMap.h"

wWorld::wWorld()
{
	m_Player = nullptr;
	m_Map = nullptr;
}

wWorld::~wWorld()
{
	if (m_Player != NULL)
		delete m_Player;
	if (m_Map != NULL)
		delete m_Map;
}

void wWorld::OnInit(cD2DRenderer& renderer, coControl* in){
	m_Player = new mPlayer;
	m_Player->onInit(renderer);
	m_Player->setKeyControl(in);

	m_Map = new wTileMap;
	m_Map->onInit(renderer);
	m_Map->setPlayer(m_Player);
}

void wWorld::Render(cD2DRenderer& renderer){
	m_Map->onRender(renderer);
}

void wWorld::Update(float deltaTime){
	m_Map->onUpdate(deltaTime);
}

