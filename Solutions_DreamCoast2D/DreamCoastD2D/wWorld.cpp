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
	
	m_Map = new wTileMap;
	m_Map->setPlayer(m_Player);
	m_Map->onInit(renderer);

	m_Player->setTileMap(m_Map);
	m_Player->setKeyControl(in);
	
	// ������ ��ſ� ������ ����
	// ��Ʈ���� �ѹ� �����س����� ��ĥ���� ������, 
	// ���ο� ���̳� ���ο� ĳ���� ���� ��쿡��
	// ��ȣ�� ������ ������Ʈ�� �� ������Ѵ�. 
	// ���� ���� ������ �޸� �����ϴ� �͵� �ʼ�
	m_Map->setSize(25.0f, 25.0f);
}

void wWorld::Render(cD2DRenderer& renderer){
	// �ʿ��� Player�������� ó��
	// ���� ������ Ÿ�� -> �÷��̾� -> ������Ʈ ������ �ǽ�
	m_Map->onRender(renderer);
}

void wWorld::Update(float deltaTime){
	m_Map->onUpdate(deltaTime);
}

