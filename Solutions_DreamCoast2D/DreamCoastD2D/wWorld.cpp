#include "stdafx.h"
#include "wWorld.h"
#include "mPlayer.h"
#include "wTileMap.h"
#include "cResourceManager.h"
#include "uFileControl.h"

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

void wWorld::OnInit(int mapnumber){

	m_Player = new mPlayer;
	m_Player->onInit();
	
	m_Map = new wTileMap;
	m_Map->setPlayer(m_Player);
	//m_Map->onInit();

	// ������ ��ſ� ������ ����
	// ��Ʈ���� �ѹ� �����س����� ��ĥ���� ������, 
	// ���ο� ���̳� ���ο� ĳ���� ���� ��쿡��
	// ��ȣ�� ������ ������Ʈ�� �� ������Ѵ�. 
	// ���� ���� ������ �޸� �����ϴ� �͵� �ʼ�
	m_Player->setTileMap(m_Map);
	
	// 50*50 �̻��� ũ�⿡�� �ɰ��ϰ� ������...
	//m_Map->setSize(25.0f, 25.0f);

	uFileControl a = uFileControl(this);
	//a.SaveToFile(1);
	a.LoadFromFile(mapnumber, this);
	m_Map->onInit();
}

void wWorld::Render(){
	// �ʿ��� Player�������� ó��
	// ���� ������ Ÿ�� -> �÷��̾� -> ������Ʈ ������ �ǽ�
	m_Map->onRender();
}

void wWorld::Update(float deltaTime){

	if (m_Player->isDeadComplete()){

	}
	m_Map->onUpdate(deltaTime);
}

bool wWorld::isGameOver() { return m_Player->isDeadComplete(); }